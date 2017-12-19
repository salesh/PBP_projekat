CFLAGS	= -g -Wall `mysql_config --cflags --libs`

main: klijent.o ponuda.o main.c
	gcc -o $@ $^ $(CFLAGS)

ponuda.o: ponuda.c ponuda.h
	gcc -o $(CFLAGS) -c -o $@ $<

radnik.o: klijent.c klijent.h
	gcc -o $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -rf *~ *.o