#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number_cc = get_long("Enter cc-number: \n");

    long count = 0;
    
    long n = number_cc;
    // This gets the length of the number
    while (n != 0)
    {
        n /= 10;
        count++;
    }
    // First sum the to be multiplied numbers
    long number1 = number_cc/10;
    long sum1 = 0;
    long digit1;
    do
    {
        digit1 = number1%10;
        number1 /= 100;
        long multi = digit1*2;

        if (multi >= 10)
        {
            sum1 += 1 + (multi%10);
        }
        else
        {
            sum1 += multi;
        }
    } while (number1 != 0);
    //Now sum the non multiplied numbers
    long number2 = number_cc;
    long sum2 = 0;
    long digit2;
    do
    {
        digit2 = number2%10;
        number2 /= 100;
        sum2 += digit2;
    } while (number2 != 0);
    long sum_tot = sum1 + sum2;
    
    // Check for sum
    if(sum_tot % 10 == 0)
    {
        // Check which company
        if (count == 15 && ((digit2 == 3 && digit1 == 4) || (digit2 == 3 && digit1 == 7)))
        {    
            printf("AMEX\n");
        }
        else if (count == 16 && (digit1 == 5 && (digit2 == 1 || digit2 == 2 || digit2 == 3 || digit2 == 4 || digit2 == 5)))
        {
            printf("MASTERCARD\n");
        }
        else if ((count == 13 || count == 16) && (digit1 == 4))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // Else, invalid
    else
    {
        printf("INVALID\n");
    }
}
