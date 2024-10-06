CC = gcc
CFLAGS = -Wall -pthread
TARGET = fire_simulation

all: $(TARGET)

$(TARGET): main.c functions.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c functions.c

clean:
	rm -f $(TARGET)
