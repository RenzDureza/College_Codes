class Rectangle:
    def __init__(self, length, width):
        self.length = length
        self.width = width
    def get_area(self):
        return self.width * self.length

while True:
    length = input("Enter length value: ")
    width = input("Enter width value: ")

    if ('.' in length) and ('.' in width):
        print("The input should be a whole number")
        continue

    if ('exit' in length) or ('exit' in width):
        print("Bye")
        break

    int_length = int(length)
    int_width = int(width)

    if int_length <= 0 or int_width <= 0:
        print("The number is not a positive integer")
        continue
    
    new_rectangle = Rectangle(int_length, int_width)
    
    print(new_rectangle.get_area())




