#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "Dictionary.h"

Dictionary * dictionary_create();

void dictionary_add(Dictionary * dictionary, const char * filename);

int dictionary_lookup(Dictionary * dictionary, const char * word);

void dictionary_destroy(Dictionary * dictionary);

/*
void print_hash(gpointer key, gpointer value, gpointer user_data) {
    printf("Key: %p, Value: %p\n", key, value);

}

void dictionary_print(Dictionary *dict) {
    printf("Contents of the hash table:\n");
    g_hash_table_foreach(dict->hash_table, print_hash, NULL);

}
*/ 


int setup_env(const char * wordlist, const char * word){
    Dictionary * dict = dictionary_create();
    dictionary_add(dict, wordlist);
    int exists = dictionary_lookup(dict, word);
    //dictionary_print(dict);
    dictionary_destroy(dict);
    
    return exists;
}

int main(int argc, char * argv[]){
    char * wordlist = NULL;
    char * word = NULL;
    int errflg =  0;
    int opt;

    while((opt = getopt(argc, argv, "w:f:")) != -1){
        switch(opt){
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

    if(wordlist == NULL){
        printf("[error] - no wordlist was given\n");
        errflg++;
    }

    if(word == NULL){
        printf("[error] - no word was given\n");
        errflg++;
    }

    if(errflg)
        return 1;

    if(setup_env(wordlist, word) == TRUE){
        printf("[OK] - word '%s' found in file '%s\n'", word, wordlist);
        return TRUE;
    } else{
        printf("[ERROR]  - word '%s' not found in file '%s\n'", word, wordlist);
    }
    return FALSE;

}
