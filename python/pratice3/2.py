
class Employee:
    name = ''
    numbers = '202026'
    salary = 11000
    work_time = 2

    def __init__(self, Name, Number, Salary):
        self.name = Name
        self.numbers = Number
        self.salary = Salary

    def Pay(self):
        print(self.work_time * self.salary)

    def Show(self):
        print(self.name)
        print(self.numbers)
        print(self.salary)


class Manager(Employee):
    salary = 10000

    def Show(self):
        print(self.name)
        print(self.numbers)
        print(self.salary)

    def Pay(self):
        print(self.work_time * self.salary + 2000)


class Salesman(Employee):
    salary = 4000

    def Show(self):
        print(self.name)
        print(self.numbers)
        print(self.salary)

    def Pay(self):
        print(self.work_time * self.salary)


saleman = Salesman('ycj','2020212326',11000)
manager = Manager('王麻子','2020212336',1000)
saleman.Show()
saleman.Pay()
manager.Show()
manager.Pay()
