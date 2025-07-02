def main():
    while True:
        print("\nMENU")
        print("1. Convert an integer to a Roman numeral")
        print("2. Convert Roman numerals to an integer")
        print("3. Exit")
        choice = input("Enter your choice: ")

        match choice:
            case "1":
                num = int(input("Enter Integer: "))
                print("Output in Roman numerals is: " + int_to_roman(num))
            case "2":
                num = input("Enter Roman numerals: ").upper()
                print("Output in Integer is: " + str(roman_to_int(num)))
            case "3":
                print("Exiting...")
                break
            case _:
                print("Invalid choice. Please try again.")

def print_roman(num, letter):
    return letter * num

def int_to_roman(num):
    res = ""

    thnum = num // 1000
    res += print_roman(thnum, "M")

    hnum = (num % 1000) // 100
    if hnum == 9:
        res += "CM"
    elif hnum >= 5:
        res += "D" + print_roman(hnum - 5, "C")
    elif hnum == 4:
        res += "CD"
    else:
        res += print_roman(hnum, "C")

    tnum = (num % 100) // 10
    if tnum == 9:
        res += "XC"
    elif tnum >= 5:
        res += "L" + print_roman(tnum - 5, "X")
    elif tnum == 4:
        res += "XL"
    else:
        res += print_roman(tnum, "X")

    onum = num % 10
    if onum == 9:
        res += "IX"
    elif onum >= 5:
        res += "V" + print_roman(onum - 5, "I")
    elif onum == 4:
        res += "IV"
    else:
        res += print_roman(onum, "I")

    return res

def roman_to_int(s):
    roman_values = {
        'I': 1, 'V': 5, 'X': 10,
        'L': 50, 'C': 100,
        'D': 500, 'M': 1000
    }

    total = 0
    prev_value = 0

    for char in reversed(s):
        value = roman_values.get(char, 0)
        if value == 0:
            return "Invalid Roman numeral"
        if value < prev_value:
            total -= value
        else:
            total += value
        prev_value = value

    return total

if __name__ == "__main__":
    main()
