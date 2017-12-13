CFLAGS	= -g -Wall `mysql_config --cflags --libs`

main: ponuda.o ponuda.h main.c main.h
	gcc -o $@ $^ $(CFLAGS)

ponuda.o: ponuda.c ponuda.h
	gcc -o $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -rf *~ *.o