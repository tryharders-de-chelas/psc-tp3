#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include "structs.h"

#define LINE_MAX_LEN 2056

Dictionary * dictionary_create();

void dictionary_add(Dictionary * dictionary, char * word);

void dictionary_add_word(Dictionary * dictionary, const char *word, Position *position);

GList *dictionary_get(Dictionary *dictionary, char *word);

int dictionary_lookup(Dictionary * dictionary, const char * word);

void dictionary_destroy(Dictionary * dictionary);

MinHeap* createMinHeap();

void insert(MinHeap *minHeap, Position *key, char * value);

gpointer extractMin(MinHeap *minHeap);

gboolean isEmpty(MinHeap *minHeap);

void minHeap_destroy(MinHeap *minHeap);

void print_list_element (gpointer data,gpointer user_data){
    printf("(%d; %d); ", ((Position *)data)->row, ((Position *)data)->column);
}

void show_results(Dictionary * not_found_dict, MinHeap * minHeap){
    printf("-----\nResults - start\n-----\n");
    while(!isEmpty(minHeap)){
        Node * node = extractMin(minHeap);
        char * word = node->value;
        GList * positions = dictionary_get(not_found_dict, word);
        printf("\n-----\n");
        //printf("size of the heap - %d\n", g_tree_nnodes(minHeap->elements));
        printf("Number of appearances - %d\n", g_list_length(positions));
        printf("%s - ", word);
        g_free(node->key);
        g_free(node->value);
        g_free(node);
        g_list_foreach(positions, print_list_element, NULL);
        printf("\n-----\n\n");
        g_list_foreach(positions, (GFunc)g_free, NULL);
        g_list_free(positions);
    }
    printf("-----\nResults - end\n-----\n");
}

void process_word(Dictionary * not_found_dict, MinHeap * minHeap, char * word, int row, int column){
    Position * pos = g_new(Position, 1);
    pos->row = row;
    pos->column = column;

    if(dictionary_lookup(not_found_dict, word) == FALSE)
        insert(minHeap, pos, word);

    dictionary_add_word(not_found_dict, word, pos);
}


void process_text(FILE * file, Dictionary * dict, Dictionary * not_found_dict, MinHeap * minHeap){
    char words[LINE_MAX_LEN];
    const char delims[] = " \n\t";
    
    int row = 0;
    while(fgets(words, sizeof(words), file) != NULL){
        int column = 0;
        char * word = strtok(words, delims);
        while(word != NULL){
            if(dictionary_lookup(dict, word) == FALSE)
                process_word(not_found_dict, minHeap, word, row, column);

            column++;
            word = strtok(NULL, delims);
        }
        row++;
    }
}

void check_text(Dictionary * dict,const char * text_file){
    FILE * file = fopen(text_file, "r");
    if(file == NULL){
        printf("[error] - couldn't open the file\n");
        exit(EXIT_FAILURE);
    }
    Dictionary * not_found_dict = dictionary_create();
    MinHeap * minHeap = createMinHeap();
    process_text(file, dict, not_found_dict, minHeap);
    fclose(file);
    show_results(not_found_dict, minHeap);
    minHeap_destroy(minHeap);
    dictionary_destroy(not_found_dict);
}

void check_word(Dictionary * dict, char * word){
    if(dictionary_lookup(dict, word) == TRUE){
        printf("Every given word was found in the dictionary");
    } else {
        printf("word: %s position: (0; 0)\n", word);
    }
}

void spell_check(char * text_file, char * word, char ** wordlists, int num_wordlists){
    Dictionary * dict = dictionary_create();
    for(int i = 0; i < num_wordlists; i++){
        dictionary_add(dict, wordlists[i]);
    }
    
    if(word == NULL){
        //printf("\nText file was provided\n");
        check_text(dict, text_file);
    } else {
        //printf("\nSingle word given\n");
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
                //printf("wordlist: %s\n", optarg);
                wordlists[num_wordlist++] = optarg;
                break;
            case 't':
                //printf("text_file: %s\n", optarg);
                text_file = optarg;
                break;
            case 'w':
                //printf("word: %s\n", optarg);
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
        printf("[error] - you have to provide a wordlist\n");
        exit(EXIT_FAILURE);
    }

    spell_check(text_file, word, wordlists, num_wordlist);


    free(wordlists);
    return 0;
}
