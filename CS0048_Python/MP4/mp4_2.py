import math

class Circle:
    def __init__(self, radius):
        self.radius = radius

    def get_area(self):
        return math.pi * (self.radius ** 2)

    def get_perimeter(self):
        return (2 ) * math.pi * ( self.radius )

while True:
    radius = input("Enter radius: ")

    if '.' in radius:
        print("The input should be a whole number")
        continue
    
    if 'exit' in radius:
        print("Bye")
        break

    int_radius = int(radius)

    if int_radius <= 0:
        print("The number is not a positive integer")
        continue

    new_circle = Circle(int_radius)
    print("The answer is: ", new_circle.get_area())
    print("Here is the Answer: ", new_circle.get_perimeter())
