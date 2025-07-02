letters = ['a', 'b','c', 'd', 'e', 'f',
           'g', 'h', 'i', 'j', 'k', 'l',
           'm', 'n', 'o', 'p', 'q', 'r',
           's','t', 'u', 'v', 'w', 'x',
           'y', 'z']

print("ALDRIN RENZ DUREZA")
print("FEU TECH")
print("Machine Problem - 4")

for i in range(1, len(letters)):
    letters[i] *=  (i + 1)

print("OUTPUT is ", letters)
