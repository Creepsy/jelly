srcDir = src/
bDir = build/

jelly: $(srcDir)jelly.cpp $(bDir)jelly_lexer.o
	g++ $(srcDir)jelly.cpp -o jelly $(bDir)jelly_lexer.o

$(bDir)jelly_lexer.o: $(srcDir)jelly_lexer.cpp $(srcDir)jelly_lexer.h $(srcDir)tokens.h
	g++ -c $(srcDir)jelly_lexer.cpp -o $(bDir)jelly_lexer.o