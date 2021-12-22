import pandas as pd
import matplotlib.pyplot as plt


DEVICE_KEYS = ['chip']


def show(df, key, v1, v2, hist_height=50):
    plt.figure(figsize=(5, 3))
    plt.vlines(v1, 0, hist_height, 'r')
    plt.grid()
    mean = df[key].mean()
    std = df[key].std()

    count = 0
    if v2 == -1:
        count = df[df[key] <= v1][key].count()
        if count > 0:
            for device_key in DEVICE_KEYS:
                print(df[df[key] <= v1][device_key].values)
        plt.vlines(mean-3*std, 0, hist_height, 'g', linestyles='dotted')
        plt.vlines(mean-6*std, 0, hist_height, 'g')
    elif v2 == -2:
        count = df[df[key] >= v1][key].count()
        if count > 0:
            for device_key in DEVICE_KEYS:
                print(df[df[key] >= v1][device_key].values)
        plt.vlines(mean+3*std, 0, hist_height, 'g', linestyles='dotted')
        plt.vlines(mean+6*std, 0, hist_height, 'g')
    else:
        plt.vlines(v2, 0, hist_height, 'r')
        plt.vlines(mean-3*std, 0, hist_height, 'g', linestyles='dotted')
        plt.vlines(mean+3*std, 0, hist_height, 'g', linestyles='dotted')
        plt.vlines(mean-6*std, 0, hist_height, 'g')
        plt.vlines(mean+6*std, 0, hist_height, 'g')
        count1 = df[df[key] <= v1][key].count()
        if count1 > 0:
            print('left')
            for device_key in DEVICE_KEYS:
                print(df[df[key] <= v1][device_key].values)
        count2 = df[df[key] >= v2][key].count()
        if count2 > 0:
            print('right')
            for device_key in DEVICE_KEYS:
                print(df[df[key] >= v2][device_key].values)
        count = count1+count2

    plt.hist(df[key], 40)
    plt.title("{0}:{1}".format(key, count))
    plt.show()


show(df, 'OC_X', 70, 90)
