#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

//----------------------------------
#ifndef NDEBUG
    #define yaissert(usl, text)                                  \
    {                                                            \
        if(!(usl))                                               \
        {                                                        \
            printf("\n" RED text "\n%s:%i" RESET, __FILE_NAME__, __LINE__);\
            abort();                                             \
        }                                                        \
    }
#else
    #define yaissert
#endif
//--------------------------------

typedef struct {
    int* ref;
    int X, Y;
    int len;
    int (*xytoD)(int X, int Y);
} Triangle_array;

bool             PrintHowItLooksLike (Triangle_array triangleArr);
bool             IsSpaceNext();
bool             InputArr(int* pX, int* pY);
bool             WhatToDoWithArray(Triangle_array*  ptriangleArr, bool isEsc);
bool             InputEdit(Triangle_array* ptriangleArr, bool isEsc);
bool             IsJob();
Triangle_array   CreateTriangleArr (int y, int x);
char             TAGetValue  (Triangle_array  triangleArr, int y, int x);//TriangleArrayGetValue
int              XYtoD (int x, int y);

//--------------------------------
int main()
{
    Triangle_array triangleArr = {};
    while(1)
    {
        int Y = 0, X = 0;
        bool isEsc = InputArr(&X, &Y);
        if(isEsc)
            break;

        triangleArr = CreateTriangleArr(Y, X);
        bool  isJob = 1;
        while(isJob)
        {
            isEsc = WhatToDoWithArray(&triangleArr, isEsc);
            if(isEsc)
                break;
            isJob = IsJob();
        }
        if(isEsc)
            break;
    }
    free(triangleArr.ref);
}
//----------------------------------



bool PrintHowItLooksLike (Triangle_array triangleArr)
{
    printf("\n\nThis is how this array look like\n\n");
    for(int y = 0; y < triangleArr.Y * 2 + 1; y++)
    {
        for(int x = 0; x < triangleArr.X; x++)
        {
            char a = 0;
            if(x * 2 - y < 0)
                a = TAGetValue(triangleArr, y - (1 + y / 2), x);
            else
                a = 'x';
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

char TAGetValue (Triangle_array triangleArr, int y, int x)
{
    if(triangleArr.ref == NULL || x > y)
        return ' ';

    int d = (((y + 1) * y) / 2) + x;
    yaissert(x >= 0, "x < 0");
    yaissert(y >= 0, "y < 0");
    yaissert(0 <= d && d < triangleArr.len, "Not in array\n");
    return (char) ((int) '0' + triangleArr.ref[d]);
}

Triangle_array CreateTriangleArr (int Y, int X)
{   
    Triangle_array triangleArr;
    yaissert(X >= 0, "X < 0");
    yaissert(Y >= 0, "Y < 0");

    triangleArr.X = X;
    triangleArr.Y = Y;
    triangleArr.len = (int) (((Y + 1) * Y + Y * 2)/2);
    triangleArr.xytoD = XYtoD;
    triangleArr.ref = (int*) calloc(triangleArr.len, sizeof(int));

    return triangleArr;
}

bool InputArr(int* pX, int* pY)
{
    int Y = 0, X = 0;
    bool isNotCorrect = 0;
    while(1)
    {
        isNotCorrect = 0;
        printf("Enter Y and X for array (or -1 and smth for escape):\n");
        int inputN  = scanf("%i %i", &Y, &X);
        bool isSpaceNext = IsSpaceNext();
        if(Y == -1)
        {
            return true;
        }

        if(X < 0 || Y < 0)
        {
            printf(RED "x and y must be positive or 0\n\n" RESET);
            isNotCorrect = 1;
        }

        if(X < Y)
        {
            printf(RED "x must to be >= y for triangle type array\n\n" RESET);
            isNotCorrect = 1;
        }

        if(inputN == 2 && isSpaceNext && !isNotCorrect)
        {
            break;
        }

        printf("Enter two number\n");
    }
    *pX = X;
    *pY = Y;
    return false;
}

bool IsSpaceNext()
{
    char tempc = ' ';
    while(tempc == ' ')
        tempc = (char) getchar();
    if(tempc == '\n')
        return true;
    return false;
}

bool WhatToDoWithArray(Triangle_array* ptriangleArr, bool isEsc)
{
    int choose = 0;
    if(isEsc)
        return true;
    while(1)
    {
        if(isEsc)
            return 1;
        printf("\n\nEnter  1 to edit value in array\n"
                   "Enter  2 to show array\n"
                   "Enter -1 to escape\n\n");
        scanf("%i", &choose);
        if(choose == -1)
            return 1;
        else if(IsSpaceNext())
            break;
    }
    if(choose == 1)
        isEsc = InputEdit(ptriangleArr, isEsc);
    else if(choose == 2)
        PrintHowItLooksLike(*ptriangleArr);
    return isEsc;
}

bool InputEdit(Triangle_array* ptriangleArr, bool isEsc)
{
    int y = 0, x = 0;
    while(1)
    {
        isEsc = InputArr(&x, &y);
        if(isEsc)
            return 1;
        if(ptriangleArr -> xytoD(x, y) >= ptriangleArr -> len)
            printf("Index not in array\n");
        else
            break;
    }
    int value = 0;
    while(1)
    {
        printf("Enter value\n");
        scanf("%i", &value);
        if(IsSpaceNext())
            break;
        printf(RED "Enter one number\n" RESET);
    }
    ptriangleArr -> ref[ptriangleArr -> xytoD(x, y)] = value;
    return isEsc;
}

int XYtoD (int x, int y)
{
    return (((y + 1) * y) / 2) + x;
}

bool IsJob()
{
    int choose = -1;
    while(1)
    {
        printf("Enter 1 to work with this array\n"
               "Enter 0 to create new\n");
        scanf("%i", &choose);
        if(IsSpaceNext() && (choose == 1 || choose == 0))
            break;
        printf(RED "Enter 0 or 1\n" RESET);
    }
    return choose;
}