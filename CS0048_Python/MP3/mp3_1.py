def digitalRoot(num):
    sum = 0
    snum = str(num)
    for i in snum:
        sum += int(i)
    if sum < 10:
        return sum
    else:
        return digitalRoot(sum) 

num = input("Enter the number: ")
print(digitalRoot(num))
