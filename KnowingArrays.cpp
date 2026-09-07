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

typedef struct {
    int* ref;
    int len;
} Triangle_array;

bool             PrintHowItLooksLike (Triangle_array triangleArr, int Y, int X);

Triangle_array   CreateTriangleArr (int y, int x);

char             TAGetValue  (Triangle_array triangleArr, int y, int x);//TriangleArrayGetValue
void             TAEditValue (Triangle_array triangleArr, int y, int x, int value);//TriangleArrayEditValue

int main()
{
    Triangle_array triangleArr1 = {.ref = NULL, .len = 0};
    triangleArr1 = CreateTriangleArr(5, 10);

    TAEditValue(triangleArr1, 1, 1, 1);
    TAEditValue(triangleArr1, 5, 5, 1);
    PrintHowItLooksLike(triangleArr1,  5, 10);
}

bool PrintHowItLooksLike (Triangle_array triangleArr, int Y, int X)
{
    printf("\n\nThis is how this array look like\n\n");
    for(int y = 0; y < Y * 2 + 1; y++)
    {
        for(int x = 0; x < X; x++)
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
    yaissert(0 <= d && d <= triangleArr.len, "Not in array\n");
    return (char) ((int) '0' + triangleArr.ref[d]);
}

Triangle_array CreateTriangleArr (int Y, int X)
{   
    Triangle_array triangleArr = {.ref = NULL, .len = 0};

    if(X <= 0 || Y <= 0)
    {
        printf("x and y must be positive");
        return triangleArr;
    }
    if(X < Y)
    {
        printf("x must to be >= y for triangle type array\n");
        return triangleArr;
    }
    triangleArr.len = (((Y + 1) * Y + Y * 2)/2);
    triangleArr.ref = (int*) calloc(triangleArr.len, sizeof(int));

    return triangleArr;
}

void TAEditValue (Triangle_array triangleArr, int y, int x, int value)
{
    y--;
    x--;
    triangleArr.ref[((y + 1) * y + y * 2)/2] = value;
}

//FIX 
//Add yaissert for y < 0 and x < 0 