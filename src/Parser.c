#include <stdlib.h>

#include "Parser.h"

void advanceToken(struct lexics * allLex, struct lexics *current, int * index){// saves state and doesn't actually keep becoming zero. I know it's not thread safe but I don't use threads in this program so wahhhhh
    *current = allLex[*index]; 
   (*index)++; 
    printf("index is %d:", *index); 
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
        advanceToken(allLex, current, index); 
        printf("Current lexeme is %s\n", current->lexeme); 
        if(!assureToken(*current, IDENTIFIER)){
            return FALSE; 
        }
        advanceToken(allLex, current, index); 
        printf("Current lexeme is %s\n", current->lexeme); 
        if(!assureToken(*current, COMMA)){
            break; 
        }
        advanceToken(allLex, current, index); 
    }
    return TRUE; 
}

// header --> VARTYPE IDENTIFIER LEFT_PARENTHESIS [arg-decl] or more RIGHT_PARENTHESIS
_Bool header(struct lexics * allLex, struct lexics *current, int *index){
    if(!assureToken(*current, VARTYPE)){
        return FALSE; 
    }
    advanceToken(allLex, current, index); 
    if(!assureToken(*current, IDENTIFIER)){
        return FALSE; 
    }
    advanceToken(allLex, current, index); 
    if(!assureToken(*current, LEFT_PARENTHESIS)){
        return FALSE; 
    }
    advanceToken(allLex, current, index); 

    if(!arg_decl(allLex, current, index)) return FALSE; 
    if(!assureToken(*current, RIGHT_PARENTHESIS)) return FALSE; 

    advanceToken(allLex, current, index); 
    return TRUE; 
}

_Bool term(struct lexics *allLex, struct lexics * current, int *index){
    return assureToken(*current, IDENTIFIER) || assureToken(*current, NUMBER); 
}

// expression --> term {BINOP term} | LEFT_PARENTHESIS expression RIGHT_PARENTHESIS
_Bool expression(struct lexics *allLex, struct lexics * current, int *index){
    if(term(allLex, current, index)){
        advanceToken(allLex, current, index); 
        while(assureToken(*current, BINOP)){
            advanceToken(allLex, current, index); 
            if(!term(allLex, current, index)) return FALSE; 
            advanceToken(allLex, current, index); 
        }
        return TRUE; 
    }else{
        if(!assureToken(*current, LEFT_PARENTHESIS)) return FALSE; 
        advanceToken(allLex, current, index); 
        expression(allLex, current, index); 
        if(!assureToken(*current, RIGHT_PARENTHESIS)) return FALSE; 
    }

    return TRUE; 
}

// assignment --> IDENTIFIER EQUAL expression EOL
_Bool assignment(struct lexics *allLex, struct lexics * current, int *index){
    advanceToken(allLex, current, index); // get past initial key
    if(!assureToken(*current, EQUAL)) return FALSE; 
    advanceToken(allLex, current, index); 
    if(!expression(allLex, current, index)) return FALSE; 

    if(!assureToken(*current, EOL)) return FALSE; 
    advanceToken(allLex, current, index); 

    return TRUE; 

}

_Bool return_stmt(struct lexics *allLex, struct lexics * current, int *index){
    advanceToken(allLex, current, index); // get past initial key

}

_Bool while_loop(struct lexics *allLex, struct lexics * current, int *index){
    advanceToken(allLex, current, index); // get past initial key

}

// body --> LEFT_BRACKET [statement-list] RIGHT_BRACKET
_Bool body(struct lexics * allLex, struct lexics *current, int *index){
    if(!assureToken(*current, LEFT_BRACKET)) return FALSE; 
    advanceToken(allLex, current, index); 

    // go to statement_list until last bracket is found 
    statement_list(allLex, current, index);  
    printf("curr lexeme is %s\n", current->lexeme);

    // then check if index is the last lexeme and is a right bracket  
    if(!assureToken(*current, RIGHT_BRACKET)) return FALSE; 
    (*index)++; 

    return TRUE; 
}

//statement --> while-loop | return | assignment | body
_Bool statement(struct lexics *allLex, struct lexics * current, int *index){
    printf("curr lexeme is %s\n", current->lexeme);
    if(assureToken(*current, WHILE_KEYWORD)) return while_loop(allLex, current, index); 
    else if (assureToken(*current, RETURN_KEYWORD)) return return_stmt(allLex, current, index); 
    else if(assureToken(*current, IDENTIFIER)) return assignment(allLex, current, index); 
    else if(assureToken(*current, LEFT_BRACKET)) return body(allLex, current, index); 
    else {
        return FALSE; 
    } 
}
// statement-list --> statement {statement}
void statement_list(struct lexics * allLex, struct lexics * current, int *index){
    while(statement(allLex, current, index)){
    }
    return; 
}

_Bool parser(struct lexics *allLex, int numberOfLexics){
    int index = 0; 
    struct lexics current; 
    advanceToken(allLex, &current, &index);  

    if(!header(allLex, &current, &index)) return FALSE; 
    if(!body(allLex, &current, &index)) return FALSE; 

    printf("index was: %d, numberOfLexics was : %d", index-1, numberOfLexics); 

    return (index-1) == numberOfLexics; 
}

