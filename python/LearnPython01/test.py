import pandas as pd
import matplotlib.pyplot as plt
import ipywidgets as widgets    # 控件库
import os
from IPython.display import display # 显示控件的方法
from matplotlib.lines import Line2D
from sqlalchemy import create_engine
 
 
 
def print_title(title):
    print("==================================")
    print("|                               ||")
    print("|{:^31s}||".format(title))
    print("|                               ||")
    print("==================================")
 
DEVICE_KEY='phone'   
     
def show(df, key, v1, v2, hist_height=30):
    plt.figure(figsize=(5, 3))
    plt.vlines(v1,0,hist_height,'r')
    plt.grid()
    mean=df[key].mean()
    std=df[key].std()
     
    count=0
    if v2==-1:
        count=df[df[key]<=v1][key].count()
        print(df[df[key]<=v1][DEVICE_KEY].values)
#         plt.vlines(mean-3*std,0,hist_height,'g',linestyles='dotted')
#         plt.vlines(mean-6*std,0,hist_height,'g')
    elif v2==-2:
        count=df[df[key]>=v1][key].count()
        print(df[df[key]>=v1][DEVICE_KEY].values)
#         plt.vlines(mean+3*std,0,hist_height,'g',linestyles='dotted')
#         plt.vlines(mean+6*std,0,hist_height,'g')
    else:
        plt.vlines(v2,0,hist_height,'r')
#         plt.vlines(mean-3*std,0,hist_height,'g',linestyles='dotted')
#         plt.vlines(mean+3*std,0,hist_height,'g',linestyles='dotted')
#         plt.vlines(mean-6*std,0,hist_height,'g')
#         plt.vlines(mean+6*std,0,hist_height,'g')
        count1=df[df[key]<=v1][key].count()
        print(df[df[key]<=v1][DEVICE_KEY].values)
        count2=df[df[key]>=v2][key].count()
        print(df[df[key]>=v2][DEVICE_KEY].values)
        count=count1+count2
         
    plt.hist(df[key],40)
    plt.title("{0}:{1}".format(key, count))
    plt.show()
 
engine = create_engine('mysql+pymysql://reader:reader@10.203.10.23:3306/test_report')
sql_query='''select * from mmi_detail where project='AA001' and IsFinal=1'''
df_mmi_raw=pd.read_sql_query(sql_query, engine)
df_mmi=df_mmi_raw.drop_duplicates(['phone'],'last')
 
print_title('Optical Center')
show(df_mmi, 'OC-X', 70, 90)
show(df_mmi, 'OC-Y', 87, 117)
show(df_mmi, 'MARK-X', 70, 90)
show(df_mmi, 'MARK-Y', 92, 112)
 
# print_title('Dead Pixel')
# show(df_mmi, 'DP-Total', 200, -2)
# show(df_mmi, 'DP-Lines', 1, -2)
# show(df_mmi, 'DP-Clusters', 3, -2)
# show(df_mmi, 'DP-ClusterSize', 60, -2)
 
# print_title('HiFreq & Tilt')
# show(df_mmi, 'HiFreq', 0.66, -2)
# show(df_mmi, 'Shading-Min', 0.44, -1)
# show(df_mmi, 'FOV', 19000, -1)
# show(df_mmi, 'LinePair', 15.8, 18.6)
# show(df_mmi, 'Rotation', -20, 20)
# show(df_mmi, 'Tilt', 1, -2)
 
# print_title('SNR')
# show(df_mmi, 'SNR-Min', 6.5, -1)
# show(df_mmi, 'SNR-Center', 6.5, -1)
# show(df_mmi, 'Signal-Min', 6, -1)
# show(df_mmi, 'Signal-Center', 6, -1)
# show(df_mmi, 'Noise-Max', 8.4, -2)
# show(df_mmi, 'Noise-Center', 8.4, -2)
 
# show(df_mmi, 'TSNR-Min', 6.5, -1)
# show(df_mmi, 'TSNR-Center', 6.5, -1)
# show(df_mmi, 'TSignal-Min', 6, -1)
# show(df_mmi, 'TSignal-Center', 6, -1)
# show(df_mmi, 'TNoise-Max', 8.4, -2)
# show(df_mmi, 'TNoise-Center', 8.4, -2)
 
# print_title('Expo')
# show(df_mmi, 'SNR-Expo', 40, -2)
# show(df_mmi, 'WhiteExpo', 12, 33)
# show(df_mmi, 'BlackExpo', 18, 54)
# show(df_mmi, 'WhiteMean', 100, 280)
# show(df_mmi, 'BlackMean', 60, 160)