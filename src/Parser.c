#include "Parser.h"

void advanceToken(struct lexics * allLex, struct lexics *current){
    static int index = 0; // saves state and doesn't actually keep becoming zero. I know it's not thread safe but I don't use threads in this program so wahhhhh
    *current = allLex[index]; 
    ++index; 
}

_Bool assureToken(struct lexics actual, int expected){
    if(actual.token == expected){
        return TRUE; 
    }
    return FALSE; 
}

// arg-decl --> VARTYPE IDENTIFIER {COMMA VARTYPE IDENTIFIER}
_Bool arg_decl(struct lexics * allLex, struct lexics * current, int *index){
    while(1){
        printf("Current lexeme is %s\n", current->lexeme); 
        if(!assureToken(*current, VARTYPE)){
            return FALSE; 
        }
        advanceToken(allLex, current); 
        printf("Current lexeme is %s\n", current->lexeme); 
        if(!assureToken(*current, IDENTIFIER)){
            return FALSE; 
        }
        advanceToken(allLex, current); 
        printf("Current lexeme is %s\n", current->lexeme); 
        if(!assureToken(*current, COMMA)){
            break; 
        }
        advanceToken(allLex, current); 
    }
    return TRUE; 
}

// header --> VARTYPE IDENTIFIER LEFT_PARENTHESIS [arg-decl] RIGHT_PARENTHESIS
_Bool header(struct lexics * allLex, struct lexics *current, int *index){
    printf("Current lexeme is %s\n", current->lexeme); 
    if(!assureToken(*current, VARTYPE)){
        return FALSE; 
    }
    advanceToken(allLex, current); 
    if(!assureToken(*current, IDENTIFIER)){
        return FALSE; 
    }
    printf("Current lexeme is %s\n", current->lexeme); 
    advanceToken(allLex, current); 
    if(!assureToken(*current, LEFT_PARENTHESIS)){
        return FALSE; 
    }
    printf("Current lexeme is %s\n", current->lexeme); 
    advanceToken(allLex, current); 
    
    return arg_decl(allLex, current, index) && assureToken(*current, RIGHT_PARENTHESIS); 
}

_Bool statement(struct lexics *allLex, struct lexics * current, int *index){

}

_Bool statement_list(struct lexics * allLex, struct lexics * current, int *index){

}

_Bool body(struct lexics * allLex, struct lexics *current, int *index){
    if(!assureToken(*current, LEFT_BRACKET)) return FALSE; 
    advanceToken(allLex, current); 

    return TRUE; 
}

_Bool parser(struct lexics *allLex, int numberOfLexics){
    int index = 0; 
    struct lexics current; 
    advanceToken(allLex, &current);  

    return body(allLex, &current, &index) && header(allLex, &current, &index); 
}

