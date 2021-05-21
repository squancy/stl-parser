all: unitTests validatorTests stlInfoTest mainUnitTest
	rm -rf  *.o *.out

unitTests: helpers.o unitTests.o
	gcc helpers.o unitTests.o -o unitTests

validatorTests: helpers.o stlValidatorTests.o
	gcc helpers.o stlValidatorTests.o -o validatorTests

stlInfoTest: helpers.o calc.o stlInfoTest.o
	gcc helpers.o calc.o stlInfoTest.o -o stlInfoTest

mainUnitTest: helpers.o mainUnitTest.o
	gcc helpers.o mainUnitTest.o -o mainUnitTest

helpers.o: ../src/helpers.c
	gcc -c ../src/helpers.c -o helpers.o

calc.o: ../src/calc.c
	gcc -c ../src/calc.c -o calc.o

stlInfoTest.o: stlInfoTest.c
	gcc -c stlInfoTest.c -o stlInfoTest.o

mainUnitTest.o: mainUnitTest.c
	gcc -c mainUnitTest.c -o mainUnitTest.o

stlValidatorTests.o: stlValidatorTests.c
	gcc -c stlValidatorTests.c -o stlValidatorTests.o

unitTests.o: unitTests.c
	gcc -c unitTests.c -o unitTests.o
