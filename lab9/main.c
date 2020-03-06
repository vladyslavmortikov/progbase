#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <progbase.h>
#include <progbase/console.h>
#include <progbase/canvas.h>
#include <time.h>
#include <stdbool.h>
#include <progbase/canvas.h>
#include <string.h>

enum TOKEN_TYPE
{
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_OPERATOR,
    TOKEN_LITERAL,
    TOKEN_DELIMITER,
    TOKEN_WHITESPACE
};

struct position
{
    int x;
    int y;
};

enum TokenSubType
{
    OP_MULT, //*
    OP_GREATER,
    OP_LESS,
    OP_SUBSTRACT,
    OP_ASSIGMENT, //=

    DEL_LEFTPAR,        //(
    DEL_RIGHTPAR,       //)
    DEL_COMMA,          //,
    DEL_SEMICOLON,      //;
    DEL_DOUBLEPOINT,    //:
    DEL_LEFTCURLBRACE,  //{
    DEL_RIGHTCURLBRACE, //}

    KW_INT,
    KW_IF,
    KW_ELSE,

    LIT_INTEGER,
    LIT_FLOAT,
    LIT_STRING,

    NONE
};

struct StringTable
{
    char *items;
    size_t capacity;
    size_t count;
    size_t rowCapacity;
};
struct Token
{
    char *lexeme;
    enum TOKEN_TYPE type;
    int subType;
    struct position pos;
};
struct TokenList
{
    struct Token *items;
    size_t capacity;
    size_t count;
    char *SubtupeToPrint;
};
struct TextPosition
{
    int row, column;
};

struct StringTable createStringTable(char *items, int cap, int rowCap);

struct TokenList createTokenList(struct Token *tokens, int cap);

void addToken(struct TokenList *plist, struct Token token);

void addString(struct StringTable *ptable, const char *str);

void insertString(struct StringTable *ptable, const char *str, int index);

void printStrings(struct StringTable *ptable);

void printTokens(const struct TokenList *tokens);

void removeStringAt(struct StringTable *ptable, int index);

char *getStringAt(struct StringTable *ptable, int index);

char *findString(struct StringTable *ptable, const char *str);

bool containsString(struct StringTable *ptable, const char *str);

void readDigit(char *cur, char *result, int *pos);

char readCode(int *pos);

bool readingNumber(char **p, char *pbuf);

enum TokenSubType checkOperatorsAndDelimeters(const char *word);

struct Token *getToken(struct TokenList *t_list, int index);

void printList(struct TokenList *t_list);

