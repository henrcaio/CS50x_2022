from cs50 import get_string


def Main():

    card_number = check_input()
    number_length = len(card_number)

    if checksum(card_number):
        check_processor(card_number, number_length)


# Checks input from user for numeric digits only and number length
def check_input():
    while (True):
        card_number = get_string("Type your credit card number: ")
        if card_number.isdigit():
            if len(card_number) >= 10:
                break
    return card_number


def checksum(card_number):
    # Creates an empty list to allocate card numbers
    numbers = []
    count = 0

    # Inserts numbers
    for c in card_number:
        numbers.insert(count, c)
        count += 1

    # Creates new list with reversed card number
    numbers = list(reversed(numbers))
    sum = 0

    # Iterates through every other number second-to-last
    for number in numbers[1::2]:
        digit = (int(number) * 2)
        if digit >= 10:
            sum += (digit % 10)
            digit = int(str(digit)[0:1:1])
            sum += digit
        else:
            sum += digit

    # Iterates through remaining numbers
    for number in numbers[::2]:
        digit = int(number)
        sum += digit

    # Checksum
    if sum % 10 == 0:
        return True
    else:
        invalid()


# Checks processor
def check_processor(card_number, number_length):
    # Checks for AMEX
    if number_length == 15:
        if int(card_number[:2]) == 34 or int(card_number[:2]) == 37:
            print("AMEX")
        else:
            invalid()

    # Checks for Mastercard and Visa
    elif number_length == 16:
        if int(card_number[:2]) >= 51 and int(card_number[:2]) <= 55:
            print("MASTERCARD")
        elif int(card_number[:1]) == 4:
            print("VISA")
        else:
            invalid()

    # Checks for Visa
    elif number_length == 13 and int(card_number[:1]) == 4:
        print("VISA")

    else:
        invalid()


# In case card checks as invalid throughout the program
def invalid():
    print("INVALID")
    return 1


Main()