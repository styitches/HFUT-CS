import pandas as pd
import matplotlib.pyplot as plt

# 读取新的CSV文件
df_temperature = pd.read_csv("avg_temperature_by_province/avg_temperature_province.csv", header=None, names=["省份", "平均气温"])
plt.rcParams['font.family'] = 'SimHei'

# 折线图
plt.figure(figsize=(10, 6))
plt.plot(df_temperature["省份"], df_temperature["平均气温"], marker='o', label='平均气温', linestyle='-', markersize=8)
plt.title('各省平均气温折线图')
plt.xlabel('省份')
plt.ylabel('平均气温')
plt.legend()

# 在每个节点上添加具体数值
for i, value in enumerate(df_temperature["平均气温"]):
    plt.annotate(f'{value:.3f}', (df_temperature["省份"][i], value), textcoords="offset points", xytext=(0,5), ha='center', fontsize=8)

plt.xticks(rotation=45, ha='right')  # 旋转45度，右对齐
plt.tight_layout()  # 调整布局
plt.show()

# 柱状图
plt.figure(figsize=(10, 6))
plt.bar(df_temperature["省份"], df_temperature["平均气温"], color='skyblue', label='平均气温')
plt.title('各省平均气温柱状图')
plt.xlabel('省份')
plt.ylabel('平均气温')
plt.legend()

# 在每个节点上添加具体数值
for i, value in enumerate(df_temperature["平均气温"]):
    plt.annotate(f'{value:.3f}', (df_temperature["省份"][i], value), textcoords="offset points", xytext=(0,5), ha='center', fontsize=8)

plt.xticks(rotation=45, ha='right')  # 旋转45度，右对齐
plt.tight_layout()  # 调整布局
plt.show()