int main(int argc, char const *argv[])
{
    char input_[] = "input.txt";
    char output[] = "output.txt";
    bool print = false;
    if (argc > 1)
    {
        int i = 1;
        while (i < argc)
        {
            if (strcmp(argv[i], "-o") == 0)
            {
                i++;
                if (i == argc)
                {
                    printf("ERROR: output file missing\n");
                    return 1;
                }
                strcpy(output, (argv[i]));
                continue;
            }
            if (strcmp(argv[i], "-l") == 0)
            {
                print = true;
            }
            if ((strcmp(argv[i], "-o") != 0) && (strcmp(argv[i], "-l") != 0) && i == 1)
            {
                strcpy(input_, (argv[i]));
                continue;
            }
            i++;
        }
    }
    //
    char input[1000];
    FILE *fp = fopen(input_, "r");
    if (fp == NULL)
    {
        return 1;
    }
    char symbol = fgetc(fp);
    int i = 0;
    while (symbol != EOF)
    {
        input[i] = symbol;
        i++;
        symbol = fgetc(fp);
    }
    
    input[i] = '\0';
    fclose(fp);
    //
    // int nTokens = 55;
    const int maxTokens = 100;
    struct Token aTokens[maxTokens];
    struct TokenList tokens = createTokenList(&aTokens[0], maxTokens);

    const int nRows = 150;
    const int nCols = 150;
    char nKeywords[nRows][nCols];
    struct StringTable keywords = createStringTable(&nKeywords[0][0], nRows, nCols);

    const int nIdRows = 150;
    const int nIdCols = 150;
    char mIdentifiers[nIdRows][nIdCols];
    struct StringTable identifiers = createStringTable(&mIdentifiers[0][0], nIdRows, nIdCols);

    const int nItRows = 150;
    const int nItCols = 150;
    char mIterals[nItRows][nItCols];
    struct StringTable literals = createStringTable(&mIterals[0][0], nItRows, nItCols);

    // const int spRows = 50;
    // const int spCols = 50;
    // char sp[nItRows][nItCols];
    //struct StringTable whitespaces = createStringTable(&sp[0][0], spRows, spCols);

    addString(&keywords, "int");
    addString(&keywords, "if");
    addString(&keywords, "else");

    char *p = input;
    char buffer[1000];
    char *pbuf = buffer;
    struct position pos1;
    pos1.x = 1;
    pos1.y = 1;
    while (true)
    {
        //readString
        if (*p == '"')
        {
            struct Token token;
            token.pos.x = pos1.x;
            token.pos.y = pos1.y;
            p++;
            while (true)
            {
                if (*p == '"' && *(p - 1) != '\\')
                {
                    p++;
                    break;
                }
                *pbuf = *p;
                pbuf++;
                p++;
            }
            *pbuf = '\0';
            pbuf = buffer;
            Console_setCursorAttribute(FG_RED);
            printf("\"%s\"", buffer);
            pos1.x += strlen(pbuf);
            addString(&literals, buffer);
            token.type = TOKEN_LITERAL;
            token.subType = LIT_STRING;
            token.lexeme = findString(&literals, buffer);
            addToken(&tokens, token);
            continue;
        }
        else if (isalpha(*p) || *p == '_')
        {
            struct Token token;
            token.pos.x = pos1.x;
            token.pos.y = pos1.y;
            while (isalpha(*p) || *p == '_')
            {
                //read word
                *pbuf = *p;
                pbuf += 1;
                p += 1;
            }
            *pbuf = '\0';
            pbuf = buffer;
            pos1.x += strlen(pbuf);
            if (containsString(&keywords, buffer))
            {
                token.lexeme = findString(&keywords, buffer);
                (token).lexeme = findString(&keywords, buffer);
                token.type = TOKEN_KEYWORD;
                if (strcmp(buffer, "int") == 0)
                {
                    token.subType = KW_INT;
                }
                else if (strcmp(buffer, "if") == 0)
                {
                    token.subType = KW_IF;
                }
                else if (strcmp(buffer, "else") == 0)
                {
                    token.subType = KW_ELSE;
                }
                Console_setCursorAttribute(FG_RED);
                printf(" %s ", buffer);
                pos1.x += strlen(buffer);
                addToken(&tokens, token);
            }
            else
            {
                //ident
                addString(&identifiers, buffer);
                token.lexeme = findString(&identifiers, buffer);
                token.type = TOKEN_IDENTIFIER;
                Console_setCursorAttribute(FG_BLUE);
                printf(" %s ", buffer);
                pos1.x += strlen(buffer);
                addToken(&tokens, token);
            }
            continue;
        }
        else if (*p == '*' || *p == '=' || *p == '<' || *p == ',' || *p == ')' || *p == '(' || *p == '{' || *p == '}' || *p == ';' || *p == '>' || *p == '-')
        {
            struct Token token;
            token.pos.x = pos1.x;
            token.pos.y = pos1.y;
            if (*p == '*' || *p == '=' || *p == '<' || *p == '>' || *p == '-')
            {
                *pbuf = *p;
                pbuf++;
                p++;
                *pbuf = '\0';
                pbuf = buffer;
                addString(&literals, buffer);
                Console_setCursorAttribute(FG_CYAN);
                printf(" %s ", buffer);
                token.type = TOKEN_OPERATOR;
                token.subType = checkOperatorsAndDelimeters(buffer);
                token.lexeme = findString(&literals, buffer);
            }
            else
            {
                *pbuf = *p;
                pbuf++;
                p++;
                *pbuf = '\0';
                pbuf = buffer;
                addString(&literals, buffer);
                Console_setCursorAttribute(FG_GREEN);
                printf("%s", buffer);
                token.type = TOKEN_DELIMITER;
                token.subType = checkOperatorsAndDelimeters(buffer);
                token.lexeme = findString(&literals, buffer);
            }
            pos1.x += strlen(pbuf);
            addToken(&tokens, token);
        }
        else if (isdigit(*p))
        {
            bool isFloat = readingNumber(&p, pbuf);
            pbuf = buffer;

            struct Token token;
            token.pos.x = pos1.x;
            token.pos.y = pos1.y;
            addString(&literals, buffer);
            pos1.x += strlen(pbuf);

            Console_setCursorAttribute(FG_INTENSITY_MAGENTA);
            printf("%s", buffer);
            token.type = TOKEN_LITERAL;
            if (isFloat)
            {
                token.subType = LIT_FLOAT;
            }
            else
            {
                token.subType = LIT_INTEGER;
            }
            token.lexeme = findString(&literals, buffer);
            addToken(&tokens, token);
        }
        else
        {
            p++;
            pos1.x++;
        }
        if (*p == '\n')
        {
            pos1.x = 1;
            pos1.y++;
        }
        if (*p == '\0')
        {
            break;
        }
    }
    puts(" ");

    if (print)
    {
        printList(&tokens);
    }
    FILE *text = freopen(output, "w", stdout);
    fprintf(text, "%s", input);
    printf("\n\n");
    if (print)
    {
        printList(&tokens);
    }
    fclose(text);
    return 0;
}

