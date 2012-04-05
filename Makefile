all:
	g++ -o main main.cpp -lm -lcrypt -O2 -pipe -DONLINE_JUDGE
	time ./main < input.in
	rm -f main

test:
	g++ -o main main.cpp -lm -lcrypt -O2 -pipe -DONLINE_JUDGE
	time ./main < teste.in
	rm -f main
