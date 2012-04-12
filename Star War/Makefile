all: compile run purge

compile:
	g++ -o main main.cpp -ggdb -Wall -Wextra -lm -lcrypt -O2 -pipe -DONLINE_JUDGE

run:
	./runtests.sh

purge:
	rm -f main *.out
