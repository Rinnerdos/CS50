from cs50 import get_string

ccNumb = get_string("Enter cc-number: \n")

count = 0
sum1 = 0

# First sum the to be multiplied digits
for i in range(len(ccNumb)-2, -1, -2):
    count += 1
    number1 = int(ccNumb[i])*2
    
    # If the to be multiplied number is > 10, add digits seperately
    if number1 >= 10:
        sum1 += 1 + number1 % 10
    else:
        sum1 += number1
  
sum2 = 0

# Then sum the non-multiplied (remainging) digits
for i in range(len(ccNumb)-1, -1, -2):
    count += 1
    sum2 += int(ccNumb[i])
    
sumTot = sum1 + sum2

# Then check which company cc number belongs to, or if invalid
if sumTot % 10 == 0:
    if (count == 15 and (ccNumb[0] == "3" and (ccNumb[1] == "4" or "7"))):
        print("AMEX")
    elif (count == 16 and (ccNumb[0] == "5" and (ccNumb[1] == "1" or "2" or "3" or "4" or "5"))):
        print("MASTERCARD")
    elif (count == 13 or 16) and ccNumb[0] == "4":
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")