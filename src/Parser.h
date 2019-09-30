#ifndef PARSER_H
#define PARSER_H

#include "Givens.h"
#include <stdio.h>

_Bool body(struct lexics * allLex, struct lexics *current, int *index); 
_Bool statement_list(struct lexics * allLex, struct lexics * current, int *index); 
_Bool statement(struct lexics *allLex, struct lexics * current, int *index); 
_Bool parser(struct lexics *someLexics, int numberOfLexics);

#endif