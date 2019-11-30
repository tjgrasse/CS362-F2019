CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g dominion.o rngs.o interface.o $(CFLAGS)

test_helpers.o: test_helpers.c test_helpers.h
	gcc -c test_helpers.c -g $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o test_helpers.o
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o test_helpers.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o test_helpers.o
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o test_helpers.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o test_helpers.o
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o test_helpers.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o test_helpers.o
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o test_helpers.o $(CFLAGS)

unittest5: unittest5.c dominion.o rngs.o test_helpers.o
	gcc -o unittest5 unittest5.c -g dominion.o rngs.o test_helpers.o $(CFLAGS)

unittest6: unittest6.c dominion.o rngs.o test_helpers.o
	gcc -o unittest6 unittest6.c -g dominion.o rngs.o test_helpers.o $(CFLAGS)

unittest7: unittest7.c dominion.o rngs.o test_helpers.o
	gcc -o unittest7 unittest7.c -g dominion.o rngs.o test_helpers.o $(CFLAGS)

unittest8: unittest8.c dominion.o rngs.o test_helpers.o
	gcc -o unittest8 unittest8.c -g dominion.o rngs.o test_helpers.o $(CFLAGS)

unittest9: unittest9.c dominion.o rngs.o test_helpers.o
	gcc -o unittest9 unittest9.c -g dominion.o rngs.o test_helpers.o $(CFLAGS)

unittest10: unittest10.c dominion.o rngs.o test_helpers.o
	gcc -o unittest10 unittest10.c -g dominion.o rngs.o test_helpers.o $(CFLAGS)

all: playdom player 

unittests: unittest1 unittest2 unittest3 unittest4 unittest5 unittest6 unittest7 unittest8 unittest9 unittest10

unittestresults: unittests
	./unittest1 > unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./unittest5 >> unittestresults.out
	./unittest6 >> unittestresults.out
	./unittest7 >> unittestresults.out
	./unittest8 >> unittestresults.out
	./unittest9 >> unittestresults.out
	./unittest10 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm -f unittest1 unittest2 unittest3 unittest4 unittest5 unittest6 unittest7 unittest8 unittest9 unittest10
