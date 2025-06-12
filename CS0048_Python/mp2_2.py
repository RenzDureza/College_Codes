magnitude = float(input("Enter an earthquake magnitude: "))

if (magnitude < 2.0):
    print("This earthquake is classified as Micro")
elif (magnitude < 3.0):
    print("This earthquake is classified as Very minor") 
elif (magnitude < 4.0):
    print("This earthquake is classified as Minor")
elif (magnitude < 5.0):
    print("This earthquake is classified as Light")
elif (magnitude < 6.0):
    print("This earthquake is classified as Moderate")
elif (magnitude < 7.0):
    print("This earthquake is classified as Strong")
elif (magnitude < 8.0):
    print("This earthquake is classified as Major")
elif (magnitude < 10.0):
    print("This earthquake is classified as Great")
elif (magnitude >= 10.0):
    print("This earthquake is classified as Meteoric")
