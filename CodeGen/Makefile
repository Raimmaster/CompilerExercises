TARGET=codegen.o
EXPR_PARSER=expr_parser.cpp
EXPR_LEXER=expr_lexer.cpp
SRC_FILES=$(EXPR_PARSER) $(EXPR_LEXER) main.cpp
OBJ_FILES=${SRC_FILES:.cpp=.o}
.PHONY=clean
RM=rm -rf

$(TARGET): $(OBJ_FILES)
	g++ -std=c++11 -o $@ $^

$(EXPR_PARSER): grammar.y
	lemon -o$@ -Tlempar.c -dtokens.h $<

$(EXPR_LEXER): lexer.l
	flex -o $@ $<

%.o: %.cpp tokens.h
	g++ -c -std=c++11 -o $@ %<

clean:
	$(RM) $(SRC_FILES) *.o tokens.h

run: $(TARGET)
	./$(TARGET) < test.cpp