//
struct TokenList createTokenList(struct Token *items, int cap)
{
    struct TokenList list;
    list.items = items;
    list.capacity = cap;
    list.count = 0;
    return list;
};
//
bool containsString(struct StringTable *ptable, const char *str)
{
    return findString(ptable, str) != NULL;
};
//
char *getStringAt(struct StringTable *ptable, int index)
{
    char *p = (*ptable).items;
    p += index * (*ptable).rowCapacity;
    return p;
};
//
struct StringTable
createStringTable(char *items, int cap, int rowCap)
{
    struct StringTable table;
    table.items = items;
    table.items[0] = '\0';
    table.capacity = cap;
    table.count = 0;
    table.rowCapacity = rowCap;
    return table;
}
//
void addString(struct StringTable *ptable, const char *str)
{
    int rowIndex = (*ptable).count;
    char *p = getStringAt(ptable, rowIndex);
    strcpy(p, str);
    (*ptable).count += 1;
}
//
void printTokens(const struct TokenList *tokens)
{
    const int len = (*tokens).count;
    printf("Tokens %d: \n", len);
    for (int i = 0; i < len; i++)
    {
        struct Token t = (*tokens).items[i];
        printf("%s , ", t.lexeme);
    }
};
//
void printStrings(struct StringTable *ptable)
{
    const int len = (*ptable).count;
    printf("StringTable %d: \n", len);
    for (int i = 0; i < len; i++)
    {
        printf("%d)  %s \n", i, getStringAt(ptable, i));
    }
};
//
void addToken(struct TokenList *plist, struct Token token)
{
    int prevCount = (*plist).count;
    int index = prevCount;
    (*plist).items[index] = token;
    (*plist).count += 1;
};
//
char *findString(struct StringTable *ptable, const char *str)
{
    for (int i = 0; i < (*ptable).count; i++)
    {
        char *p = getStringAt(ptable, i);
        if (strcmp(p, str) == 0)
        {
            return p;
        }
    }
    return NULL;
};
//
enum TokenSubType checkOperatorsAndDelimeters(const char *word)
{

    if (strcmp(word, "*") == 0)
    {
        return OP_MULT;
    }
    else if (strcmp(word, "<") == 0)
    {
        return OP_GREATER;
    }
    else if (strcmp(word, "-") == 0)
    {
        return OP_SUBSTRACT;
    }
    else if (strcmp(word, ">") == 0)
    {
        return OP_LESS;
    }
    else if (strcmp(word, "(") == 0)
    {
        return DEL_LEFTPAR;
    }
    else if (strcmp(word, ")") == 0)
    {
        return DEL_RIGHTPAR;
    }
    else if (strcmp(word, ",") == 0)
    {
        return DEL_COMMA;
    }
    else if (strcmp(word, ";") == 0)
    {
        return DEL_SEMICOLON;
    }
    else if (strcmp(word, "}") == 0)
    {
        return DEL_RIGHTCURLBRACE;
    }
    else if (strcmp(word, "{") == 0)
    {
        return DEL_LEFTCURLBRACE;
    }
    else if (strcmp(word, "=") == 0)
    {
        return OP_ASSIGMENT;
    }

