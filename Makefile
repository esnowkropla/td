CC=clang
CFLAGS=-Weverything -g -c -std=c11 
LDFLAGS=
EXE=td

all: td.o
	$(CC) -o $(EXE) $(LDFLAGS) td.o

%.o : %.c %.h
	$(CC) $(CFLAGS) $<

clean:
	rm -r *.o $(EXE)

run:
	./$(EXE)
