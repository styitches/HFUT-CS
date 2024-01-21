import random as r
import string
sum = 0
list1 = []
with open('第五问.txt', "w+") as f:
    for _ in range(r.randint(4, 8)):
        ran_str = ''.join(r.sample(string.ascii_letters + string.digits, 8))
        f.write(ran_str+'\n')

for i in open("第五问.txt", 'r'):
    line = i.rsplit()
    list1.append(line)
    sum +=1

print(list1)
print(sum)
