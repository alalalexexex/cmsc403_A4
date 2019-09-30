#include <unistd.h>
#include <stdlib.h>
#include "Analyzer.h"

void printInfo(struct lexics * allLexics, FILE * infile){
	int numberOfLexics = 0;
	printf("Did tokenize: %d\n",tokenizer(allLexics, &numberOfLexics, infile));
	printf("Number of lexemes: %d\n",numberOfLexics);
	printf("Lexemes: ");
	for(int i = 0; i < numberOfLexics; i++){
		printf(" %s ",allLexics[i].lexeme);
	}
	printf("\n");
	printf("Did parse: %d\n",parser(allLexics, numberOfLexics));
	printf("\n"); 
}

int main(){
	//initialize file pointer to NULL 
	FILE *infile = NULL; 

	//Define a character array to store the name of the file to read and write
	char filename[MY_CHAR_MAX];  
	int count = 0; 
	//Prompt the user to input a filename and continue to prompt the user until they enter a correct one
	while(infile == NULL /*|| count <= 8*/) {  
		//printf("Enter filename: ");  
		//scanf("%s",filename);
		//When given a filename, use fopen to create a new file pointer. 
			//If fopen can not find the file, it returns null
		sprintf(filename, "./TokenTests/tokenTest%d.txt", count); 
		infile = fopen("tt.txt", "r+");
		if(infile == NULL){ 
			printf("ERROR: file %s cannot be opened\n", filename);
	  	}
		
		struct lexics allLexics[1024];
		printInfo(allLexics, infile); 
		count++; 

	}




	// struct lexics allLexics[1024];
	// int numberOfLexics = 0;
	// printf("Did tokenize: %d\n",tokenizer(allLexics, &numberOfLexics, infile));
	// printf("Number of lexemes: %d\n",numberOfLexics);
	// printf("Lexemes: ");
	// for(int i = 0; i < numberOfLexics; i++){
	// 	printf(" %s ",allLexics[i].lexeme);
	// }
	// printf("\n");
	// printf("Did parse: %d\n",parser(allLexics, numberOfLexics));

}