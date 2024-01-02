#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include "structs.h"

Dictionary * dictionary_create();

void dictionary_add(Dictionary * dictionary, char * word);

void dictionary_add_word(Dictionary * dictionary, const char *word, Position *position);

GList * dictionary_get(Dictionary *dictionary, char *word);

gboolean dictionary_lookup(Dictionary * dictionary, const char * word);

void dictionary_destroy(Dictionary * dictionary);

MinHeap * createMinHeap();

void min_heap_insert(MinHeap *minHeap, Position *key, char * value);

Node * extractMin(MinHeap *minHeap);

gboolean min_heap_is_empty(MinHeap *minHeap);

void min_heap_destroy(MinHeap *minHeap);

void min_heap_node_destroy(Node * node);

void check_if_allocated(gpointer * ptr){
    if(ptr == NULL){
        printf("[error] - memory couldn't be allocated\n");
        exit(EXIT_FAILURE);
    }
}

void check_if_file_opened(FILE * file){
    if(file == NULL){
        printf("[error] - couldn't open the file\n");
        exit(EXIT_FAILURE);
    }
}

void show_positions (gpointer data,gpointer user_data){
    printf("(%d; %d); ", ((Position *)data)->row, ((Position *)data)->column);
    g_free(data);
}

void show_results(Dictionary * missing_words_dict, MinHeap * min_heap){
    printf("-----\nResults - start\n(row; column)\n");
    while(min_heap_is_empty(min_heap) == FALSE){
        Node * node = extractMin(min_heap);
        char * word = node->word;
        printf("-----\n");
        GList * positions = dictionary_get(missing_words_dict, word);
        printf("Number of appearances - %d\n", g_list_length(positions));
        printf("%s - ", word);
        g_list_foreach(positions, show_positions, NULL);
        g_list_free(positions);
        printf("\n-----\n");
        min_heap_node_destroy(node);
    }
    printf("Results - end\n-----\n\n");
}

void process_word(Dictionary * missing_words_dict, MinHeap * min_heap, char * word, int row, int column){
    Position * pos = g_new(Position, 1);
    pos->row = row;
    pos->column = column;

    if(dictionary_lookup(missing_words_dict, word) == FALSE)
        min_heap_insert(min_heap, pos, word);

    dictionary_add_word(missing_words_dict, word, pos);
}


void process_text(FILE * file, Dictionary * dict, Dictionary * missing_words_dict, MinHeap * min_heap){
    char words[LINESIZE];
    const char delims[] = " \n\t\r\v";
    
    int row = 0;
    while(fgets(words, sizeof(words), file) != NULL){
        int column = 0;
        char * word = strtok(words, delims);
        while(word != NULL){
            if(dictionary_lookup(dict, word) == FALSE)
                process_word(missing_words_dict, min_heap, word, row, column);

            column++;
            word = strtok(NULL, delims);
        }
        row++;
    }
}

void check_text(Dictionary * dict,const char * text_file){
    FILE * file = fopen(text_file, "r");
    check_if_file_opened(file);
    Dictionary * missing_words_dict = dictionary_create();
    MinHeap * minHeap = createMinHeap();
    process_text(file, dict, missing_words_dict, minHeap);
    fclose(file);
    show_results(missing_words_dict, minHeap);
    min_heap_destroy(minHeap);
    dictionary_destroy(missing_words_dict);
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
    g_free(wordlists);
    
    if(word == NULL){
        check_text(dict, text_file);
    } else {
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

    if(errflg)
        exit(EXIT_FAILURE);

    if((text_file != NULL && word != NULL) || (text_file == NULL && word == NULL)){
        printf("[error] - you have to provide one of the options: -w or -t\n");
        exit(EXIT_FAILURE);
    }

    if(wordlists == NULL){
        printf("[error] - you have to provide a wordlist\n");
        exit(EXIT_FAILURE);
    }

    spell_check(text_file, word, wordlists, num_wordlist);

    return 0;
}
