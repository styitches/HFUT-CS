import random
a = int(input("请输入你要猜的数字的范围前值： "))
b = int(input("请输入你要猜的数字的范围后值：  "))
d = int(input("请输入你想要猜的次数： "))
x = random.randint(a,b)
i = 0
while i < d:
    c = int(input("请输入你要猜的数字： "))
    if c == x:
        print("right")
        break

    elif c < d:
        i += 1
        print("too small")
    else:
        i += 1
        print("too large")

if i == d:
    print("游戏结束 ， 正确结果为：", x)
