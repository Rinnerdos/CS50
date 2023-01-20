from cs50 import get_int

while True:
    h = get_int("Input height of the pyramids.\n")
    if (0 < h < 9):
        break

for i in range(1, h+1):
    for j in range(h-i, 0, -1):
        print(" ", end="")
    for k in range(0, i):
        print("#", end="")
    print("  ", end="")
    for k in range(0, i):
        print("#", end="")
    print()
