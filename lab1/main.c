// Компілювати за допомогою:
// gcc main.c -lprogbase -lm

#include <stdio.h>    // Для друку в термінал
#include <math.h>     // Для математичних функцій
#include <stdlib.h>   // Деякі додаткові функції
#include <progbase.h> // Спрощений ввід і вивід даних у консоль

int main()
{
    float x;
    float y;
    float z;
    float a0;
    float a1;
    float a2;

    printf("Please, enter your 'X' BE ATTENTION! - X є (-∞;0)U(0;+∞) here - ");
    scanf("%f", &x);

    printf("Please, enter your 'Y' here - ");
    scanf("%f", &y);

    printf("Please, enter your 'Z' here - ");
    scanf("%f", &z);

    a0 = pow(x, y + 1) / pow((x + y), 1 / z);
    a1 = 7 * y + (z / x);
    a2 = sqrt(fabs((cos(y) / sin(x)) + 2));

    float a = a0 + a1 + a2;
    printf("x = %.10f", x);
    puts("");

    printf("y = %.10f", y);
    puts("");

    printf("z = %.10f", z);
    puts("");

    printf("a0 = %.10f", a0);
    puts("");

    printf("a1 = %.10f", a1);
    puts("");

    printf("a2 = %.10f", a2);
    puts("");

    printf("The a is %.10f! Thank you for using this program! ♥", a);
    puts("");
    // Кінець програми
    return 0;
}