CC = gcc
CFLAGS = -Wall -Werror $(shell pkg-config --cflags glib-2.0)
LDFLAGS = -lm $(shell pkg-config --libs glib-2.0)
SOURCES = Dictionary.c test_dict.c
OBJECTS = $(SOURCES:.c=.o)
OUT = test_dict_static

run: run_static

static: $(OBJECTS)
	ar rcs libdictionary.a $(OBJECTS)

dictionary_test_static: static $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUT) $(LDFLAGS)

run_static: dictionary_test_static
	./$(OUT) -f ./wordlist_test.txt -w sim

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	rm -f $(OBJECTS) libdictionary.a $(OUT)

