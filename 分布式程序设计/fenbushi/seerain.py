import pandas as pd
import matplotlib.pyplot as plt

# 读取CSV文件
df = pd.read_csv("highest_avg_rainfall/avg_rain.csv", header=None, names=["地区", "城市", "数值"])
plt.rcParams['font.family'] = 'SimHei'
# 根据城市分组并计算平均值
df_avg = df.groupby("城市").mean()

# 折线图
plt.figure(figsize=(10, 6))
plt.plot(df_avg.index, df_avg["数值"], marker='o', label='平均数值')
plt.title('城市平均数值折线图')
plt.xlabel('城市')
plt.ylabel('平均数值')
plt.legend()
plt.show()

# 柱状图
plt.figure(figsize=(10, 6))
plt.bar(df_avg.index, df_avg["数值"], color='skyblue', label='平均数值')
plt.title('城市平均数值柱状图')
plt.xlabel('城市')
plt.ylabel('平均数值')
plt.legend()
plt.show()
