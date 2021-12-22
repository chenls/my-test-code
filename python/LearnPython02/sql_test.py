import pandas as pd
from sqlalchemy import create_engine
 
engine = create_engine('mysql+pymysql://reader:reader@10.203.10.23:3306/test_report')
sql_query='''select * from mmi_detail where project = 'nash' and timestamp > '2020-12-24' and timestamp < '2020-12-30' '''
df_mmi_nash500=pd.read_sql_query(sql_query, engine)

print(df_mmi_nash500)
# print(df.columns)
# print(df['phone'].values)