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
	./spell_checker -d ./wordlist_test.txt -t ./words.txt

compile: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUT) $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

