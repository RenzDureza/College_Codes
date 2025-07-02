num = [63, 52, 10, 42, 32, 17, 60, 45, 47, 39, 71, 55, 41, 95, 70, 48, 42, 32, 13, 35]

print("(a) Print the list:")
print("   ", *num)

print("(b) Print the average of the elements in the list.")
sum = 0
for i in num:
    sum += i
ave = sum/len(num)
print("   ", ave)

print("Print the largest and smallest values in the list.")
print("    Largest: ", max(num))
print("    Smallest: ", min(num))

print("(d) Print the second largest and second smallest entries in the list.")
num.sort()
print("    2nd Largest: ", num[-2])
print("    2nd Smallest: ", num[-19])

print("(e) Print how many even numbers are in the list.")
even_count = 0
for i in num:
    if i % 2 == 0:
        even_count += 1
print("   ", even_count)

print("(f) Print how many odd numbers are in the list.")
odd_count = 0
for i in num:
    if i % 1 == 0:
        odd_count += 1
print("   ", odd_count)

