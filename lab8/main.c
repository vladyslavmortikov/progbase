#include <stdio.h>   
#include <math.h>     
#include <stdlib.h>  
#include <progbase.h> 
#include <progbase/console.h> 
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

enum TokenType
{
   TOKEN_KEYWORD,
   TOKEN_IDENTIFIER,
   TOKEN_LITERAL,
   TOKEN_OPERATOR,
   TOKEN_DELIMITER,
};
enum TokenKeywords
{
   KW_INT,
   KW_IF,
   KW_ELSE,
};
enum TokenLiterals
{
   LIT_INTEGER,
   LIT_FLOAT,
   LIT_STRING,
};
enum TokenOperators
{
   OP_PLUS,
   OP_MULT,
   OP_ASSIGNMENT,
   OP_DIVISION,
};
enum TokenDelimiters
{
   DEL_LEFTPAR,
   DEL_RIGHTPAR,
   DEL_COMMA,
   DEL_SEMICOLON,
};

struct StringTable
{
   char * items;
   size_t capacity;
   size_t count;
   size_t rowCapacity;
};
struct TokenList
{
    struct Token * items;
    size_t capacity;
    size_t count;
};
struct Token
{
   char * lexeme;
   enum TokenType type;
   int    subType;
};

struct StringTable createStringTable(char *items, int cap, int rowCap);
struct TokenList createTokenList(struct Token * a, int n);
void addToken(struct TokenList * plist, struct Token newToken);
void addString(struct StringTable *ptable, const char *str);
char * getStringAt(const struct StringTable *ptable, int index);
void printToken(struct TokenList * plist);
void parseCode(char * p, struct StringTable *keywords, struct StringTable * identifiers, struct StringTable *literals, struct StringTable *operators, struct StringTable *delimiters, struct TokenList * plist);
char * readWord(char * str, char * dest, const int destSize);
char * readNumber(char * str, char * dest, const int destSize, int * Dot);
char * readString(char * str, char * dest, const int destSize);
bool IsOperator(char ch, struct Token * token);
bool IsDelimiter(char ch, struct Token * token);

