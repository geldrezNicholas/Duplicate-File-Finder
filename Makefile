CC = gcc
CFLAGS = -Wall -Wextra -g -pthread -Iinclude 

SRC = src/main.c src/hash.c src/list.c
OBJ = $(SRC:.c=.o)
TARGET = dedup

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f src/*.o $(TARGET)