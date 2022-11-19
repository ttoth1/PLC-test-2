#include "rda.cpp"

/******************************************************/
/* main driver */
int main(void) {
	/* Open the input data file and process its contents */
	 if ((in_fp = fopen("front.in", "r")) == NULL){
	 	printf("ERROR - cannot open front.in \n");
		return 1;
	 }
	 if ((out_fp = fopen("tokenList.txt", "w")) == NULL){
	 	printf("ERROR - cannot open tokenList.txt \n");
        return 1;
     }
	 else {
	 	getChar();
	 do {
	 	lex();
        program();
	 } while ((nextToken != EOF) && !lexicalError && !syntError);
	 }
     if (!lexicalError && !syntError){
        printf("\n-----------------------------\n");
        printf("\nProgram successfully completed without errors.\n");
        printf("\n-----------------------------\n");
     }
	 fclose(in_fp);
	 fclose(out_fp);
	 return 0;
}