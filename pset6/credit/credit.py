from cs50 import get_int
number = -1
while number < 0:
    number = get_int("Number: ")
# Luhn's algorithm
# checking if the credit card is valid
sum = number % 10
# determining the length of the number
s_num = str(number)
length = len(s_num)
for i in range(length):
    # determine all the numbers
    m = 10**(i+2)
    l = 10**(i+1)
    num = (number % m - number % l) / l
    # multiply every second by 2
    if i == 0 or i % 2 == 0:
        if (num > 4):
            num = (num * 2) % 10 + 1
        elif num <= 4:
            num = num * 2
    sum += num

# determing first numbers
start_number = number
for i in range(length - 2):
    start_number = int(start_number/10)
# checking the validity of the card
if sum % 10 == 0:
    if (length == 15) and (start_number == 34 or (start_number == 37)):
        print("AMEX")
    elif (length == 16) and (start_number >= 51 and start_number <= 55):
        print("MASTERCARD")
    elif (length == 13 or length == 16) and (start_number >= 40 and start_number < 50):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")

