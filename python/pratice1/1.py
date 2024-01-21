import random
y = int(input("请输入你要猜的数： "))
a = int(input("请输入你要猜得到数的范围前值："))
b = int(input("请输入你要猜的数的范围后值： "))
x = random.randint(a,b)
if x == y:
   print(" right   恭喜你，猜对了")
elif x < y:
    print("too small  正确答案：", x)
else:
    print("too large  正确答案：", x)