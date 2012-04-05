all:
	g++ -o main main.cpp
	./main < input.in
	rm -f main
