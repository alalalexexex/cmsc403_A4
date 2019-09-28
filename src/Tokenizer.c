#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Tokenizer.h"

void addToLexics(struct lexics * aLex, int * numLex, char * lexeme){
    struct lexics current; 
    strcpy(current.lexeme, lexeme); 
    aLex[*numLex] = current;
    (*numLex)++; 
}

void parseBracket(struct lexics * aLex, char * p, int * numLex, char * bracket){
    int length; 

    //printf("the new string p is %s \n", p); 

    if((length = strcspn(p, bracket)) == 0){
        // only add paren
        printf("in first if with %s \n", p);
        addToLexics(aLex, numLex, bracket); 
    }else{
        // add before paren 
        char newLexeme[length]; 
        strncpy(newLexeme, p, length); 
        addToLexics(aLex, numLex, newLexeme);
        // add the actual paren
        addToLexics(aLex, numLex, bracket);
    }
    
    //printf("the difference is %ld \n", strlen(result) - length); 
    // i think I'm doing incorrect math
    strncpy(p, p + length +1, strlen(p) - length);
    //p = strtok(NULL, bracket); 
    // check if the next thing is blank
    if(p[0] == '\0' || p[0] == '\n' || p[0] == '\t'){
        p = strtok(NULL, " \t\n"); 
    }

    //printf("result is: %s\n",p); 
}
void lineParse(struct lexics * aLex, char * currLine, int *numLex){
    int start = 0; 
    //printf("line length is: %ld\n", strlen(currLine));
    int charCounter = 0; 
    for(int i =0; i < strlen(currLine); ++i){
        if(!isalpha(currLine[i])){
            if(charCounter == 0){
                continue; 
            }else{
                char * currentIdent = malloc(MY_CHAR_MAX * sizeof(char)); 
                currentIdent[MY_CHAR_MAX - 1] = '\0'; 
                strncpy(currentIdent, (currLine + i) - charCounter, charCounter); 
                printf("%s\n",  currentIdent); 
                free(currentIdent); 
            }
            charCounter = 0; 
            // char str[i - start +1]; 
            // str[i -start +1] = '\0';
            // strncpy(str, currLine + start, i - start + 1); 
            // printf("%s\n", str); 
            // start = i + 1; 
        }else if(isalpha(currLine[i])){
            charCounter ++; 
            //printf("%c", currLine[i]); 
        }
    }
    // char *p = strtok(currLine, " \t\n");
    // while(p != NULL){
    //     struct lexics current; 
    //     int length; 
    //     // check if p has  a bracket 
    //     if(strstr(p, "(") != NULL){
    //         parseBracket(aLex, p, numLex, "(");   
    //     }else if(strstr(p, ")") != NULL){
    //         parseBracket(aLex, p, numLex, ")");  
    //     }else if(strstr(p, "}") != NULL){
    //         parseBracket(aLex, p, numLex, "}");  
    //     }else if(strstr(p, "{") != NULL){
    //         parseBracket(aLex, p, numLex, "{");  
    //     }else if(strstr(p, "=") != NULL){
    //         parseBracket(aLex, p, numLex, "=");
    //     }else if(strstr(p, "+") != NULL){
    //         parseBracket(aLex, p, numLex, "+");
    //     }else if(strstr(p, ",") != NULL){
    //         parseBracket(aLex, p, numLex, ","); 
    //     }else if(strstr(p, ";") != NULL){
    //         parseBracket(aLex, p, numLex, ";");  
    //     }
    //     else{
    //         addToLexics(aLex, numLex, p); 
    //         p = strtok(NULL, " \t\n");
    //     }  
    //     printf("p is %s\n", p); 
    // }
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