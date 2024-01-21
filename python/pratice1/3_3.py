x = input("请输入一个字符串 ：")
# 切片法，字符串反转
a = x[::-1]
if a == x:
    print("这是一个回文")
else:
    print("这不是一个回文")
