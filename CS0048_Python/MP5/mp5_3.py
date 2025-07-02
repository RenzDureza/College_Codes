num = [30, 7, 30, 2, 88, 44, 60, 40, 1, 53, 100, 72, 86,
       64, 40, 85, 3, 19, 62, 84, 17, 31, 95, 84, 99, 60,
       85, 74, 65, 38, 43, 80, 39, 70, 8, 21, 32, 68, 64,
       55, 88, 84, 49, 68, 70, 98, 21, 51, 3, 97
       ]

print("ALDRIN RENZ DUREZA")
print("FEU TECH")
print("Machine Problem - 3")

grater_than_ten = 0
less_than_ten = 0
for i in range(len(num)):
    if num[i] > 10:
        num[i] = 666
        grater_than_ten += 1
    else:
        less_than_ten += 1

print("OUTPUT is ", num)
print("Total equal values ", grater_than_ten)
print("Total not equal values ", less_than_ten)