    return NONE;
}
//
void printList(struct TokenList *t_list)
{
    for (int i = 0; i < 43; i++)
    {
        struct Token tok;
        tok = *getToken(t_list, i);
        if (tok.type == TOKEN_KEYWORD)
        {
            printf("%-20s", "TOKEN_KEYWORD");
            if (tok.subType == KW_INT)
            {
                printf("%-20s", "KW_INT");
            }
            else if (tok.subType == KW_IF)
            {
                printf("%-20s", "KW_IF");
            }
            else if (tok.subType == KW_ELSE)
            {
                printf("%-20s", "KW_ELSE");
            }
        }
        else if (tok.type == TOKEN_IDENTIFIER)
        {
            printf("%-20s", "TOKEN_IDENTIFIER");
            printf("%-20s", "");
        }
        else if (tok.type == TOKEN_OPERATOR)
        {
            printf("%-20s", "TOKEN_OPERATOR");

            if (tok.subType == OP_GREATER)
            {
                printf("%-20s", "OP_GREATER");
            }
            else if (tok.subType == OP_LESS)
            {
                printf("%-20s", "OP_LESS");
            }
            else if (tok.subType == OP_MULT)
            {
                printf("%-20s", "OP_MULT");
            }
            else if (tok.subType == OP_ASSIGMENT)
            {
                printf("%-20s", "OP_ASSIGMENT");
            }
        }
        else if (tok.type == TOKEN_LITERAL)
        {
            printf("%-20s", "TOKEN_LITERAL");
            if (tok.subType == LIT_FLOAT)
            {
                printf("%-20s", "LIT_FLOAT");
            }
            else if (tok.subType == LIT_INTEGER)
            {
                printf("%-20s", "LIT_INTEGER");
            }
            else if (tok.subType == LIT_STRING)
            {
                printf("%-20s", "LIT_STRING");
            }
        }
        else if (tok.type == TOKEN_DELIMITER)
        {
            printf("%-20s", "TOKEN_DELIMITER");
            if (tok.subType == DEL_LEFTCURLBRACE)
            {
                printf("%-20s", "DEL_LEFTCURLBRACE");
            }
            else if (tok.subType == DEL_RIGHTCURLBRACE)
            {
                printf("%-20s", "DEL_RIGHTCURLBRACE");
            }
            else if (tok.subType == DEL_COMMA)
            {
                printf("%-20s", "DEL_COMMA");
            }
            else if (tok.subType == DEL_LEFTPAR)
            {
                printf("%-20s", "DEL_LEFTPAR");
            }
            else if (tok.subType == DEL_RIGHTPAR)
            {
                printf("%-20s", "DEL_RIGHTPAR");
            }
            else if (tok.subType == DEL_SEMICOLON)
            {
                printf("%-20s", "DEL_SEMICOLON");
            }
        }
        printf("%d\t\t", tok.pos.x);
        printf("%d\t\t", tok.pos.y);
        printf("\"%s\"\n", tok.lexeme);
    }
}
//

struct Token *getToken(struct TokenList *t_list, int index)
{
    struct Token *tok = t_list->items;
    tok += index;
    return tok;
}
//
bool readingNumber(char **p, char *pbuf)
{
    bool isFloat = false;
    while (isdigit(**p))
    {
        *pbuf = **p;
        pbuf++;
        (*p)++;
    }
    if (**p == '.')
    {
        *pbuf = **p;
        pbuf++;
        (*p)++;
        while (isdigit(**p))
        {
            *pbuf = **p;
            pbuf++;
            (*p)++;
        }
        isFloat = true;
    }
    *pbuf = '\0';
    return isFloat;
}