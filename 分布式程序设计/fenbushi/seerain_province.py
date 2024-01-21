import pandas as pd
import matplotlib.pyplot as plt

# 读取新的CSV文件
df = pd.read_csv("avg_rainfall_by_province/avg_rainfall_province.csv", header=None, names=["省份", "数值"])
plt.rcParams['font.family'] = 'SimHei'

# 折线图
plt.figure(figsize=(10, 6))
plt.plot(df["省份"], df["数值"], marker='o', label='平均数值', linestyle='-', markersize=8)
plt.title('省份平均降雨量折线图')
plt.xlabel('省份')
plt.ylabel('平均降雨量')
plt.legend()

# 在每个节点上添加具体数值
for i, value in enumerate(df["数值"]):
    plt.annotate(f'{value:.3f}', (df["省份"][i], value), textcoords="offset points", xytext=(0,5), ha='center', fontsize=8)

plt.xticks(rotation=45, ha='right')  # 旋转45度，右对齐
plt.tight_layout()  # 调整布局
plt.show()

# 柱状图
plt.figure(figsize=(10, 6))
plt.bar(df["省份"], df["数值"], color='skyblue', label='平均数值')
plt.title('省份平均降雨量柱状图')
plt.xlabel('省份')
plt.ylabel('平均降雨量')
plt.legend()
# 在每个节点上添加具体数值
for i, value in enumerate(df["数值"]):
    plt.annotate(f'{value:.3f}', (df["省份"][i], value), textcoords="offset points", xytext=(0,5), ha='center', fontsize=8)

plt.xticks(rotation=45, ha='right')  # 旋转45度，右对齐
plt.tight_layout()  # 调整布局
plt.show()
