#include<stdio.h>
#include<string.h>
#define phase2line(a,b) qsqrt((a)*(a) + (b)*(b) + (a)*(b))
typedef unsigned short uint16_t;
int qsqrt(int n);
int str2dec(char *str);

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Not enough items.\n");
        return 0;
    }
    int n1, n2;
    n1 = str2dec(argv[1]);
    n2 = str2dec(argv[2]);
    printf("Line voltage is %d.\n", phase2line(n1, n2));
}
int qsqrt(int n)
{
    if (n < 0)
        return 0;
    int ret = n >> 1;
    while (ret - n / ret > 0)
        ret = (n / ret + ret) >> 1;
    return ret;
}

int isNum(char *str){
    int len = strlen(str), i;
    if (!(str[0] > '0' || str[0] < '9' || str[0] == '+' || str[0] == '-'))
        return 0;
    for (i = 1; i < len; i++)
        if (str[i] < '0' || str[i] > '9')
            return 0;
    return 1;
}

int str2dec(char *str)
{
    if (!isNum(str)){
        printf("'%s' is not a number.\n", str);
        return 0;
    }
    int len = strlen(str), i = 0, ret = 0;
    if (str[i] == '-' || str[i] == '+')  
        i++;
    for (; i < len; i++){
        ret *= 10;
        ret += str[i] - '0';
    }
    if (str[0] == '-')
        return -ret;
    else
        return ret;
}