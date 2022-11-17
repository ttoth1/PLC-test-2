/* front.cpp - a lexical analyzer system for simple
 arithmetic expressions */
#include <stdio.h>
#include <ctype.h>

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

/* Function declarations */
int lookup(char ch);
void addChar(void);
void getChar(void);
void getNonBlank(void);
int lex(void);

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
#define NOT 34
#define LEFT_BRACKET 35
#define RIGHT_BRACKET 36
#define UNDERSCORE 37

/******************************************************/
/* main driver */
int main(void) {
	/* Open the input data file and process its contents */
	 if ((in_fp = fopen("front.in", "r")) == NULL){
	 	printf("ERROR - cannot open front.in \n");
		return 1;
	 }
	 if ((out_fp= fopen("tokenList.txt", "w")) == NULL){
	 	printf("ERROR - cannot open tokenList.txt \n");
        return 1;
     }
	 else {
	 	getChar();
	 do {
	 	lex();
	 } while (nextToken != EOF);
	 }
	 return 0;
}
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
			 nextToken = NOT;
			 break;
		 case '_':
			 addChar();
			 nextToken = UNDERSCORE;
			 break;
		 default:
			 addChar();
			 printf("Error - lexeme '%s' not in language\n", lexeme);
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
			//  TODO: add check here against keywords and assign as such if appropriate
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
	 }else{
		printf("End of file\n");
	 }
	// fputc(nextChar, out_fp);
	// fputc(' ',out_fp);
	 return nextToken;
} /* End of function lex */