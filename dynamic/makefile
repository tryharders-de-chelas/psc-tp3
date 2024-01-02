CC = gcc
CFLAGS = -Wall -Werror $(shell pkg-config --cflags glib-2.0)
LDFLAGS = -lm $(shell pkg-config --libs glib-2.0)
SOURCES = Dictionary.c test_dict.c
OBJECTS = $(SOURCES:.c=.o)
OUT = dictionary_test_dynamic

run: run_dynamic

dynamic: $(OBJECTS)
	$(CC) -shared -o libdictionary.so $(OBJECTS) $(LDFLAGS)

dictionary_test_dynamic: dynamic $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUT) $(LDFLAGS)

run_dynamic: dictionary_test_dynamic
	./$(OUT) -f ./wordlist_test.txt -w sim

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) libdictionary.so $(OUT)
