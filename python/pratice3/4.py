class Myqueue:
    def __init__(self):
        self.size = 10
        self.data = []
        self.current = 0

    def set(self):
        self.size = 10
        self.data = []
        self.current = 0

    def if_empty(self):
        if self.current == 0:
            return True
        else:
            return False

    def if_full(self):
        if self.current == self.size:
            return True
        else:
            return False

    def get_head(self):
        if not self.if_empty():
            return self.data[0]
        else:
            print("队列为空！无法取值")

    def set_Value(self, value):
        if not self.if_full():
            self.data.append(value)
            self.current += 1

    def pop(self):
        if not self.if_empty():
            self.data.pop(0)
            self.current -= 1
            print("弹出成功！")


myQueue = Myqueue()
myQueue.set_Value(10)
myQueue.set_Value(120)
print(myQueue.get_head())
myQueue.pop()
print(myQueue.get_head())
myQueue.pop()
myQueue.set_Value(33)
myQueue.set_Value(500)
print(myQueue.get_head())
