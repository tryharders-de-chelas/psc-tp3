CC = gcc
CFLAGS = -Wall -Werror $(shell pkg-config --cflags glib-2.0)
LDFLAGS = -lm $(shell pkg-config --libs glib-2.0)
SOURCES = Dictionary.c test_dict.c
OBJECTS = $(SOURCES:.c=.o)
OUT = test_dict

test: clean
	echo "Tested successfully"

clean: run
	rm -f $(OBJECTS) $(OUT)

run: compile
	chmod +x $(OBJECTS)
	./test_dict -f ./wordlist.txt -w palavra

compile: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUT) $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

