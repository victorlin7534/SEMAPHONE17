default: ctrl.o main.o
	gcc -o test ctrl.o main.o
ctrl.o: ctrl.c
	gcc -c ctrl.c
main.o: main.c
	gcc -c main.c
clean:
	rm -f *~ *.o test* *out *exe
