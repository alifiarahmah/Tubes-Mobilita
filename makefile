CC=gcc -std=c99
TARGET=main.exe

all:
	$(CC) -o $(TARGET) main.c modules/wordmachine.c modules/charmachine.c

clean:
	rm $(TARGET)