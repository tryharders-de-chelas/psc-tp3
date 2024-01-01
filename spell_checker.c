#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include "structs.h"

#define LINE_MAX_LEN 2056

Dictionary * dictionary_create();

void dictionary_add(Dictionary * dictionary, char * word);

void dictionary_add_word(Dictionary * dictionary, char * word);

int dictionary_lookup(Dictionary * dictionary, const char * word);

void dictionary_destroy(Dictionary * dictionary);

MinHeap* createMinHeap();

void insert(MinHeap *minHeap, Position key, char * value);

char * extractMin(MinHeap *minHeap);

gboolean isEmpty(MinHeap *minHeap);

void minHeap_destroy(MinHeap *minHeap);

void print_list_element (gpointer data,gpointer user_data){
    Position * pos = data;
    printf("(%d; %d); ", pos->row, pos->column);
}

void check_text(Dictionary * dict,const char * text_file){
    FILE * file = fopen(text_file, "r");
    if(file == NULL){
        printf("[error] - couldn't open the file\n");
        exit(EXIT_FAILURE);
    }
    char words[LINE_MAX_LEN];
    const char delims[] = " \n\t";

    Dictionary * not_found_dict = dictionary_create();
    MinHeap * minHeap = createMinHeap();
    int row = 0;
    while(fgets(words, sizeof(words), file)){
        int column = 0;
        char * word = strtok(words, delims);
        while(word != NULL){
            if(dictionary_lookup(dict, word) == FALSE){
                printf("word right now: %s\n", word);
               if(dictionary_lookup(not_found_dict, word) == FALSE){
                   Position pos = {.row = row, .column = column};
                   insert(minHeap, pos, word);
               } else {
                   dictionary_add_word(not_found_dict, word);
               }
            }
            column++;
            word = strtok(NULL, delims);
        }
        row++;
    }
    fclose(file);

    while(!isEmpty(minHeap)){
        char * minStr = extractMin(minHeap);
        printf("%s\n", minStr);
        break;
        GList * positions = g_hash_table_lookup(not_found_dict->hash_table, minStr);
        printf("%s - ", minStr);
        g_list_foreach(positions, print_list_element, NULL);
        g_list_free(positions);
    }
    dictionary_destroy(not_found_dict);
    minHeap_destroy(minHeap);
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
    for(int i = 0; i < num_wordlists; i++){
        dictionary_add(dict, wordlists[i]);
    }
    if(word == NULL){
        printf("\n\n\nText file was provided\n\n\n");
        check_text(dict, text_file);
    } else {
        printf("\n\n\nSingle word given\n\n\n");
        check_word(dict, word);
    }
    dictionary_destroy(dict);
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
                printf("wordlist: %s\n", optarg);
                wordlists[num_wordlist++] = optarg;
                break;
            case 't':
                printf("text_file: %s\n", optarg);
                text_file = optarg;
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

    if((text_file != NULL && word != NULL) || (text_file == NULL && word == NULL)){
        printf("[error] - you have to provide one of the options: -w or -t\n");
        exit(EXIT_FAILURE);
    }

    if(wordlists == NULL){
        printf("[error] - you have to provide a wordlist");
        exit(EXIT_FAILURE);
    }

    spell_check(text_file, word, wordlists, num_wordlist);

    free(wordlists);
    return 0;
}
