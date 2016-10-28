cc=gcc
cflags=-Wall -Wextra -pedantic -std=c99 -g

hashtable.o: hashtable.c hashtable.h
	$(cc) $(cflags) -c hashtable.c -o hashtable.o
	
hashtable_test: hashtable.o hashtable_test.c
	$(cc) $(cflags) hashtable.o hashtable_test.c -o hashtable_test

lex.o: lex.c lex.h
	$(cc) $(cflags) -c lex.c -o lex.o
	
lex_test: lex.o lex_test.c
	$(cc) $(cflags) lex.o lex_test.c -o lex_test

parse.o: parse.c parse.h
	$(cc) $(cflags) -c parse.c -o parse.o
	
parse_test: parse.o parse_test.c hashtable.o lex.o
	$(cc) $(cflags) parse.o lex.o hashtable.o parse_test.c -o parse_test

test: parse_test hashtable_test lex_test
	./parse_test
	
clean:
	-rm -rf lex_test lex.o parse.o parse_test hashtable_test hashtable.o
	
PHONY: test clean
