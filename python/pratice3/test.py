import random
from collections import Counter
list = []
for i in range(50):
    list.append(random.randint(1, 20))
arr = Counter(list)
print(arr)


