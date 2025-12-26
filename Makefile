
CC = cc
CFLAGS = -Wall -Wextra -O2 -g
SRC = $(wildcard src/*.c)
OBJ = $(patsubst %.c,%.o,$(SRC))
TARGET = shut-the-box
LDLIBS = -lm

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDLIBS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
