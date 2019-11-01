CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)

runtests: testme 
	./testme &> unittestresult.out
	gcov testme.c >> unittestresult.out
	cat testme.c.gcov >> unittestresult.out

all: testme

clean:
	rm -f *.o *.gcno *.gcov *.gcda *.out testme
