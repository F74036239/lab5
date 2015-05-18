main: main.o HugeInt.o
	g++ -o main main.o HugeInt.o
HugeInt.o: HugeInt.cpp HugeInt.h
	g++ -c HugeInt.cpp
main.o: main.cpp HugeInt.h
	g++ -c main.cpp
clean:
	rm main *.o
