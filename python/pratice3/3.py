class Vehicle:
    __MaxSpeed = 100
    __weight = 100

    def __init__(self):
        self.__MaxSpeed = 200
        self.__weight = 101

    def set(self,maxSpeed):
        self.__MaxSpeed = maxSpeed

    def show(self):
        print(self.__MaxSpeed)


class Bicycle(Vehicle):
    def __init__(self, height):
        super().__init__()
        self.__height = height
        self.__weight = 20

    def SetMaxSpeed_Bicycle(self, maxSpeed):
        self.set(maxSpeed)

    def __set(self, height):
        self.__height = height

    def __get(self):
        return self.__height

    def __del(self):
        del self.__height

    height = property(__get,__set,__del)


bicycle = Bicycle(200)
bicycle.height = 100
print(bicycle.height)
bicycle.weight = 50
print(bicycle.weight)
bicycle.SetMaxSpeed_Bicycle(20)
bicycle.show()
