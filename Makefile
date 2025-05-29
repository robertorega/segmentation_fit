segmentation_fit: main.c coda.o hash.o pila.o utile_coda.o utile_hash.o test_programma.o
	gcc -Wall -g main.c coda.o hash.o pila.o utile_coda.o utile_hash.o test_programma.o -o segmentation_fit

segmentation_fit_test: main_test.c coda.o hash.o pila.o utile_coda.o utile_hash.o test_programma.o
	gcc -Wall -g main_test.c coda.o hash.o pila.o utile_coda.o utile_hash.o test_programma.o -o segmentation_fit_test

coda.o: coda.h coda.c
	gcc -Wall -g -c coda.c -o coda.o

hash.o: hash.h hash.c
	gcc -Wall -g -c hash.c -o hash.o

pila.o: pila.h pila.c
	gcc -Wall -g -c pila.c -o pila.o

utile_coda.o: utile_coda.h utile_coda.c
	gcc -Wall -g -c utile_coda.c -o utile_coda.o

utile_hash.o: utile_hash.h utile_hash.c
	gcc -Wall -g -c utile_hash.c -o utile_hash.o

test_programma.o: test_programma.h test_programma.c
	gcc -Wall -g -c test_programma.c -o test_programma.o

clean:
	rm -f *.o segmentation_fit segmentation_fit_test
