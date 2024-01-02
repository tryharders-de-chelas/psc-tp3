CC = gcc

CFLAGS = -Wall -Werror $(shell pkg-config --cflags glib-2.0)

LDFLAGS = -lm $(shell pkg-config --libs glib-2.0)

SOURCES = Dictionary.c test_dict.c

OBJECTS = $(SOURCES:.c=.o)

OUT_STATIC = dictionary_test_static

OUT_DYNAMIC = dictionary_test_dynamic



all: run_static run_dynamic



static: $(OBJECTS)

	ar rcs libdictionary.a $(OBJECTS)



dynamic: $(OBJECTS)

	$(CC) -shared -o libdictionary.so $(OBJECTS) $(LDFLAGS)



dictionary_test_static: static $(OBJECTS)

	$(CC) $(OBJECTS) -o $(OUT_STATIC) $(LDFLAGS)



dictionary_test_dynamic: dynamic $(OBJECTS)

	$(CC) $(OBJECTS) -o $(OUT_DYNAMIC) $(LDFLAGS)



run_static: dictionary_test_static

	./$(OUT_STATIC) -f ./wordlist_test.txt -w sim



run_dynamic: dictionary_test_dynamic

	./$(OUT_DYNAMIC) -f ./wordlist_test.txt -w sim



%.o: %.c

	$(CC) -c $(CFLAGS) $< -o $@



clean:

	rm -f $(OBJECTS) libdictionary.a libdictionary.so $(OUT_STATIC) $(OUT_DYNAMIC)

