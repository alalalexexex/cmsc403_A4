#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Tokenizer.h"

#define isDigit(c) ('0' <= c && c <= '9')
#define isLetter(c) ('a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' || c == '_')
#define isWhite(c) (c == ' ' || c == '\t' || c == '\r' || c =='\n')
#define isStructure(c) (c == '}' || c == '{' || c == ')' || c =='(' || c == '=' || c == '*' || c == '+' || c =='!' || c == ';' || c == ',')


/**
 * function to make it easier to add to the lexics
*/
void addToLexics(struct lexics * aLex, int * numLex, char * lexeme, int token){
    struct lexics current; 
    strcpy(current.lexeme, lexeme);
    current.token = token;  
    aLex[*numLex] = current;
    (*numLex)++; 
}

/**
 * function to build a number from the current input stream. Will stop when something 
 * that isn't a number is reached. 
*/
char * getNumber(char * currLine, int * position){
    char * num = malloc(MY_CHAR_MAX * sizeof(char)); 
    num[MY_CHAR_MAX - 1] = '\0'; 
    int index = 0; 
    while(isDigit(currLine[*position])){
        num[index] = currLine[*position]; 
        index++; 
        (*position)++; 
    }
    (*position)--; // decrement the position because we've gone one too far in the while loop
    return num;  
}

/**
 * function to build an identifier until something that can't be considered and is reserved
 * in the grammar. I didn't use validIdentifier, because that would assume we are only using 
 * valid identifiers. 
*/
char * getIdentifier(char * currLine, int * position){
    char * ident = malloc(MY_CHAR_MAX * sizeof(char)); // make new storage
    ident[0] = currLine[*position]; 
    int index = 1;
    (*position)++; 
    while(!isWhite(currLine[*position]) && !isStructure(currLine[*position])){
        ident[index] = currLine[*position]; 
        index++; 
        (*position)++; 
    }
    ident[index] = '\0'; 
    (*position)--; // decrement the position because we've gone one too far in the while loop
    return ident; 
}

/**
 * Creates a single char lexeme. This is beneficial because if 
 * I reach a valid single lexeme like a bracket, I can just create a 
 * lexeme instead of extracting it from the input stream. 
*/
char * makeSingleLex(char lex){
    char * single = malloc(2 * sizeof(char)); 
    single[0] = lex; 
    single[1] = '\0'; 
    return single; 
}

/**
 * Main function that goes through each character of the input stream. 
 * It is setup to only take in valid lexemes, and will return false if an 
 * invalid lexeme is found. 
 */
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
            // check to make sure that the lexeme is '!=' and not just '!'
            if(currLine[i+1] == '='){
                addToLexics(aLex, numLex, "!=", BINOP); 
                i++; // consumed more than one character
            }
        }else if(currLine[i] == '='){
            // check to see if we see a '==' or just '='
            if(currLine[i + 1] == '='){
                addToLexics(aLex, numLex, "==", BINOP); 
                i++; // consumed more than one character
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
    
    // fgets gets each line of the input stream
    while(fgets(str, MY_CHAR_MAX, inf) != NULL){ 
        if(lineParse(aLex, str, numLex) == FALSE){
            return FALSE; 
        }
    }
     
    return TRUE; 
}