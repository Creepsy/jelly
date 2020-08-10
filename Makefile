sDir = src/
bDir = build/

test: test.cpp $(bDir)jelly_lexer.o $(sDir)jelly_lexer.h $(bDir)jelly_parser.o $(sDir)jelly_parser.h $(bDir)jelly_ast.o $(sDir)jelly_ast.h
	g++ test.cpp -o test $(bDir)jelly_lexer.o $(bDir)jelly_parser.o $(bDir)jelly_ast.o

$(bDir)jelly_lexer.o: $(sDir)jelly_lexer.cpp
	g++ -c $(sDir)jelly_lexer.cpp -o $(bDir)jelly_lexer.o

$(bDir)jelly_parser.o: $(sDir)jelly_parser.cpp
	g++ -c $(sDir)jelly_parser.cpp -o $(bDir)jelly_parser.o

$(bDir)jelly_ast.o: $(sDir)jelly_ast.cpp
	g++ -c $(sDir)jelly_ast.cpp -o $(bDir)jelly_ast.o