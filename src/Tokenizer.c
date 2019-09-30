#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Tokenizer.h"

#define isDigit(c) ('0' <= c && c <= '9')
#define isLetter(c) ('a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' || c == '_')
#define isWhite(c) (c == ' ' || c == '\t' || c == '\r' || c =='\n')

void addToLexics(struct lexics * aLex, int * numLex, char * lexeme, int x){
    struct lexics current; 
    strcpy(current.lexeme, lexeme);
    current.token = x;  
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
    ident[0] = currLine[*position]; 
    int index = 1;
    (*position)++; 
    while(validIdentifier(ident)){
        printf("here with the char %c\n", currLine[*position]);
        ident[index] = currLine[*position]; 
        index++; 
        (*position)++; 
    }
    ident[--index] = '\0'; 
    (*position) = (*position) - 2; 
    return ident; 
}

char * makeSingleLex(char lex){
    char * single = malloc(2 * sizeof(char)); 
    single[0] = lex; 
    single[1] = '\0'; 
    return single; 
}

_Bool lineParse(struct lexics * aLex, char * currLine, int *numLex){
    int start = 0; 
    int charCounter = 0; 
    for(int i =0; i < strlen(currLine); ++i){
        if(isLetter(currLine[i])){
            char * word = getIdentifier(currLine, &i); 
            int currTok = IDENTIFIER; 
            if(!strcmp(word, "int") || !strcmp(word, "void")){    
                currTok = VARTYPE; 
            }else if(!strcmp(word, "while")){
                currTok = WHILE_KEYWORD; 
            }else if(!strcmp(word, "return")){
                currTok = RETURN_KEYWORD; 
            }
            addToLexics(aLex, numLex, word, currTok);   
        }else if(isDigit(currLine[i])){
            addToLexics(aLex, numLex, getNumber(currLine, &i), NUMBER); 
        }else if(currLine[i] == '{'){
            addToLexics(aLex, numLex, makeSingleLex(currLine[i]), LEFT_BRACKET); 
        }else if(currLine[i] == ';'){
            addToLexics(aLex, numLex, makeSingleLex(currLine[i]), EOL); 
        }else if(currLine[i] == ','){
            addToLexics(aLex, numLex, makeSingleLex(currLine[i]), COMMA); 
        }else if(currLine[i] == '}'){
            addToLexics(aLex, numLex, makeSingleLex(currLine[i]), RIGHT_BRACKET); 
        }else if(currLine[i] == '('){
            addToLexics(aLex, numLex, makeSingleLex(currLine[i]), LEFT_PARENTHESIS); 
        }else if(currLine[i] == ')'){
            addToLexics(aLex, numLex, makeSingleLex(currLine[i]), RIGHT_PARENTHESIS); 
        }else if(currLine[i] == '+' || currLine[i] == '*' || currLine[i] == '%'){
            addToLexics(aLex, numLex, makeSingleLex(currLine[i]), BINOP); 
        }else if(currLine[i] == '!'){
            if(currLine[i+1] == '='){
                addToLexics(aLex, numLex, "!=", BINOP); 
                i++; 
            }
        }else if(currLine[i] == '='){
            if(currLine[i + 1] == '='){
                addToLexics(aLex, numLex, "==", BINOP); 
                i++; 
            }else{
                addToLexics(aLex, numLex, "=", EQUAL); 
            }
        }else if(isWhite(currLine[i])){
            continue; 
        }else{
            return FALSE; 
        }
    }
    return TRUE; 
}

_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf){
    char str[MY_CHAR_MAX]; 
    
    while(fgets(str, MY_CHAR_MAX, inf) != NULL){ 
        if(lineParse(aLex, str, numLex) == FALSE){
            return FALSE; 
        }
    }
     
    return TRUE; 
}

// How to procede?
// Get each line, delimit by space 
// check for parens, then if ( check for anything inside parens 
// check for ) 