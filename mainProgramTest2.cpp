#include "rda.cpp"

/******************************************************/
/* main driver */
int main(int argc, char *argv[]) {
    if (argc != 2){
	 	printf("ERROR - must supply filename of input to be read\n");
        return 1;
    }
	/* Open the input data file and process its contents */
	 if ((in_fp = fopen(argv[1], "r")) == NULL){
	 	printf("ERROR - cannot open %s\n", argv[1]);
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