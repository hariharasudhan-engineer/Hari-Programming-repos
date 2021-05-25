class Demo():
    print("Welcome")
    def __init__(sef,name,age,gender):
        sef.name = name
        sef.age = age
        sef.gender = gender
    def display(abc):
        print("Name is:",abc.name)
        print("Age is:",abc.age)
        print("Gender is:",abc.gender)

obj = Demo("Vijay",21,"Male")
obj.display()
