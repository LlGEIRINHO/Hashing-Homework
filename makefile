all: compile run

compile:
	g++ -Wall -std=c++17 hash.cpp -o main

clean:
	rm -f main movies.txt

run:
	./main