CC = gcc
CFLAGS = -Wall -Werror -fPIC $(shell pkg-config --cflags glib-2.0)
LDFLAGS = -lm $(shell pkg-config --libs glib-2.0)
SOURCES = Dictionary.c test_dict.c
OBJECTS = $(SOURCES:.c=.o)
OUT_DYNAMIC = dictionary_test_dynamic

all: run_dynamic

dynamic: CFLAGS += -fPIC
dynamic: $(OBJECTS)
	$(CC) -shared -o libdictionary.so $(OBJECTS) $(LDFLAGS)

dictionary_test_dynamic: dynamic $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUT_DYNAMIC) $(LDFLAGS)

run_dynamic: dictionary_test_dynamic
	./$(OUT_DYNAMIC) -f ./wordlist_test.txt -w sim

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) libdictionary.so $(OUT_DYNAMIC)
