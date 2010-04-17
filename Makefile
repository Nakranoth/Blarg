CC = g++
CFLAGS = -g

all:
	$(CC) $(CFLAGS) -o a.out main.cc building.cc

clean:
	rm -f a.out