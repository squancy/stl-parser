stlp: main.o conv.o calc.o price.o helpers.o
	gcc main.o conv.o calc.o price.o helpers.o -o stlp
	rm -rf *.o

main.o: main.c
	gcc -c main.c -o main.o

conv.o: conv.c
	gcc -c conv.c -o conv.o

calc.o: calc.c
	gcc -c calc.c -o calc.o

price.o: price.c
	gcc -c price.c -o price.o

helpers.o: helpers.c
	gcc -c helpers.c -o helpers.o

main.c, conv.c, calc.c, price.c, helpers.c:
	echo "done"

clean:
	rm -rf *.o *.out
