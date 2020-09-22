#CFB TEA

CFBTEA.out: main.o header.h CFBOperations.o TEA.o bitOperations.o fileIO.o
	g++ -o CFBTEA.out main.o header.h CFBOperations.o TEA.o bitOperations.o fileIO.o

main.o: main.o header.h CFBOperations.o TEA.o bitOperations.o fileIO.o
	g++ -c main.cpp

CFBOperations.o: CFBOperations.cpp header.h 
	g++ -c CFBOperations.cpp

TEA.o: TEA.cpp header.h 
	g++ -c TEA.cpp

bitOperations.o: bitOperations.cpp header.h 
	g++ -c bitOperations.cpp

fileIO.o: fileIO.cpp header.h
	g++ -c fileIO.cpp

clean:
	rm *.o CFBTEA.out
