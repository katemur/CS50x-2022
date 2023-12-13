from cs50 import get_float
dollars = -1.0
while dollars < 0:
    dollars = get_float("Change owed: ")
# converting dollars to cents
cents = round(dollars * 100)
coins = 0
# cheking for quaters
while cents >= 25:
    cents -= 25
    coins += 1
# checking for dimes
while cents >= 10:
    cents -= 10
    coins += 1
# checking for nickels
while cents >= 5:
    cents -= 5
    coins += 1
# checking for pennies
while cents > 0:
    cents -= 1
    coins += 1
# print the result
print(coins)