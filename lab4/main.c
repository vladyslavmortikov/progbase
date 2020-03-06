#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <progbase.h>
#include <progbase/console.h>
#include <time.h>
#include <stdbool.h>

int getColor(char colorCode);

const char image[28][28] = {
    {0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1},
    {0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1},
    {0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1},
    {0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1},
    {0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1},
    {0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1},
    {0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF},
    {0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0x0, 0x0, 0x0, 0x0, 0x0, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF},
    {0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF},
    {0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x0, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF},
    {0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0x0, 0x0, 0x7, 0x0, 0x0, 0x0, 0x7, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF},
    {0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0x0, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x1, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF},
    {0xF, 0xF, 0xF, 0xF, 0xF, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF},
    {0xF, 0xF, 0xF, 0xF, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF},
    {0xF, 0xF, 0xF, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF},
    {0xF, 0x7, 0x7, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x7, 0x7, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF},
    {0xF, 0x7, 0x7, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x7, 0x7, 0x7, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF},
    {0xF, 0xF, 0xF, 0xF, 0xF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x1, 0x0, 0x0, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF},
    {0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xE, 0xE},
    {0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0x0, 0x0, 0xF, 0xF, 0xF, 0xF, 0x0, 0x0, 0xF, 0x1, 0x0, 0x0, 0xF, 0xF, 0xF, 0xF, 0xF, 0xE, 0xE, 0xE, 0xE},
    {0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0x0, 0x0, 0x0, 0xF, 0xF, 0xF, 0x0, 0x0, 0x0, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE},
    {0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE},
    {0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1},
    {0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1},
    {0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1},
    {0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1},
    {0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1},
    {0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1}};

