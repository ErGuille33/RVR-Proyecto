CC=g++
CFLAGS=-g -std=c++11 -I.
DEPS = Socket.h Chat.h GameManager.h
OBJ = Socket.o Chat.o GameManager.o
LIBS=-lpthread 

%.o: %.cc $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

all: cs cc

cs: $(OBJ) ChatServer.o
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

cc: $(OBJ) ChatClient.o
	g++ -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f *.o cs cc

