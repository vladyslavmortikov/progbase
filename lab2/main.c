#include <stdio.h>    // Для друку в термінал
#include <math.h>     // Для математичних функцій
#include <stdlib.h>   // Деякі додаткові функції
#include <progbase.h> // Спрощений ввід і вивід даних у консоль

int main()
{
    const float xmin = -10.0;
    const float xmax = 10.0;
    const float xstep = 0.5;
    float x = xmin;
    float y;
    while (x <= xmax)
    {
        if ((x >= -4.5 && x < -1) || (x > 1 && x <= 4.5))
        {
            y = tan(pow(x, 2)) + sin(pow(2 * x, 2));
            printf("Y is %f \n", y);
        }
        else if (x != 1)
        {
            y = (pow(x, 2) - 5) / (x - 1);
            printf("Y is %f \n", y);
        }
        else
            printf("ERROR! X=1 - invalid data!\n");
        x += xstep;
    }
    return 0;
}