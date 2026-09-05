#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#ifndef NDEBUG

#define yaissert(usl, text)                       \
{                                                 \
    if(!(usl))                                    \
    {                                             \
        printf("text\n%s:%s", __FILE__, __LINE__);\
        abort();                                  \
    }                                             \
}

#else
    #define yaissert
#endif

bool    PrintHowItLooksLike (int* treangleArr, int Y, int X);

int*    CreateTreangleArr (int* treangleArr, int y, int x);

char     TAGetValue (int* treangleArr, int y, int x);//TreangleArrayGetValue
void    TAEditValue (int* treangleArr, int y, int x, int value);//TreangleArrayEditValue

int main()
{
    PrintHowItLooksLike(NULL, 10, 10);
    int treangleArr1[] = {};
    CreateTreangleArr(treangleArr1, 5, 10);
    TAEditValue(treangleArr1, 1, 1, 1);
    TAEditValue(treangleArr1, 5, 5, 1);
    PrintHowItLooksLike(treangleArr1, 5, 10);
    return 1;
}

bool PrintHowItLooksLike (int* treangleArr, int Y, int X)
{
    printf("\n\nThis is how this array look like\n\n");
    for(int y = 0; y < Y * 2 + 1; y++)
    {
        for(int x = 0; x < X; x++)
        {
            char a = (x * 2 - y < 0) ? TAGetValue(treangleArr, y - (1 + y / 2), x) : 'x'; 
            if(y % 2 == 0)
                printf("+-");
            else
                printf("|%c", a);
        }

        if(y % 2 == 0)
            printf("+\n");
        else
            printf("|\n");
    }
    return 1;
}

char TAGetValue (int* treangleArr, int y, int x)
{
    if(treangleArr == NULL || x > y)
    {
        return ' ';
    }
    return (char) ('0' + treangleArr[(((y + 1) * y) / 2) + x]);
}

int* CreateTreangleArr (int* treangleArr, int y, int x)
{
    if(x < y)
    {
        printf("x must to be >= y for treangle type array\n");
        return NULL;
    }

    for(int d = 0; d < ((y + 1) * y + y * 2)/2; d++)
    {
        treangleArr[d] = 0;
    }
    return treangleArr;
}

void TAEditValue (int* treangleArr, int y, int x, int value)
{
    y--;
    x--;
    treangleArr[((y + 1) * y + y * 2)/2] = value;
}

//FIX 
//Add yaissert for y < 0 and x < 0 