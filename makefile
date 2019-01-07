dmsc: main.o common.o
	g++ -g -fopenmp -O0 main.o common.o -o dmsc
main.o: main.cpp common.h
	g++ -g -fopenmp -O0 main.cpp -c
common.o: common.cpp common.h
	g++ -g -fopenmp -O0 common.cpp -c
clean:
	rm dmsc main.o common.o
