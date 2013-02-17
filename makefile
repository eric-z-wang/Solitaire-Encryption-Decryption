sol : sol.o reading.o card.o
	gcc -Wall -g -o $@ $^

sol.o : sol.c
	gcc -Wall -g -c $<

%.o : %.c %.h
	gcc -Wall -g -c $<

clean :
	rm sol *.o 