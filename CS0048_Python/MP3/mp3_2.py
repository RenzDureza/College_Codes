def xyz_diff(first, second):
    count = len(first)
    while count > 0:
        for i in first:
            for j in second:
                if i == j:
                    break
            else:
                return first.index(i) + 1
        return -1
    count -= 1

first = input("Enter first string: ")
second = input("Enter second string: ")

print(xyz_diff(first, second))
