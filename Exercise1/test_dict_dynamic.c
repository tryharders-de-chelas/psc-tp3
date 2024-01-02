#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <dlfcn.h>
#include "Dictionary.h"

typedef struct Dictionary Dictionary;

Dictionary *(*create_function)();
void (*add_function)(Dictionary *, const char *);
int (*lookup_function)(Dictionary *, const char *);
void (*destroy_function)(Dictionary *);
GList *(*get_function)(Dictionary *, const char *);
void (*add_word_function)(Dictionary *, const char *, Position *);

void *load_library() {
    void *libHandle = dlopen("./libdictionary.so", RTLD_LAZY);

    if (!libHandle) {
        fprintf(stderr, "Error loading library: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    create_function = (Dictionary *(*)(void))dlsym(libHandle, "dictionary_create");
    add_function = (void (*)(Dictionary *, const char *))dlsym(libHandle, "dictionary_add");
    lookup_function = (int (*)(Dictionary *, const char *))dlsym(libHandle, "dictionary_lookup");
    destroy_function = (void (*)(Dictionary *))dlsym(libHandle, "dictionary_destroy");
    get_function = (GList *(*)(Dictionary *, const char *))dlsym(libHandle, "dictionary_get");
    add_word_function = (void (*)(Dictionary *, const char *, Position *))dlsym(libHandle, "dictionary_add_word");

    if (!create_function || !add_function || !lookup_function || !destroy_function || !get_function || !add_word_function) {
        fprintf(stderr, "Error obtaining function pointers: %s\n", dlerror());
        dlclose(libHandle);
        exit(EXIT_FAILURE);
    }
    return libHandle;
}

void unload_library(void *lib) {
    dlclose(lib);
}

int main(int argc, char *argv[]) {
    char *wordlist = NULL;
    char *word = NULL;
    int errflg = 0;
    int opt;

    while ((opt = getopt(argc, argv, "w:f:")) != -1) {
        switch (opt) {
            case 'f':
                printf("filename: %s\n", optarg);
                wordlist = optarg;
                break;
            case 'w':
                printf("word: %s\n", optarg);
                word = optarg;
                break;
            case ':':
                printf("[error] - option needs a value\n");
                errflg++;
                break;
            case '?':
                printf("[error] - unknown option: %c\n", optopt);
                errflg++;
                break;
        }
    }

    if (wordlist == NULL) {
        printf("[error] - no wordlist was given\n");
        errflg++;
    }

    if (word == NULL) {
        printf("[error] - no word was given\n");
        errflg++;
    }

    if (errflg)
        return 1;

    void *lib = load_library();  // Load the shared library

    Dictionary *dict = create_function();  // Create a dictionary

    // Call dictionary-related functions using function pointers
    add_function(dict, wordlist);
    int exists = lookup_function(dict, word);

    // Unload the shared library
    unload_library(lib);

    if (exists) {
        printf("[OK] - word '%s' found in file '%s\n'", word, wordlist); 
    } else {
        printf("[ERROR]  - word '%s' not found in file '%s\n'", word, wordlist);
    }
     return EXIT_SUCCESS;
}