int main()
{
    srand(time(0));

    bool isMainMenuRunning = true;

    while (isMainMenuRunning)
    {
        Console_clear();
        puts("1. Array ");
        puts("2. Matrix");
        puts("0. Quit  ");

        char mainMenuUserInput = Console_getChar();

        switch (mainMenuUserInput)
        {

        case '0':
        {
            isMainMenuRunning = false;
            break;
        }

        case '1':
        {

            Console_clear();
            int N = 0;
            printf("Enter array length: ");
            scanf("%d", &N);

            if (N <= 0)
            {
                Console_setCursorAttribute(FG_RED);
                printf("Please, enter n > 0 & n < 100\n");
                Console_reset();
                break;
            }
            int array[N];

            for (int i = 0; i < N; i++)
            {
                array[i] = 0;
            }
            bool isSubmenu1Running = true;
            while (isSubmenu1Running)
            {
                Console_clear();
                puts("\nThis is ARRAY submenu!");
                puts("\nArray: ");
                for (int i = 0; i < N; i++)
                {
                    printf(" %5.1i |", array[i]);
                }
                puts("");

                puts("\n\n1) To fill the array with random numbers from L to H.              ");
                puts("2) To reset all elements of the array.                                 ");
                puts("3) To find the maximum array element and its index.                    ");
                puts("4) To output the sum of positive elements of the array.                ");
                puts("5) To swape the values of the maximum and minimum elements of the array.");
                puts("6) To increase all elements of the array by the entered number.        ");

                puts("\n\n0. <- Back");
                printf("> Enter your option: ");

                char submenu1Input = Console_getChar();
                printf("You entered: '%c'\n", submenu1Input);

                switch (submenu1Input)
                {

                case '0':

                    isSubmenu1Running = false;
                    break;

                case '1':
                {
                    int l = 0;
                    int h = 0;

                    printf("Enter L (min): ");
                    scanf("%i", &l);
                    puts(" ");

                    printf("Enter H (max): ");
                    scanf("%i", &h);
                    puts(" ");

                    if (h >= l)
                    {
                        for (int i = 0; i < N; i++)
                        {
                            array[i] = rand() % (h - l + 1) + l;
                        }
                    }
                    break;
                }

                case '2':

                    for (int i = 0; i < N; i++)
                    {
                        array[i] = 0;
                    }
                    break;

                case '3':
                {
                    int index = 0;
                    int max = array[0];
                    for (int i = 1; i < N; i++)
                    {
                        if (max < array[i])
                        {
                            max = array[i];
                            index = i;
                        }
                    }
                    printf("The max is %i, its index is %i!", max, index);
                    break;
                }
                case '4':
                {
                    int sum = 0;
                    for (int i = 0; i < N; i++)
                    {
                        if (array[i] > 0)
                        {
                            sum = sum + array[i];
                        }
                    }
                    printf("The sum is %i!", sum);
                    break;
                }
                case '5':
                {
                    int maxEl = array[0];
                    int minEl = array[0];
                    int indexMaxEl = 0;
                    int indexMinEl = 0;
                    for (int i = 1; i < N; i++)
                    {
                        for (int f = 1; f < N; f++)
                        {

                            if (maxEl < array[i])
                            {
                                maxEl = array[i];
                                indexMaxEl = i;
                            }

                            if (minEl > array[f])
                            {
                                minEl = array[f];
                                indexMinEl = f;
                            }
                        }
                    }
                    array[indexMaxEl] = minEl;
                    array[indexMinEl] = maxEl;
                    break;
                }
                case '6':
                {
                    int number = 0;
                    printf("Enter your number here - ");
                    scanf("%i", &number);
                    for (int i = 0; i < N; i++)
                    {
                        array[i] += number;
                    }
                }
                default:
                    break;
                }
            }
            break;
        }

        case '2':
        {
            Console_clear();
            bool isSubmenu2Running = true;

            int n = 0;
            int m = 0;

            printf("Enter your N here (strings): ");
            scanf("%i", &n);

            printf("Enter your M here (columns): ");
            scanf("%i", &m);

            if (n <= 0 || m <= 0)
            {
                Console_setCursorAttribute(FG_RED);
                printf("Please, enter n > 0 & n < 100\n");
                Console_reset();
                break;
            }

            int matrix[n][m];

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    matrix[i][j] = 0;
                }
            }

            while (isSubmenu2Running)
            {

                Console_clear();

                puts("\nThis is MATRIX submenu!");

                puts("\nMatrix: ");

                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < m; j++)
                    {
                        printf(" %5.1i |", matrix[i][j]);
                    }
                    puts(" ");
                }

                puts("\n\n1) To fill the matrix with random numbers from L to H.");
                puts("2) To reset all elements of the array.");
                puts("3) To find the minimal element and its indexes (i and j).");
                puts("4) To find the sum of line items for a given index.");
                puts("5) To swape places of the maximum and minimum elements of the array.");
                puts("6) To change the value of an item by specified indexes to a specified one.");

                puts("\n\n0. <- Back");
                printf("> Enter your option: ");

                char submenu2Input = Console_getChar();
                printf("You entered: '%c'\n", submenu2Input);

                switch (submenu2Input)
                {

                case '0':
                {

                    isSubmenu2Running = false;
                    break;
                }
                case '1':
                {

                    int a = 0;
                    int b = 0;

                    printf("Enter L (min): ");
                    scanf("%i", &a);
                    puts(" ");

                    printf("Enter H (max): ");
                    scanf("%i", &b);
                    puts(" ");

                    for (int i = 0; i < n; i++)
                    {
                        for (int j = 0; j < m; j++)
                        {
                            matrix[i][j] = rand() % (b - a + 1) + a;
                        }
                    }
                    break;
                }
                case '2':
                {
                    for (int i = 0; i < n; i++)
                    {
                        for (int j = 0; j < m; j++)
                        {
                            matrix[i][j] = 0;
                        }
                    }
                }
                case '3':
                {
                    int indexI = 0;
                    int indexJ = 0;
                    int min = matrix[0][0];
                    for (int i = 1; i < n; i++)
                    {
                        for (int j = 1; j < m; j++)
                        {
                            if (min > matrix[i][j])
                            {
                                min = matrix[i][j];
                                indexI = i;
                                indexJ = j;
                            }
                        }
                    }
                    printf("The min is %i, its index is [%2.1i][%2.1i]!", min, indexI, indexJ);
                    break;
                }
                case '4':
                {
                    int sum = 0;
                    int i = 0;
                    printf("> I want to use this line - ");
                    scanf("%i", &i);

                    if (i >= 0 && i < n)
                    {
                        for (int j = 0; j < m; j++)
                        {
                            sum = sum + matrix[i][j];
                        }
                        printf("The sum of elements when i = %i is %i", i, sum);
                    }
                    else
                        printf("Please, print another i here");
                    break;
                }
                case '5':
                {
                    int maxEl = matrix[0][0];
                    int minEl = matrix[0][0];
                    int indexIMaxEl = 0;
                    int indexJMaxEl = 0;
                    int indexIMinEl = 0;
                    int indexJMinEl = 0;

                    for (int i = 1; i < n; i++)
                    {
                        for (int j = 1; j < m; j++)
                        {
                            for (int g = 1; g < n; g++)
                            {
                                for (int f = 1; f < m; f++)
                                {

                                    if (maxEl < matrix[i][j])
                                    {
                                        maxEl = matrix[i][j];
                                        indexIMaxEl = i;
                                        indexJMaxEl = j;
                                    }

                                    if (minEl > matrix[g][f])
                                    {
                                        minEl = matrix[g][f];
                                        indexIMinEl = g;
                                        indexJMinEl = f;
                                    }
                                }
                            }
                        }
                    }
                    matrix[indexIMaxEl][indexJMaxEl] = minEl;
                    matrix[indexIMinEl][indexJMinEl] = maxEl;
                    break;
                }
                case '6':
                {
                    int i = 0;
                    int j = 0;
                    float indexValue = 0;

                    printf("Enter your i here - ");
                    scanf("%i", &i);

                    printf("Enter your j here - ");
                    scanf("%i", &j);

                    if (i >= 0 && i < n && j >= 0 && j < m)
                    {
                        printf("\n\nelement[%i][%i] = %i", i, j, matrix[i][j]);
                        puts("\nWhat value do you want?");
                        printf("\n\n> I want its ");
                        scanf("%f", &indexValue);
                        matrix[i][j] = indexValue;
                    }
                    else
                        printf("Please, input valid dates!");

                    break;
                }
                default:
                {
                }
                }
            }
        }

        case '3':
        {

            Console_clear();

            bool consoleDrawing = true;

            while (consoleDrawing)
            {
                for (int i = 0; i < 28; i++)
                {
                    for (int j = 0; j < 28; j++)
                    {
                        int color = getColor(image[i][j]);
                        Console_setCursorAttribute(color);
                        Console_setCursorPosition(i, j);
                        printf(" ");
                        printf("%c", image[i][j]);
                    }
                    Console_reset();
                    puts("  ");
                }
                printf("\tCOMMERCIAL\n");
                puts("If you want to continue to use our program, please, INPUT '1'");
                puts("If you want to exit, please, INPUT OTHER SYMBOLS");

                int exitMenu3 = 0;
                scanf("%i", &exitMenu3);

                if (exitMenu3 == 1)
                {
                    consoleDrawing = false;
                    break;
                }
                else
                    isMainMenuRunning = false;
                    break;
            }
        }
        }
    }

    puts("Bye!");

    return 0;
}

int getColor(char colorCode)
{
    const char colorsTable[16][2] = {
        {0x0, BG_BLACK},
        {0x1, BG_INTENSITY_BLACK},
        {0x2, BG_RED},
        {0x3, BG_INTENSITY_RED},
        {0x4, BG_GREEN},
        {0x5, BG_INTENSITY_GREEN},
        {0x6, BG_YELLOW},
        {0x7, BG_INTENSITY_YELLOW},
        {0x8, BG_BLUE},
        {0x9, BG_INTENSITY_BLUE},
        {0xa, BG_MAGENTA},
        {0xb, BG_INTENSITY_MAGENTA},
        {0xc, BG_CYAN},
        {0xd, BG_INTENSITY_CYAN},
        {0xe, BG_WHITE},
        {0xf, BG_INTENSITY_WHITE}};
    const int tableLength = sizeof(colorsTable) / sizeof(colorsTable[0]);
    for (int i = 0; i < tableLength; i++)
    {
        char colorPairCode = colorsTable[i][0];
        char colorPairColor = colorsTable[i][1];
        if (colorCode == colorPairCode)
        {
            return colorPairColor;
        }
    }
    return 0;
}