class MySet:
    @staticmethod
    def union(set_a, set_b):
        res = set()
        for a in set_a:
            if a in set_b:
                res.add(a)
        return res

    @staticmethod
    def difference(set_a, set_b):
        res = set_a.copy()
        union = MySet.union(set_a, set_b)
        for e in union:
            res.remove(e)
        return res

    @staticmethod
    def and_set(set_a, set_b):
        res = set_a.copy()
        res.update(set_b)
        return res


setA = set(map(int, input("请输入setA\n").split(" ")))
setB = set(map(int, input("请输入setB\n").split(" ")))
print(setA)
print(setB)
print("差集")
print(setA - setB)
print(MySet.difference(setA, setB))
print("并集")
print(setA | setB)
print(MySet.and_set(setA, setB))
print("交集")
print(setA & setB)
print(MySet.union(setA, setB))
