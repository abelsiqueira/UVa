all:
	g++ -o main main.cpp
	./main < test1.in > test1.out
	diff -s test1.out test1.sol
	rm -f main test1.out
