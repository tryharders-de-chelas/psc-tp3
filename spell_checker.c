#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include "structs.h"

#define LINE_MAX 2056

Dictionary * dictionary_create();

void dictionary_add(Dictionary * dictionary, const char * filename);

int dictionary_lookup(Dictionary * dictionary, const char * word);

void dictionary_destroy(Dictionary * dictionary);


void check_text(Dictionary * dict, char * text_file){
    FILE * file = fopen(text_file, "r");
    if(file == NULL){
        printf("[error] - couldn't open the file");
        exit(EXIT_FAILURE);
    }
    char words[LINE_MAX];
    const char delims[] = " \n\t";

    while(fgets(words, sizeof(words), file)){
        char * word = strtok(words, delims);
        while(word != NULL){
            //TODO
            if(dictionary_lookup(dict, word) == FALSE){

            }
            word = strtok(NULL, delims);
        }
    }

}

void check_word(Dictionary * dict, char * word){
    if(dictionary_lookup(dict, word) == TRUE){
        printf("Every given word was found in the dictionary");
    } else {
        printf("word: %s position: 0;0\n", word);
    }
}

void spell_check(char * text_file, char * word, char ** wordlists, int num_wordlists){
    Dictionary * dict = dictionary_create();
    for(int i = 0; i < num_wordlists; ++i){
        dictionary_add(dict, wordlists[i]);
    }
    if(word == NULL){
        check_text(dict, text_file);
    } else {
        check_word(dict, word);
    }
}

int main(int argc, char * argv[]){
    char * word = NULL;
    char * text_file = NULL;
    char ** wordlists = NULL;
    int num_wordlist = 0;

    int errflg =  0;
    int opt;

    while((opt = getopt(argc, argv, "w:d:t:")) != -1){
        switch(opt){
            case 'd':
                wordlists = realloc(wordlists, (num_wordlist + 1) * sizeof(char *));
                if(wordlists == NULL){
                    printf("[error] - memory couldn't be allocated\n");
                    exit(EXIT_FAILURE);
                }
                wordlists[num_wordlist++] = optarg;
                break;
            case 't':
                text_file = optarg;
                break;
            case 'w':
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

        if((text_file != NULL && word != NULL) || (text_file == NULL && word == NULL)){
            printf("[error] - you have to provide one of the options: -w or -t\n");
            exit(EXIT_FAILURE);
        }

        spell_check(text_file, word, wordlists, num_wordlist);

        free(wordlists);
        return 0;
    }
}
