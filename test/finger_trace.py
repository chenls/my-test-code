#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
 
 
import os
import sys
import time
import subprocess
import matplotlib.pyplot as plt
import numpy as np
import re
# cat log time in s
logcat_times = int(sys.argv[1])
 
os.system("adb logcat -c")
current_time = time.strftime('%Y_%m_%d_%H_%M_%S',time.localtime(time.time()))
 
hal_log = current_time + "_hal.log"
ta_log = current_time + "_ta.log"
 
hal_log_process = subprocess.Popen('adb logcat |grep "ANC" >{}'.format(hal_log), shell=True)
ta_log_process = subprocess.Popen('adb shell cat /dev/kmsg | grep TEE >{}'.format(ta_log),shell=True)
# ta_log_process = subprocess.Popen('adb shell cat /d/tzdbg/qsee_log >{}'.format(ta_log),shell=True)
 
# 等待log_times之后抓取log
time.sleep(logcat_times)
 
# 终止抓取log进程
hal_log_process.terminate()
ta_log_process.terminate()
 
# 开始分析log,包括内存和耗时
time_pattern = [
r'(.*)capture image spent (.*?) ms',
r'(.*)enroll algo spent (.*?) ms',
r'(.*)verify algo spent (.*?) ms',
r'(.*)match ok spent (.*?) ms',
r'(.*)match fail spent (.*?) ms',
]
time_title = [
    "capture image time",
    "enroll algo time",
    "verify algo time",
    "match ok time",
    "match fail time"
]
 
time_result = [[],[],[],[],[]]
 
mem_pattern = [
r'(.*)Memory Peak is (.*?),',
r'(.*)Current Total Memory is (\d+)',
]
mem_title = [
    "memory peak",
    "current total memory",
]
 
mem_result = [[],[]]
with open(hal_log, 'r') as f:
    for line in f:
        for i in range(len(time_pattern)):
            match_result = re.match(time_pattern[i], line)
            if match_result :
                time_result[i].append(int(match_result.group(2)))
 
# draw
for i in range(len(time_pattern)):
    plt.figure("time")
    plt.subplot(len(time_pattern),1,i+1)
    y_max = 100 if len(time_result[i])==0  else max(time_result[i])+50
    plt.ylim(0, y_max)
    time_mean = 0 if len(time_result[i])==0 else int(np.mean(time_result[i]))
    plt.ylabel("avg:{}".format(time_mean))
    plt.title(time_title[i])
    plt.plot(range(len(time_result[i])),time_result[i])
 
plt.tight_layout()
plt.savefig('{}'.format(hal_log)+'.png')
 
with open(ta_log, 'r') as f:
    for line in f:
        for i in range(len(mem_pattern)):
            match_result = re.match(mem_pattern[i], line)
            if match_result :
                mem_result[i].append((int(match_result.group(2)))/1000000)
 
# draw
for i in range(len(mem_pattern)):
    plt.figure("memory")
    plt.subplot(len(mem_pattern),1,i+1)
    plt.ylim(0, 25)
    plt.ylabel("M")
    plt.title(mem_title[i])
    plt.plot(range(len(mem_result[i])),mem_result[i])
 
plt.tight_layout()
plt.savefig('{}'.format(ta_log)+'.png')
plt.show()
