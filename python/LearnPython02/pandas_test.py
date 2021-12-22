#!/usr/bin/python

import pandas as pd
# read csv
df=pd.read_csv("1117-1.6k.csv")
 
print(df.columns)
print(df['Chip ID'].values)
 
# condition
df_1=df[(df['Contrast']<1680)]
print(df_1['Chip ID'].values)
 
df_2=df[(df['Sagittal1']<0.7)]
print(df_2['Chip ID'].values)
 
df_3=df[(df['Contrast']<1680)&(df['Sagittal1']<0.7)]
print(df_3['Chip ID'].values)
 
df_4=df[(df['Contrast']<1680)|(df['Sagittal1']<0.7)]
print(df_4['Chip ID'].values)
 
# drop duplicates
 
df=df.drop_duplicates(['Chip ID'],'last')