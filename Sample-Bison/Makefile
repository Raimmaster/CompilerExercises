TARGET=sample2
EXPR_PARSER_SRC=expr_parser.cpp
EXPR_LEXER_SRC=expr_lexer.cpp
SRC_FILES=$(EXPR_PARSER_SRC) $(EXPR_LEXER_SRC) ast.cpp main.cpp
OBJ_FILES=${SRC_FILES:.cpp=.o}
.PHONY: clean

$(TARGET): $(OBJ_FILES)
	g++ -o $@ $(OBJ_FILES)

$(EXPR_LEXER_SRC): expression.l
	flex -o $@ $^

$(EXPR_PARSER_SRC): expr.y
	bison -rall --defines=tokens.h -o $@ $<

%.o: %.cpp tokens.h
	g++ -c -o $@ $<

run: $(TARGET)
	./$(TARGET) input.txt

run_alt: $(TARGET)
	./$(TARGET) alt_input.txt

clean:
	rm -f expr_parser.cpp expr_lexer.cpp
	rm -f *.o
	rm -f tokens.h
	rm -f $(TARGET)
	rm -f *.output
