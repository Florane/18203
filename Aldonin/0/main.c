#include "stdio.h"
#include "string.h"
//#include "translate.h"

int atoi(char c)
{
    if(c <= 'F' && c >= 'A')
        return c-'A'+10;
    if(c <= '9' && c >= '0')
        return c-'0';
    return -1;
}

char itoa(int i)
{
    if(i <= 9 && i >= 0)
        return i+'0';
    else if(i <= 15)
        return i+'A';
    return -1;
}

int exp(int a, int b)
{
    int c = a;
    for(int i = 1;i < b;i++)
    {
        a *= c;
    }
    return a;
}

int failSafe(int b1, int b2, char* number)
{
    if(b1 < 2 || b1 > 16)
        return 1;
    if(b2 < 2 || b2 > 16)
        return 2;
    for(int i = 0;number[i] != 0;++i)
    {
        int c = atoi(number[i]);
        if(c > b2)
            return 3;
        if(c == -1 && number[i] != '.')
            return 4;
        if(i > 13)
            return 5;
    }
    return 0;
}

double numToDouble(int base, char* number)
{
    double ret = 0;
    int ifDot = -1;
    for(int i = 0;number[i] != 0;++i)
    {
        char c = number[i];
        if(c == '.')
        {
            ifDot = i;
            continue;
        }
        double a = atoi(c);
        if(ifDot == -1)
        {
            ret *= base;
            ret += a;
        }
        else
        {
            ret += a/(exp(base,i-ifDot));
        }
    }
    return ret;
}

char* intToNum(int base,int number)
{
    char buffer[255];
    int size = 0;
    for(int i = 0;number != 0;i++,size++)
    {
        int c = number % base;
        printf("test %d %d\n",i,c);
        buffer[i] = itoa(c);
        number /= base;
    }
    printf("size = %d\n",size);
    printf("test = %s\n",buffer);
    char output[size];
    for(int i = 0;i < size;i++)
        output[i] = buffer[i];
    printf("  %s\n",output);
    return output;
}

char* floatToNum(int base,double number)
{
    char output[12];
    for(int i = 0;i < 12;i++)
    {
        int c = number*base;
        number = (number*base)-c;
        output[i] = itoa(c);
    }
    printf("  %s\n",output);
    return output;
}

char* doubleToNum(int base,double number)
{
    char output[255];
    int n = number;
    char* output1 = intToNum(base, n);
    char* output2 = floatToNum(base, number);
    printf("  %s\n",output);

    return output;
}

int main()
{
    int b1, b2;
    char enter[255];
    scanf("%d %d",&b1,&b2);
    scanf("%s",enter);
    int test = failSafe(b1, b2, enter);
    if(test != 0)
        return test;

    double d = numToDouble(b1, enter);
    char* c = doubleToNum(b2, d);
    printf("%s",c);

    return 0;
}
