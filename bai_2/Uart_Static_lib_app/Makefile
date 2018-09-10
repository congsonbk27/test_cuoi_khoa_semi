

uartapi.o : uartapi.c
	gcc -c -o uartapi.o uartapi.c
#	gcc -c -Wall uartapi.c -o uartapi.o
libmyuart.a: uartapi.c 	uartapi.h
	ar -crD libmyuart.a uartapi.o 
main : main.o 
	gcc main.c -L. -lmyuart -o main
