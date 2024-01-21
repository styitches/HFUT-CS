import math
f1 = math.pow(37.78, 1 / 52)
f2 = f1 / math.pow(1 - 0.01, 2)
f3 = math.pow(f2, 1 / 5)
res = f3 - 1
print("工作日要努力{:.2f}%".format(res * 100))
