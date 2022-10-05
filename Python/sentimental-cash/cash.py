from cs50 import get_float


def Main():
    # Checks input
    while (True):
        cents = get_float("Change owed: ")
        if cents > 0.0:
            cents = cents * 100.0
            break

    # Calls function to calculate number of coins
    calculate(cents)


def calculate(cents):
    # Calculates quarters
    quarters = 0
    while cents >= 25:
        quarters += 1
        cents = cents - 25

    # Calculates dimes
    dimes = 0
    while cents >= 10:
        dimes += 1
        cents = cents - 10

    # Calculates nickels
    nickels = 0
    while cents >= 5:
        nickels += 1
        cents = cents - 5

    # Calculates pennies
    pennies = 0
    while cents >= 1:
        pennies += 1
        cents = cents - 1

    # Calls function to sum different coins and print result
    Coins(quarters, dimes, nickels, pennies)


# Sums different coins and prints result
def Coins(quarters, dimes, nickels, pennies):

    print(quarters + dimes + nickels + pennies)


Main()