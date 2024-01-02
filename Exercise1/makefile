CC = gcc
CFLAGS = -Wall -Werror -ggdb3 -fPIC $(shell pkg-config --cflags glib-2.0)
LDFLAGS = -lm -ggdb3 $(shell pkg-config --libs glib-2.0)
SOURCES_STATIC = Dictionary.c test_dict_static.c utils.c
SOURCES_DYNAMIC = Dictionary.c test_dict_dynamic.c utils.c
OBJECTS = $(SOURCES_STATIC:.c=.o)
OUT_STATIC = test_dict_static
OUT_DYNAMIC = test_dict_dynamic

run: clean run_static run_dynamic

static: $(OBJECTS)
	ar rcs libdictionary.a $(OBJECTS)

dynamic: CFLAGS += -fPIC
dynamic: $(OBJECTS)
	$(CC) -shared -o libdictionary.so $(OBJECTS) $(LDFLAGS)

dictionary_test_dynamic: dynamic $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUT_DYNAMIC) $(LDFLAGS)

dictionary_test_static: static $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUT_STATIC) $(LDFLAGS) -L. -ldictionary

run_dynamic: dictionary_test_dynamic
	./$(OUT_DYNAMIC) -f ./wordlist_test.txt -w sim

run_static: dictionary_test_static
	./$(OUT_STATIC) -f ./wordlist_test.txt -w sim

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) libdictionary.a libdictionary.so $(OUT_STATIC) $(OUT_DYNAMIC)

.PHONY: valgrind

valgrind_dynamic: run_dynamic
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(OUT_DYNAMIC) -f ./wordlist_test.txt -w sim

valgrind_static: run_static
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(OUT_STATIC) -f ./wordlist_test.txt -w sim
