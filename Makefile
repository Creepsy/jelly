srcDir = src/
bDir = build/

jelly: $(srcDir)jelly.cpp $(bDir)jelly_lexer.o $(bDir)jelly_parser.o $(bDir)arithmetric_parser.o $(bDir)branch.o
	g++ $(srcDir)jelly.cpp -o jelly $(bDir)jelly_lexer.o $(bDir)jelly_parser.o $(bDir)arithmetric_parser.o $(bDir)branch.o

$(bDir)jelly_lexer.o: $(srcDir)jelly_lexer.cpp $(srcDir)jelly_lexer.h $(srcDir)tokens.h
	g++ -c $(srcDir)jelly_lexer.cpp -o $(bDir)jelly_lexer.o

$(bDir)jelly_parser.o: $(srcDir)jelly_parser.cpp $(srcDir)jelly_parser.h $(bDir)jelly_lexer.o $(srcDir)branch.h $(bDir)arithmetric_parser.o
	g++ -c $(srcDir)jelly_parser.cpp -o $(bDir)jelly_parser.o

$(bDir)arithmetric_parser.o: $(srcDir)arithmetric_parser.cpp $(srcDir)arithmetric_parser.h $(srcDir)branch.h
	g++ -c $(srcDir)arithmetric_parser.cpp -o $(bDir)arithmetric_parser.o

$(bDir)branch.o: $(srcDir)branch.cpp $(srcDir)branch.h 
	g++ -c $(srcDir)branch.cpp -o $(bDir)branch.o