class Employee: #Common base class for all employees
    empcount=0 #Class variable. It can be accessed as Employee.empcount from inside the class or outside the class

    def __init__(self, name, salary):#first method __init__() is a special method, which is called class constructor or initialization method that Python calls when you create a new instance of this class.
        self.name = name
        self.salary = salary
        Employee.empcount +=1

    def displayCount(self):
        print("Total Employee %d" % Employee.empcount)

    def displayEmployee(self):
        print ("Name : ",self.name, ", Salary: ", self.salary)

#Creating Instance Objects
#To create instances of a class, you call the class using class name and pass in whatever arguments its __init__ method accepts.
emp1 = Employee("hari", 10000)#this would create  first object of Employee class
emp2 = Employee("sudhan", 20000)#this would create  first object of Employee class

#Accessing Attributes means access the variables and methods which is availabel in class
#You access the object's attributes using the dot operator with object. Class variable would be accessed using class name as follows
emp1.displayEmployee()
emp2.displayEmployee()
print( "Total Employee %d" % Employee.empcount)
        
class temp:
    print(Employee.empcount)
    def hari1(self,a,b):
        return a,b
obj = temp()
hari = obj.hari1(2,3)
print(hari)
