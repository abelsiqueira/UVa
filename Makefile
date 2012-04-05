all:
	g++ -o main main.cpp -lm -lcrypt -O2 -pipe -DONLINE_JUDGE
	time ./main < test1.in > test1.out
	diff -s test1.sol test1.out
	rm -f main

test:
	g++ -o main main.cpp -lm -lcrypt -O2 -pipe -DONLINE_JUDGE
	time ./main < test2.in > test2.out
	diff -s test2.sol test2.out
	rm -f main
