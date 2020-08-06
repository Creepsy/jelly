sDir = src/
bDir = build/

test: $(bDir)jelly_lexer.o $(sDir)jelly_lexer.h
	g++ test.cpp -o test $(bDir)jelly_lexer.o

$(bDir)jelly_lexer.o: $(sDir)jelly_lexer.cpp
	g++ -c $(sDir)jelly_lexer.cpp -o $(bDir)jelly_lexer.o