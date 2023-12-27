CC = gcc
CFLAGS = -Wall -Werror $(shell pkg-config --cflags glib-2.0)
LDFLAGS = -lm $(shell pkg-config --libs glib-2.0)
SOURCES = Dictionary.c test_dict.c
OBJECTS = $(SOURCES:.c=.o)
OUT = test_dict

all: test static dynamic

test: clean
    echo "Tested successfully"

clean: run
    rm -f $(OBJECTS) $(OUT) libdictionary.a libdictionary.so

run: compile
    chmod +x $(OBJECTS)
    ./test_dict -f ./wordlist.txt -w sim

compile: $(OBJECTS)
    $(CC) $(OBJECTS) -o $(OUT) $(LDFLAGS)

static: $(OBJECTS)
    ar rcs libdictionary.a $(OBJECTS)

dynamic: $(OBJECTS)
    $(CC) -shared -o libdictionary.so $(OBJECTS) $(LDFLAGS)

%.o: %.c
    $(CC) -c $(CFLAGS) $< -o $@
