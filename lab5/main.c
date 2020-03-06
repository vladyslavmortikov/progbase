#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <progbase.h>
#include <time.h>
#include <stdbool.h>
#include <progbase/console.h>
#include <ctype.h>
#include <string.h>

int conReadLine(char str[], int maxBufLen)
{
    fgets(str, maxBufLen, stdin);
    int bufLength = strlen(str);
    if (str[bufLength - 1] == '\n')
    {
        str[bufLength - 1] = '\0';
        bufLength -= 1;
    }
    else
    {
        for (char ch; (ch = getchar()) != '\n';)
        {
        }
    }
    return bufLength;
}

void title1STmenu()
{
    Console_setCursorAttribute(FG_GREEN);
    printf("\nThe result is >> ");
}

int main()
{
    srand(time(0));

    bool mainMenu = true;

    while (mainMenu)
    {
        Console_clear();

        Console_setCursorAttribute(FG_BLUE);
        puts("M A I N   M E N U");
        Console_reset();

        puts("1. Characters");
        puts("2. String");
        puts("0. Quit  ");

        char mainMenuUserInput = Console_getChar();

        switch (mainMenuUserInput)
        {

        case '0':
        {
            mainMenu = false;
            break;
        }

        case '1':
        {

            bool isSubMenu1Running = true;

            while (isSubMenu1Running)
            {
                Console_clear();

                Console_setCursorAttribute(FG_BLUE);
                puts("\n\nThis is CHARACTERS submenu");
                Console_reset();

                puts("\t1. Alphanumeric");
                puts("\t2. Alphabetic (lowercase)");
                puts("\t3. Alphabetic(uppercase) ");
                puts("\t4. Alphabetic(all)");
                puts("\t5. Decimal digit");
                puts("\t6. Hexadecimal digit");
                puts("\t7. Punctuation");

                puts("0. <- Back");
                printf("> Enter your option: ");

                char menu1Running = Console_getChar();
                printf("You entered: '%c'\n", menu1Running);

                if (menu1Running > 7 && menu1Running < 0)
                {
                    printf("\nPlease, choose numbers from '0' to '7'");
                }

                else

                    switch (menu1Running)
                    {

                    case '0':
                    {
                        isSubMenu1Running = false;
                    }
                    break;

                    case '1':
                    {
                        title1STmenu();
                        for (int c = 0; c <= 200; c++)
                        {
                            if (isalnum(c))
                            {
                                putchar(c);
                                putchar(32);
                            }
                        }
                    }
                    break;

                    case '2':
                    {
                        title1STmenu();
                        for (int c = 0; c <= 200; c++)
                        {
                            if (isalpha(c))
                            {
                                if (islower(c))
                                {
                                    putchar(c);
                                    putchar(32);
                                }
                            }
                        }
                    }
                    break;

                    case '3':
                    {
                        title1STmenu();
                        for (int c = 0; c <= 200; c++)
                        {
                            if (isalpha(c))
                            {
                                if (isupper(c))
                                {
                                    putchar(c);
                                    putchar(32);
                                }
                            }
                        }
                    }
                    break;

                    case '4':
                    {
                        title1STmenu();
                        for (int c = 0; c <= 200; c++)
                        {
                            if (isalpha(c))
                            {
                                putchar(c);
                                putchar(32);
                            }
                        }
                    }
                    break;

                    case '5':
                    {
                        title1STmenu();
                        for (int c = 0; c <= 200; c++)
                        {
                            if (isdigit(c))
                            {
                                putchar(c);
                                putchar(32);
                            }
                        }
                    }
                    break;

                    case '6':
                    {
                        title1STmenu();

                        for (int c = 0; c <= 200; c++)
                        {
                            if (isxdigit(c))
                            {
                                putchar(c);
                                putchar(32);
                            }
                        }
                    }
                    break;

                    case '7':
                    {
                        title1STmenu();

                        for (int c = 0; c <= 200; c++)
                        {
                            if (ispunct(c))
                            {
                                putchar(c);
                                putchar(32);
                            }
                        }
                    }
                    break;
                    }
            }

        case '2':
        {
            Console_clear();

            int stringLen = 0;
            printf("Please, input a size of the string >> \n");
            scanf("%i", &stringLen);
            Console_clear();
            char string[stringLen];
            int key = 0;

            for (int c = 0; c < stringLen; c++)
            {
                string[c] = rand() % (126 - 32 + 1) + 32;
            }

            string[stringLen - 1] = '\0';

            do
            {

                printf("\n\nString (%i)>>\n", stringLen);
                puts(string);

                puts("\t1. To change the string");
                puts("\t2. To clear the string");
                puts("\t3. To output a substring from a given position to a given length.");
                puts("\t4. Output a list substrings separated by a given character.");
                puts("\t5. Print the longest word.");
                puts("\t6. Find and print all integers contained in a line.");
                puts("\t7. Find and output the sum of all fractional numbers contained in a line.");

                puts("0. <- Back");
                printf("> Enter your option: ");

                scanf("%i", &key);
                for (char ch; (ch = getchar()) != '\n';)
                {
                }

                switch (key)
                {

                case 1:
                {
                    Console_clear();

                    printf("Enter string: ");
                    const int bufLen = stringLen;
                    char buf[bufLen];
                    int strLen = 0;
                    while (!strLen)
                        strLen = conReadLine(buf, bufLen);
                    stringLen = strLen;
                    for (int c = 0; c <= stringLen; c++)
                    {
                        string[c] = buf[c];
                        if (c == strLen)
                        {
                            string[c] = '\0';
                        }
                    }

                    printf("Entered (%d): \"%s\"", strLen, buf);
                    puts("\n---");
                }
                break;

                case 2:
                {
                    Console_clear();
                    string[0] = '\0';
                }
                break;

                case 3:
                {
                    int positionMin = 0;
                    int positionMax = 0;
                    puts("Input min:");
                    scanf("%i", &positionMin);

                    puts("Input max:");
                    scanf("%i", &positionMax);
                    Console_clear();
                    if (positionMin - 1 >= 0 && positionMax < stringLen)
                    {
                        printf(">>Substring:\n");
                        for (int c = positionMin; c <= positionMax; c++)
                        {
                            putchar(string[c]);
                        }
                        puts(" ");
                    }
                    else
                    {
                        break;
                    }
                }
                break;

                case 4:
                {
                    Console_clear();
                    char separator = 0;
                    scanf("%c", &separator);

                    int tmpI = 0;
                    char tmpStr[stringLen];
                    for (int i = 0;; i++)
                    {
                        char ch = string[i];

                        if (ch == separator || ch == '\0')
                        {
                            if (tmpI != 0)
                            {
                                tmpStr[tmpI] = '\0';
                                printf(">> %s", tmpStr);
                                puts("");
                                tmpI = 0;
                            }
                            if (ch == '\0')
                            {
                                break;
                            }
                        }
                        else
                        {
                            tmpStr[tmpI] = ch;
                            tmpI += 1;
                        }
                    }
                }
                break;

                case 5:
                {
                    Console_clear();
                    int tmpI = 0;
                    char maxlength[stringLen];
                    char tmpStr[stringLen];
                    maxlength[0] = '\0';
                    for (int i = 0;; i++)
                    {
                        char ch = string[i];
                        if (ch == '\0' || (isalpha(ch) == 0))
                        {
                            if (tmpI != 0)
                            {
                                tmpStr[tmpI] = '\0';
                                if (strlen(tmpStr) > strlen(maxlength))
                                {
                                    strcpy(maxlength, tmpStr);
                                }
                                tmpI = 0;
                            }
                            if (ch == '\0')
                            {
                                break;
                            }
                        }
                        else if (isalpha(ch))
                        {
                            tmpStr[tmpI] = ch;
                            tmpI += 1;
                        }
                    }
                    puts(maxlength);
                    puts("\n");
                }
                break;

                case 6:
                {
                    int tmpI = 0;
                    char tmpStr[stringLen];

                    for (int i = 0;; i++)
                    {
                        char ch = string[i];
                        if (ch == '\0' || (isdigit(ch) == 0))
                        {
                            if (tmpI != 0)
                            {
                                tmpStr[tmpI] = '\0';
                                printf(">> %s\n", tmpStr);
                                tmpI = 0;
                            }
                            if (ch == '\0')
                            {
                                break;
                            }
                        }
                        else if (isdigit(ch))
                        {
                            tmpStr[tmpI] = ch;
                            tmpI += 1;
                        }
                        // puts("\n");
                    }
                }
                break;

                case 7:
                {
                    Console_size();
                    int tmpI = 0;
                    char tmpStr[stringLen];
                    bool dotsaved = false;
                    float res = 0;
                    for (int i = 0;; i++)
                    {
                        char ch = string[i];
                        if (ch == '\0' || ((isdigit(ch) == 0) && dotsaved))
                        {
                            if (tmpI != 0)
                            {
                                tmpStr[tmpI] = '\0';
                                printf(">> %s\n", tmpStr);
                                res += atof(tmpStr);
                                tmpI = 0;
                                dotsaved = !dotsaved;
                            }
                            if (ch == '\0')
                            {
                                break;
                            }
                        }
                        else if ((isdigit(ch) && dotsaved) || (!dotsaved && ch == '.') || (!dotsaved && isdigit(ch)))
                        {
                            tmpStr[tmpI] = ch;
                            tmpI += 1;

                            if (ch == '.')
                            {
                                dotsaved = true;
                            }
                        }
                    }
                    printf(" the summ is %f\n", res);
                }
                break;

                default:
                {
                    Console_clear();
                }
                break;
                }

            } while (key != 8);
        }
        }
        }
    }

    puts("\nBye!");

    return 0;
}