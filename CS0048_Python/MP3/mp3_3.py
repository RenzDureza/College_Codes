
prime_numbers = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97]

def nextPrimeList(n):
    for i in prime_numbers:
        if  i > n:
            return i

while True:
    num = input("Enter a positive integer: ")
    if '.' in num:
        print("The input should be a whole number")
        continue

    intNum = int(num)

    if intNum <= 0:
        print("The number is not a positive integer")
        continue

    prime = nextPrimeList(intNum)
    if prime:
        print("The first prime greater than the number entered is: ", prime)
    else:
        print("No prime number found")
