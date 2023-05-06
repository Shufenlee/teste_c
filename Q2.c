#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
I= 1.
V= 5.
X= 10.
L= 50.
C= 100.
D= 500.
M= 1000.
*/

int Value(char c)
{
    int v = 0;
    switch (c)
    {
    case 'I':
        v = 1;
        break;

    case 'V':
        v = 5;
        break;

    case 'X':
        v = 10;
        break;

    case 'L':
        v = 50;
        break;

    case 'C':
        v = 100;
        break;

    case 'D':
        v = 500;
        break;

    case 'M':
        v = 1000;
        break;
    }
    return v;
}

int Calculate(char* number, int len)
{
    int i;

    int bIncrese = 1;
    int value = Value(number[len - 1]);

    if (len == 0)
    {
        return 0;
    }
    if (len == 1)
    {
        return Value(number[0]);
    }

    for (i = 2; i <= len ; i++)
    {
        if (Value(number[len - i]) > Value(number[len + 1 - i]))   // if right character is larger, add the value
        {
             bIncrese = 1;
             value += Value(number[len - i]);
        }
        else if (Value(number[len - i]) < Value(number[len + 1 - i])) // if right character is smaller, substract the value
        {
             bIncrese = 0;
             value -= Value(number[len - i]);
        }
        else   // equal: depends the previous one is adding or substracting
        {
            if (bIncrese)
            {
                value += Value(number[len - i]);
            }
            else
            {
                value -= Value(number[len - i]);
            }
        }
    }

    return value;
}

#define MAX_INPUT_CHAR 100
int main()
{
    char str[MAX_INPUT_CHAR ];
    int value = 0;

    printf("Enter a value :");
    gets(str);
    printf(str);

    value = Calculate(str, strlen(str));
    printf("\nvalue = %d", value);

    return 0;
}
