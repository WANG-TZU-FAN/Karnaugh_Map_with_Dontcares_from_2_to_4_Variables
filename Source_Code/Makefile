E14061313_Logic_System_Kmap: main.o Simplifier.o map.o
	g++ -o E14061313_Logic_System_Kmap main.o Simplifier.o map.o

map.o: map.cpp map.h
	g++ -c map.cpp

Simplifier.o: Simplifier.cpp Simplifier.h map.h
	g++ -c Simplifier.cpp
	
main.o: main.cpp Simplifier.h map.h
	g++ -c main.cpp
clean:
	rm main *.o
