#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

Dictionary * dictionary_create();

void dictionary_add(Dictionary * dictionary, const char * filename);

int dictionary_lookup(Dictionary * dictionary, const char * word);

void dictionary_destroy(Dictionary * dictionary);

int setup_env(const char * wordlist, const char * word){
    Dictionary * dict = dictionary_create();
    dictionary_add(dict, wordlist);
    int exists = dictionary_lookup(dict, word);
    dictionary_destroy(dict);
    if(exists)
        return 0;
    return 1;
}

int main(int argc, char * argv[]){
    FILE * filepath = NULL;
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
        printf("[error] - no wordlist was given");
        errflg++;
    }

    if(word == NULL){
        printf("[error] - no word was given");
        errflg++;
    }

    if(errflg)
        return 1;

    if(setup_env(wordlist, word))
        printf("[OK] - word: %s, file: %s", word, filepath);
        return 0;
    return 1;

}