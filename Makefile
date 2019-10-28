CFLAGS=-DDEBUG -g -std=c++14
proj=predictors

all: $(proj).o
	g++ -g $(proj).o -o $(proj)

$(proj).o: p1.cpp
	g++ -c $(CFLAGS) p1.cpp -o predictors.o

run: all
	./$(proj) short_trace1.txt output.txt

clean:
	rm -rf *.o $(proj)
