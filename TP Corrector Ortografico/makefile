CFLAGS += -g -Wall -Wextra -Werror

all: main

main: main.o glist.o diccionarioHash.o corregirPalabra.o leerPalabra.o
	$(CC) $(CFLAGS) $^ -o $@ -g

clean:
	rm -f *.o
	rm -f main

.PHONY = clean all