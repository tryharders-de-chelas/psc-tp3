CC = gcc
CFLAGS = -Wall -Werror $(shell pkg-config --cflags glib-2.0)
LDFLAGS = -lm $(shell pkg-config --libs glib-2.0)
SOURCES = Dictionary.c spell_checker.c MinHeap.c
OBJECTS = $(SOURCES:.c=.o)
OUT = spell_checker

test: clean
	echo "Tested successfully"

clean: run
	rm -f $(OBJECTS) $(OUT)

run: compile
	chmod +x $(OBJECTS)
	./$(OUT) -d ./wordlist-ao-20101027.txt -t ./words.txt

compile: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUT) $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

PHONY: valgrind

valgrind: compile
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(OUT) -d ./wordlist-ao-20101027.txt -t words.txt
