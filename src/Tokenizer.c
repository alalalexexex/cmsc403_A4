#include <string.h>
#include "Tokenizer.h"

_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf){
    char str[MY_CHAR_MAX]; 
    
    while(fgets(str, MY_CHAR_MAX, inf) != NULL){ 
        // create a lexics struct 
        strcpy(aLex[*numLex].lexeme, str);  
        ++ *numLex; 
    }
     
    return FALSE; 
}