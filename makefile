
#OBJECTS = main.o arena.o arith.o atom.o except.o fmt.o mem.o memchk.o stack.o
OBJECTS= main.o except.o fmt.o mem.o

test: $(OBJECTS)
	cc -o test $(OBJECTS)

main.o : main.c
	cc -c -g main.c

except.o : except.c
	cc -c -g except.c

fmt.o : fmt.c
	cc -c -g fmt.c

mem.o : mem.c
	cc -c -g mem.c


clean:
	rm *.o




































