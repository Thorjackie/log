all: test run

clean: test
	rm test

test: test.c
	gcc -o test test.c

run: test
	./test
