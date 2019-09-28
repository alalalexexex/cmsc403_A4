#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Tokenizer.h"

#define isDigit(c) ('0' <= c && c <= '9')
#define isLetter(c) ('a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' || c == '_')

void addToLexics(struct lexics * aLex, int * numLex, char * lexeme){
    struct lexics current; 
    strcpy(current.lexeme, lexeme); 
    aLex[*numLex] = current;
    (*numLex)++; 
}

char * getNumber(char * currLine, int * position){
    char * num = malloc(MY_CHAR_MAX * sizeof(char)); 
    num[MY_CHAR_MAX - 1] = '\0'; 
    int index = 0; 
    while(isDigit(currLine[*position])){
        num[index] = currLine[*position]; 
        index++; 
        (*position)++; 
    }
    (*position)--; 
    return num;  
}

char * getIdentifier(char * currLine, int * position){
    char * ident = malloc(MY_CHAR_MAX * sizeof(char)); 
    ident[MY_CHAR_MAX - 1] = '\0'; 
    int index = 0; 
    while(isLetter(currLine[*position])){
        ident[index] = currLine[*position]; 
        index++; 
        (*position)++; 
    }
    (*position)--; 
    return ident; 
}

char * makeSingleLex(char lex){
    char * single = malloc(2 * sizeof(char)); 
    single[0] = lex; 
    single[1] = '\0'; 
    return single; 
}

void lineParse(struct lexics * aLex, char * currLine, int *numLex){
    int start = 0; 
    int charCounter = 0; 
    for(int i =0; i < strlen(currLine); ++i){
        if(isLetter(currLine[i])){
            addToLexics(aLex, numLex, getIdentifier(currLine, &i));   
        }else if(isDigit(currLine[i])){
            addToLexics(aLex, numLex, getNumber(currLine, &i)); 
        }else if(currLine[i] == '{'){
            addToLexics(aLex, numLex, makeSingleLex(currLine[i])); 
        }else if(currLine[i] == ';'){
            addToLexics(aLex, numLex, makeSingleLex(currLine[i])); 
        }else if(currLine[i] == ','){
            addToLexics(aLex, numLex, makeSingleLex(currLine[i])); 
        }else if(currLine[i] == '}'){
            addToLexics(aLex, numLex, makeSingleLex(currLine[i])); 
        }else if(currLine[i] == '('){
            addToLexics(aLex, numLex, makeSingleLex(currLine[i])); 
        }else if(currLine[i] == ')'){
            addToLexics(aLex, numLex, makeSingleLex(currLine[i])); 
        }
    }
}

_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf){
    char str[MY_CHAR_MAX]; 
    
    while(fgets(str, MY_CHAR_MAX, inf) != NULL){ 
        lineParse(aLex, str, numLex); 
    }
     
    return FALSE; 
}

// How to procede?
// Get each line, delimit by space 
// check for parens, then if ( check for anything inside parens 
// check for ) 