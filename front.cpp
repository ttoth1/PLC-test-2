/* front.cpp - a lexical analyzer system for simple
 arithmetic expressions */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp;
FILE *out_fp;
bool lexicalError = false;
int lexemeCount = 0;

/* Lexical function declarations */
int lookup(char ch);
void addChar(void);
void getChar(void);
void getNonBlank(void);
int lex(void);
void lexError(void);

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define MOD_OP 27
#define GREATER_THAN 28
#define LESS_THAN 29
#define SEMICOLON 31
#define LEFT_BRACE 32
#define RIGHT_BRACE 33
#define NOT_EQUAL 34
#define LEFT_BRACKET 35
#define RIGHT_BRACKET 36
#define UNDERSCORE 37
#define EQUAL 38
#define GREATER_THAN_EQUAL 39
#define LESS_THAN_EQUAL 40
#define TREVOR_LOOP 50
#define TREVOR_SELECTION 51
#define TREVOR_ALT_SELECTION 52
#define JUST_ONE_BYTE 60
#define JUST_TWO_BYTES 61
#define JUST_FOUR_BYTES 62
#define JUST_EIGHT_BYTES 63

/******************************************************/
/* lookup - a function to look up operators and
 parentheses and return the token */
int lookup(char ch) {
	 switch (ch) {
		 case '(':
			 addChar();
			 nextToken = LEFT_PAREN;
			 break;
		 case ')':
			 addChar();
			 nextToken = RIGHT_PAREN;
			 break;
		 case '+':
			 addChar();
			 nextToken = ADD_OP;
			 break;
		 case '-':
			 addChar();
			 nextToken = SUB_OP;
			 break;
		 case '*':
			 addChar();
			 nextToken = MULT_OP;
			 break;
		 case '/':
			 addChar();
			 nextToken = DIV_OP;
			 break;
		 case '%':
			 addChar();
			 nextToken = MOD_OP;
			 break;
		 case '>':
			 addChar();
			 nextToken = GREATER_THAN;
			 break;
		 case '<':
			 addChar();
			 nextToken = LESS_THAN;
			 break;
		 case '=':
			 addChar();
			 nextToken = ASSIGN_OP;
			 break;
		 case ';':
			 addChar();
			 nextToken = SEMICOLON;
			 break;
		 case '{':
			 addChar();
			 nextToken = LEFT_BRACE;
			 break;
		 case '}':
			 addChar();
			 nextToken = RIGHT_BRACE;
			 break;
		 case '[':
			 addChar();
			 nextToken = LEFT_BRACKET;
			 break;
		 case ']':
			 addChar();
			 nextToken = RIGHT_BRACKET;
			 break;
		 case '!':
			 addChar();
			 nextToken = NOT_EQUAL;
			 break;
		 case '_':
			 addChar();
			 nextToken = UNDERSCORE;
			 break;
		 case '|':
			 addChar();
			 nextToken = EQUAL;
			 break;
		 case '@':
			 addChar();
			 nextToken = GREATER_THAN_EQUAL;
			 break;
		 case '$':
			 addChar();
			 nextToken = LESS_THAN_EQUAL;
			 break;
		 default:
			 addChar();
			 lexError();
			 printf("Lexeme '%s' not in language\n", lexeme);
			 nextToken = EOF;
			 break;
	 }
	 return nextToken;
}

/******************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar(void) {
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = '\0';
	} else
	printf("Error - lexeme is too long \n");
}

/******************************************************/
/* getChar - a function to get the next character of
 input and determine its character class */
void getChar(void) {
	 if ((nextChar = getc(in_fp)) != EOF) {
		 if (isalpha(nextChar))
		 	charClass = LETTER;
		 else if (isdigit(nextChar))
		 	charClass = DIGIT;
		 else if (nextChar == '_'){
		 	charClass = UNDERSCORE;
		 }
		 else
		 	charClass = UNKNOWN;
	 } else
	 	charClass = EOF;
}

/******************************************************/
/* getNonBlank - a function to call getChar until it
 returns a non-whitespace character */
void getNonBlank(void) {
	while (isspace(nextChar))
	getChar();
}

/******************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions */
int lex(void) {
	 lexLen = 0;
	 getNonBlank();
	 switch (charClass) {
		/* Identifiers */
		 case LETTER:
			 addChar();
			 getChar();
			 while (charClass == LETTER || charClass == UNDERSCORE) {
				 addChar();
				 getChar();
			 }
			/* Keywords */
			if (!strcmp(lexeme, "TREVOR_LOOP")){
				printf("Loop found\n");
				nextToken = TREVOR_LOOP;
				break;
			}
			if (!strcmp(lexeme, "TREVOR_SELECTION")){
				printf("Selection found\n");
				nextToken = TREVOR_SELECTION;
				break;
			}
			if (!strcmp(lexeme, "TREVOR_ALT_SELECTION")){
				printf("Selection found\n");
				nextToken = TREVOR_ALT_SELECTION;
				break;
			}
			if (!strcmp(lexeme, "JUST_ONE_BYTE")){
				printf("JUST_ONE_BYTE found\n");
				nextToken = JUST_ONE_BYTE;
				break;
			}
			if (!strcmp(lexeme, "JUST_TWO_BYTES")){
				printf("JUST_TWO_BYTES found\n");
				nextToken = JUST_TWO_BYTES;
				break;
			}
			if (!strcmp(lexeme, "JUST_FOUR_BYTES")){
				printf("JUST_FOUR_BYTES found\n");
				nextToken = JUST_FOUR_BYTES;
				break;
			}
			if (!strcmp(lexeme, "JUST_EIGHT_BYTES")){
				printf("JUST_EIGHT_BYTES found\n");
				nextToken = JUST_EIGHT_BYTES;
				break;
			}
			/* Variable names must be 6-8 characters long */
			if (lexLen < 6){
				printf("%s is too short to be a valid name\n", lexeme);
				printf("Variable names must be between 6 and 8 characters\n");
				lexError();
				break;
			} else if (lexLen > 8){
				printf("%s is too long to be a valid name\n", lexeme);
				printf("Variable names must be between 6 and 8 characters\n");
				lexError();
				break;
			}
			 nextToken = IDENT;
			 break;
		/* Integer literals */
		 case DIGIT:
			 addChar();
			 getChar();
			 while (charClass == DIGIT) {
				 addChar();
				 getChar();
			 }
			 nextToken = INT_LIT;
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
			 lexeme[3] = '\0';
		 	break;
	 } /* End of switch */
	 if(nextToken != EOF){
		printf("Next token is: %d, Next lexeme is %s\n",
		nextToken, lexeme);
		fprintf(out_fp, "%d", nextToken);
		fputc(' ',out_fp);
		lexemeCount++;
	 }else{
		printf("\nEnd of file\n");
		printf("\nLexeme count: %d\n", lexemeCount);
	 }
	 return nextToken;
} /* End of function lex */

/******************************************************/
/* lexError - a function to display that 
	there is a lexical error and stop the program */
void lexError(void) {
	lexicalError = true;
	printf("LEXICAL ERROR AT LEXEME %s \nSTOPPING EXECUTION NOW\n", lexeme);
	exit(1);
}
