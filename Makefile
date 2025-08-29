CC=gcc
CFLAGS=-O2 -Wall -Wextra -std=c11
TARGET=qs

all: $(TARGET)

$(TARGET): main.c src/quicksort.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c src/quicksort.c

clean:
	rm -f $(TARGET)
