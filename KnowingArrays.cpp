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
            printf("\n" text "\n%s:%i", __FILE_NAME__, __LINE__);\
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
    int (*xytoD)(int, int);
} Triangle_array;

bool             PrintHowItLooksLike (Triangle_array triangleArr);
bool             IsSpaceNext();
bool             InputArr(int* pX, int* pY);
bool             InputJob(Triangle_array*  triangleArr, bool isEsc);
bool             InputEdit(Triangle_array* triangleArr, bool isEsc);
bool             IsJob();

Triangle_array   CreateTriangleArr (int y, int x);

char             TAGetValue  (Triangle_array  triangleArr, int y, int x);//TriangleArrayGetValue
void             TAEditValue (Triangle_array* triangleArr, int y, int x, int value);//TriangleArrayEditValue

int              XYtoD (int x, int y);

//--------------------------------
int main()
{
    while(1)
    {
        int Y = 0, X = 0;
        bool isEsc = InputArr(&X, &Y);
        Triangle_array triangleArr = {.ref = NULL, .X = X, .Y = Y, .len = 0};
        triangleArr = CreateTriangleArr(Y, X);
        bool isJob = 1;
        while(isJob)
        {
            isEsc = InputJob(&triangleArr, isEsc);
            isJob = IsJob();
        }
        if(isEsc)
            break;
    }
    

    // TAEditValue(triangleArr1 1, 1, 1);
    // TAEditValue(triangleArr, 5, 5, 1);
    // PrintHowItLooksLike(triangleArr1,  5, 10);
}
//----------------------------------






bool PrintHowItLooksLike (Triangle_array triangleArr)
{
    printf("\n\nThis is how this array look like\n\n");
    for(int y = 0; y < triangleArr.Y * 2 + 1; y++)
    {
        for(int x = 0; x < triangleArr.X; x++)
        {
            char a = (x * 2 - y < 0) ? TAGetValue(triangleArr, y - (1 + y / 2), x) : 'x'; 
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
    {
        return ' ';
    }

    int d = (((y + 1) * y) / 2) + x;
    yaissert(x >= 0, "x < 0");
    yaissert(y >= 0, "y < 0");
    yaissert(0 <= d && d <= triangleArr.len, "Not in array\n");
    return (char) ((int) '0' + triangleArr.ref[d]);
}

Triangle_array CreateTriangleArr (int Y, int X)
{   
    Triangle_array triangleArr = {.ref = NULL, .len = 0};
    yaissert(X >= 0, "X < 0");
    yaissert(Y >= 0, "Y < 0");
    triangleArr.X = X;
    triangleArr.Y = Y;
    triangleArr.len = (((Y + 1) * Y + Y * 2)/2);
    triangleArr.ref = (int*) calloc(triangleArr.len, sizeof(int));
    triangleArr = {.xytoD = XYtoD};

    return triangleArr;
}

void TAEditValue (Triangle_array* triangleArr, int y, int x, int value)
{
    y--;
    x--;
    triangleArr -> ref[((y + 1) * y + y * 2)/2] = value;
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
            break;
        }

        if(X <= 0 || Y <= 0)
        {
            printf(RED "x and y must be positive\n\n" RESET);
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
    if(Y == 'E') return true;
    *pX = X;
    *pY = Y;
    return false;
}

bool IsSpaceNext()
{
    char tempc = ' ';
    while(tempc == ' ')
        tempc = getchar();
    if(tempc == '\n')
        return true;
    return false;
}

bool InputJob(Triangle_array* triangleArr, bool isEsc)
{
    int choose = 0;
    if(isEsc == 1)
        return 1;
    while(1)
    {
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
        isEsc = InputEdit(triangleArr, isEsc);
    else if(choose == 2)
        PrintHowItLooksLike(*triangleArr);
    return isEsc;
}

bool InputEdit(Triangle_array* triangleArr, bool isEsc)
{
    int choose = 0;
    int y = 0, x = 0;
    while(1)
    {
        InputArr(&x, &y);
        if(triangleArr -> xytoD(x, y) >= triangleArr -> len)
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
    triangleArr -> ref[triangleArr -> xytoD(x, y)] = value;
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