TARGET=minusc
EXPR_PARSER=expr_parser.cpp
EXPR_LEXER=expr_lexer.cpp
SRC_FILES=$(EXPR_PARSER) $(EXPR_LEXER) main.cpp
OBJ_FILES=${SRC_FILES:.cpp=.o}
.PHONY=clean
RM=rm -rf

$(TARGET): $(OBJ_FILES)
	g++ -std=c++11 -o $@ $<

$(EXPR_PARSER): grammar.y
	lemon -o$@ -dtokens.h -Tlempar.c $<

$(EXPR_LEXER): lexer.l
	flex -o $@ $<

%.o: %.cpp tokens.h
	g++ -c -std=c++11 -o $@ %<

run: $(TARGET)
	./$(TARGET) < input.txt

clean:
	$(RM) $(SRC_FILES) *.o tokens.h
