#include <iostream>
#include <string>
#include <conio.h>

int charClass;
char lexeme[100];
char nextChar;
int ident;
int lexLen;
int token;
int nextToken;
char nextTokenc[30];
FILE *in_fp, *fopen();
char addChar();
void getChar();
void getNonBlank();
int lex();

#define LETTER 0
#define DIGIT 1
#define PAGAR 2
#define USE 3
#define MY 4
#define HASH 5
#define UNKNOWN 99

#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define RANDOM 0

main() {

if ((in_fp = fopen("source.txt", "r")) == NULL){
printf("ERROR - source.txt tidak ada \n");
getch();
}
else {
getChar();
do {
lex();
} while (nextToken != EOF);
}
getch();
}

int lookup(char ch) {
switch (ch) {
case '=':
addChar();
strcpy (nextTokenc,"ASSIGN_OP");
nextToken = RANDOM;
break;
case '"':
addChar();
strcpy (nextTokenc,"QUOTE");
nextToken = RANDOM;
break;
case ',':
addChar();
strcpy (nextTokenc,"COLON");
nextToken = RANDOM;
break;
case ';':
addChar();
strcpy (nextTokenc,"SEMI_COLON");
nextToken = RANDOM;
break;
case '$':
addChar();
strcpy (nextTokenc,"SCALAR_DEC");
nextToken = RANDOM;
break;
case '%':
addChar();
strcpy (nextTokenc,"VECTOR_DEC");
nextToken = RANDOM;
break;
case '@':
addChar();
strcpy (nextTokenc,"ARRAY_DEC");
nextToken = RANDOM;
break;
case '(':
addChar();
nextToken = LEFT_PAREN;
strcpy (nextTokenc,"LEFT_PAREN");
break;
case ')':
addChar();
nextToken = RIGHT_PAREN;
strcpy (nextTokenc,"RIGHT_PAREN");
break;
case '{':
addChar();
strcpy (nextTokenc,"LEFT_BRACKET");
nextToken = RANDOM;
break;
case '}':
addChar();
nextToken = RIGHT_PAREN;
strcpy (nextTokenc,"RIGHT_BRACKET");
nextToken = RANDOM;
break;
case '[':
addChar();
strcpy (nextTokenc,"LEFT_BRACKET");
nextToken = RANDOM;
break;
case ']':
addChar();
nextToken = RIGHT_PAREN;
strcpy (nextTokenc,"RIGHT_BRACKET");
nextToken = RANDOM;
break;
case '+':
addChar();
nextToken = ADD_OP;
strcpy (nextTokenc,"ADD_OP");
break;
case '-':
addChar();
nextToken = SUB_OP;
strcpy (nextTokenc,"SUB_OP");
break;
case '*':
addChar();
nextToken = MULT_OP;
strcpy (nextTokenc,"MULT_OP");
break;
case '/':
addChar();
nextToken = DIV_OP;
strcpy (nextTokenc,"DIV_OP");
break;
default:
addChar();
nextToken = EOF;
break;
}
return nextToken;
}

char addChar() {
if (lexLen <= 98) {
lexeme[lexLen++] = nextChar;
lexeme[lexLen]=0;
}
else
{
printf("Error - lexeme terlalu panjang \n");
getch();}
}


void getChar() {
if ((nextChar = getc(in_fp)) != EOF) {
if (isalpha(nextChar))
charClass = LETTER;
else if (isdigit(nextChar))
charClass = DIGIT;
else charClass = UNKNOWN;
}
else
charClass = EOF;
}

void getNonBlank() {
while (isspace(nextChar))
getChar();
}

int lex() {
ident=1;
lexLen = 0;
getNonBlank();
switch (charClass) { 

/* Parse identifiers */
case LETTER:
addChar();
getChar();
while (charClass == LETTER || charClass == DIGIT) {
addChar();
getChar();
}
nextToken = IDENT;
if(ident==1)strcpy (nextTokenc,"VARIABLE");
break;

/* Parse integer literals */
case DIGIT:
addChar();
getChar();
while (charClass == DIGIT) {
addChar();
getChar();
}
nextToken = INT_LIT;
strcpy (nextTokenc,"INTEGER");
break;

/* Parentheses and operators */
case UNKNOWN:
lookup(nextChar);
getChar();
break;

/* EOF */
case EOF:
nextToken = EOF;
lexeme[0] = 'E';
lexeme[1] = 'O';
lexeme[2] = 'F';
lexeme[3] = 0;
strcpy (nextTokenc,"EOF");
break;

default:
while (charClass == LETTER || charClass == DIGIT) {
addChar();
getChar();
}
nextToken = IDENT;
strcpy (nextTokenc,"IDEN");
break;
} /* End of switch */
printf("lexeme: %s \t token: %s\n",lexeme, nextTokenc);
return nextToken;
}
