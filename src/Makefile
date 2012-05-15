CC      = gcc
LDFLAGS = -g -Wall

all: etapa3

## Etapa 3
etapa3: nico


doc: Doxyfile $(HEAD1)
	doxygen Doxyfile

nico: lex.yy.c nico.tab.c tokens.h node.o main-nico.c lista.o symbol_table.o
	$(CC) $(LDFLAGS) -o nico lex.yy.c nico.tab.c main-nico.c node.o lista.o symbol_table.o -lfl

lex.yy.c: scanner.l tokens.h
	flex scanner.l

tokens.h: nico.tab.c

nico.tab.c: nico.y
	bison --defines=tokens.h nico.y

symbol_table.o: symbol_table.c symbol_table.h
	$(CC) $(LDFLAGS) -Wall -c symbol_table.c

lista.o: lista.c lista.h
	$(CC) $(LDFLAGS) -Wall -c lista.c

node.o: node.c node.h
	$(CC) $(LDFLAGS) -Wall -c node.c

clean:
	rm -f *.o lex.yy.? nico.tab.? tokens.h nico
