CC ?= gcc
CFLAGS = -g -Wall
LDFLAGS = -l ncurses
TARGET ?= caesar-cipher

src = $(wildcard *.c)
obj = $(src:.c=.o)

$(TARGET): $(obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) $(TARGET)

