.ONESHELL:
.PHONY: main distclean

objs = %.o
main: main.o
	gcc -o main.o main

main.o: main.c
	gcc -c main.c main.o

distclean:
	@-rm *.o
	@-rm *.so
	@echo clean over
