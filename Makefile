CC=gcc
CFLAGS=-c -std=c99 -g
SRC= src
OBJ = obj

default: parse

parse: $(OBJ)/Analyzer.o $(OBJ)/Givens.o $(OBJ)/Tokenizer.o $(OBJ)/Parser.o
	$(CC)  $(OBJ)/Analyzer.o  $(OBJ)/Givens.o  $(OBJ)/Tokenizer.o  $(OBJ)/Parser.o -o parse

$(OBJ)/Analyzer.o: $(SRC)/Analyzer.c
	$(CC) -I$(SRC) $(CFLAGS) $< -o $@

$(OBJ)/Givens.o: $(SRC)/Givens.c 
	$(CC) $(CFLAGS) -I$(SRC) $< -o $@

$(OBJ)/Tokenizer.o: $(SRC)/Tokenizer.c 
	$(CC) -I$(SRC) $(CFLAGS) $< -o $@

$(OBJ)/Parser.o: $(SRC)/Parser.c 
	$(CC) -I$(SRC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJ)/*o parse