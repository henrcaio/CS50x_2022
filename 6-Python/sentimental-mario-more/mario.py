from cs50 import get_int


def Main():
    # Checks input for positive integer between 1 and 8
    while (True):
        n = get_int("Height: ")
        # If the input passes the test, calls Brick function and break out of the loop
        if n > 0 and n < 9:
            Bricks(n)
            break


# Calls Bricks function to print the pyramid
def Bricks(n):
    for i in range(1, n + 1):
        for j in range(n, i, - 1):
            print(" ", end="")
        print("#" * i, "", "#" * i)


Main()