int main() {
    Console_clear();
    //start
    char string[] = "int x = 5 + 5.6 / 2;\nif (x > 10) {\n puts(\"Greater\");}\n else if (x < 0)\n {\n int a = 42;\n printf(\"%d\", x - a);\n}";

    const int nTokens = 100;
    struct Token Tokens[nTokens];
    struct TokenList tokens = createTokenList(&Tokens[0], nTokens);

    const int nRows = 10;
    const int nColoms = 33;
    char nKeywords[nRows][nColoms];
    char nIdentifiers[nRows][nColoms];
    char nLiterals[nRows][nColoms];
    char nOperators[nRows][nColoms];
    char nDelimiters[nRows][nColoms];
    struct StringTable keywords = createStringTable(&nKeywords[0][0], nRows, nColoms);
    struct StringTable identifiers = createStringTable(&nIdentifiers[0][0], nRows, nColoms);
    struct StringTable literals = createStringTable(&nLiterals[0][0], nRows, nColoms);
    struct StringTable operators = createStringTable(&nOperators[0][0], nRows, nColoms);
    struct StringTable delimiters = createStringTable(&nDelimiters[0][0], nRows, nColoms);
    char * p = &string[0];
    puts("Code >>>");
    puts(string);
    puts("<<<\n");
    parseCode(p, &keywords, &identifiers, &literals,&operators, &delimiters, &tokens);
    puts("Tokens >>>");
    printToken(&tokens);
    puts("<<<\n");
    // end
    return 0;
}
//create string's list
struct StringTable createStringTable(char *items, int cap, int rowCap)
{
   struct StringTable table;
   table.items = items;
   table.capacity = cap;
   table.count = 0;
   table.rowCapacity = rowCap;
   return table; 
}
//create token's list
struct TokenList createTokenList(struct Token * items, int cap)
{
    struct TokenList list;
    list.items = items;
    list.capacity = cap;
    list.count = 0;
    return list;
}
//add token to list
void addToken(struct TokenList * plist, struct Token newToken)
{
    int presentCount = (*plist).count;
    int index = presentCount;
    (*plist).items[index] = newToken;
    int newCount = presentCount + 1;
    (*plist).count = newCount;
}
//add string to list
void addString(struct StringTable *ptable, const char *str)
{
    int rowIndex = (*ptable).count;
    char *p = getStringAt(ptable, rowIndex);
    strcpy(p, str);
    (*ptable).count += 1;
}
//get strings
char * getStringAt(const struct StringTable *ptable, int index)
{
   char *p = (*ptable).items;
   p += index * (*ptable).rowCapacity;
   return p;
}
//print tokens to list
void printToken(struct TokenList * plist)
{
    for(int i = 0; i < (*plist).count; i++)
    {
        if((*plist).items[i].type == TOKEN_KEYWORD)
        {
           printf("TOKEN_KEYWORD\t\t");
           if((*plist).items[i].subType == KW_INT)
           {
               printf("KW_INT\t\t");
           }
           else if((*plist).items[i].subType == KW_IF)
           {
               printf("KW_IF\t\t");
           }
           else if((*plist).items[i].subType == KW_ELSE)
           {
               printf("KW_ELSE\t\t");
           }
           printf("\"%s\"\n", (*plist).items[i].lexeme);
        }
        else if((*plist).items[i].type == TOKEN_IDENTIFIER)
        {
           printf("TOKEN_IDENTIFIER\t\t\t");
           printf("\"%s\"\n", (*plist).items[i].lexeme);
        }
        else if((*plist).items[i].type == TOKEN_LITERAL)
        {
           printf("TOKEN_LITERAL\t\t");
           if((*plist).items[i].subType == LIT_INTEGER)
           {
               printf("LIT_INTEGER\t");
               printf("\"%s\"\n", (*plist).items[i].lexeme);
           }
           else if((*plist).items[i].subType == LIT_FLOAT)
           {
               printf("LIT_FLOAT\t");
               printf("\"%s\"\n", (*plist).items[i].lexeme);
           }
           else if((*plist).items[i].subType == LIT_STRING)
           {
               printf("LIT_STRING\t");
               printf("%s\n", (*plist).items[i].lexeme);
           }
        }
        else if((*plist).items[i].type == TOKEN_DELIMITER)
        {
           printf("TOKEN_DELIMITER\t\t");
           if((*plist).items[i].subType == DEL_COMMA)
           {
               printf("DEL_COMMA\t");
           }
           else if((*plist).items[i].subType == DEL_SEMICOLON)
           {
               printf("DEL_SEMICOLON\t");
           }
           else if((*plist).items[i].subType == DEL_LEFTPAR)
           {
               printf("DEL_LEFTPAR\t");
           }
           else if((*plist).items[i].subType == DEL_RIGHTPAR)
           {
               printf("DEL_RIGHTPAR\t");
           }
           printf("\"%s\"\n", (*plist).items[i].lexeme);
        }
        else if((*plist).items[i].type == TOKEN_OPERATOR)
        {
           printf("TOKEN_OPERATOR\t\t");
           if((*plist).items[i].subType == OP_MULT)
           {
               printf("OP_MULT\t\t");
           }
           else if((*plist).items[i].subType == OP_PLUS)
           {
               printf("OP_PLUS\t\t");
           }
           else if((*plist).items[i].subType == OP_ASSIGNMENT)
           {
               printf("OP_ASSIGNMENT\t");
           }
           else if((*plist).items[i].subType == OP_DIVISION)
           {
               printf("OP_DIVISION\t");
           }
           printf("\"%s\"\n", (*plist).items[i].lexeme);
        }
        else
        {
            printf("List is empty");
        }
    }
}
// parse code
void parseCode(char * p, struct StringTable *keywords, struct StringTable * identifiers, struct StringTable *literals, struct StringTable *operators, struct StringTable *delimiters, struct TokenList * plist)
{
    const int bufSize = 10;
    char buf[bufSize];
    int Dot = 0;
    struct Token newToken;
    while(*p != '\0')
    {
        if(isspace(*p))
        {
            //ignore
            p += 1;
        }
        else if(isalpha(*p) || *p == '_')
        {
            p = readWord(p, buf, bufSize);
            if(p != NULL)
            {
                if(strcmp(buf, "int") == 0)
                {
                    addString(keywords, buf);
                    newToken.lexeme = getStringAt(keywords, (*keywords).count - 1);
                    newToken.type = TOKEN_KEYWORD;
                    newToken.subType = KW_INT;
                    addToken(plist, newToken);
                }
                else if(strcmp(buf, "if") == 0)
                {
                    addString(keywords, buf);
                    newToken.lexeme = getStringAt(keywords, (*keywords).count - 1);
                    newToken.type = TOKEN_KEYWORD;
                    newToken.subType = KW_IF;
                    addToken(plist, newToken);
                }
                else if(strcmp(buf, "else") == 0)
                {
                    addString(keywords, buf);
                    newToken.lexeme = getStringAt(keywords, (*keywords).count - 1);
                    newToken.type = TOKEN_KEYWORD;
                    newToken.subType = KW_ELSE;
                    addToken(plist, newToken);
                }
                else
                {
                    addString(identifiers, buf);
                    newToken.lexeme = getStringAt(identifiers, (*identifiers).count - 1);
                    newToken.type = TOKEN_IDENTIFIER;
                    addToken(plist, newToken);
                }
            }
        }
        else if(isdigit(*p))
        {
            p = readNumber(p, buf, bufSize, &Dot);
            if(p != NULL)
            {
                if(Dot == 1)
                {
                    addString(literals, buf);
                    newToken.lexeme = getStringAt(literals, (*literals).count - 1);
                    newToken.type = TOKEN_LITERAL;
                    newToken.subType = LIT_FLOAT;
                    addToken(plist, newToken);
                }
                else
                {
                    addString(literals, buf);
                    newToken.lexeme = getStringAt(literals, (*literals).count - 1);
                    newToken.type = TOKEN_LITERAL;
                    newToken.subType = LIT_INTEGER;
                    addToken(plist, newToken);
                }
            }
        }
        else if(*p == '"')
        {
            p = readString(p, buf, bufSize);
            if(p != NULL)
            {
                addString(literals, buf);
                newToken.lexeme = getStringAt(literals, (*literals).count - 1);
                newToken.type = TOKEN_LITERAL;
                newToken.subType = LIT_STRING;
                addToken(plist, newToken);
            }
        }
        else if(IsOperator(*p, &newToken))
        {
            if(bufSize < 2)
            {
                p = NULL;
            }
            else
            {
                buf[0] = *p;
                buf[1] = '\0';
                addString(operators, buf);
                newToken.lexeme = getStringAt(operators, (*operators).count - 1);
                newToken.type = TOKEN_OPERATOR;
                addToken(plist, newToken);
                p++;
            }
        }
        else if(IsDelimiter(*p, &newToken))
        {
            if(bufSize < 2)
            {
                p = NULL;
            }
            else
            {
                buf[0] = *p;
                buf[1] = '\0';
                addString(delimiters, buf);
                newToken.lexeme = getStringAt(delimiters, (*delimiters).count - 1);
                newToken.type = TOKEN_DELIMITER;
                addToken(plist, newToken);
                p++;
            }
        }
        else
        {
            p += 1;
        }
        if(p == NULL)
        {
            printf("Error:\n");
            break;
        }
    }
}
//read word
char * readWord(char * str, char * dest, const int destSize)
{
    char * p = str;
    int count = 0;
    while(isalnum(*p) || *p == '_')
    {
        *dest = *p;
        dest++;
        count++;
        if(count >= destSize)
        {
            return NULL;
        }
        p++;
    }
    *dest = '\0';
    return p;
}
//indetifier numbers
char * readNumber(char * str, char * dest, const int destSize, int * Dot)
{
    char * p = str;
    int count = 0;
    *Dot = 0;
    while(isdigit(*p))
    {
        *dest = *p;
        dest++;
        count++;
        if(count >= destSize)
        {
            return NULL;
        }
        p++;
    }
    if(*p == '.')
    {
        *Dot = 1;
        *dest = *p;
        dest++;
        count++;
        if(count >= destSize)
        {
            return NULL;
        }
        p++;
        if(!isdigit(*p))
        {
            return NULL;
        }
        else
        {
            while(isdigit(*p))
            {
                *dest = *p;
                dest++;
                count++;
                if(count >= destSize)
                {
                    return NULL;
                }
                p++;
            }
        }
    }
    *dest = '\0';
    return p;
}
//ident strings
char * readString(char * str, char * dest, const int destSize)
{
    char * p = str;
    int count = 0;
    *dest = *p;
    dest++;
    p++;
    count++;
    while(*p != '"')
    {
        if(isgraph(*p) || isspace(*p))
        {
            *dest = *p;
            dest++;
            count++;
            if(count >= destSize)
            {
                return NULL;
            }
            p++;
        }
        else
        {
            return NULL;
        }
    }
    *dest = *p;
    dest++;
    p++;
    *dest = '\0';
    return p;
}
//operators + - * / < > = 
bool IsOperator(char ch, struct Token * token)
{
    if(ch == '+')
    {
        token->subType = OP_PLUS;
    }
    else if(ch == '*')
    {
        token->subType = OP_MULT;
    }
    else if(ch == '/')
    {
        token->subType = OP_DIVISION;
    }
    else if(ch == '=')
    {
        token->subType = OP_ASSIGNMENT;
    }
    else
    {
        return false;
    }
    return true;
}


//delimeters
bool IsDelimiter(char ch, struct Token * token)
{
    if(ch == ';')
    {
        token->subType = DEL_SEMICOLON;
    }
    else if(ch == ',')
    {
        token->subType = DEL_COMMA;
    }
    else if(ch == '(')
    {
        token->subType = DEL_LEFTPAR;
    }
    else if(ch == ')')
    {
        token->subType = DEL_RIGHTPAR;
    }
    else
    {
        return false;
    }
    return true;
}