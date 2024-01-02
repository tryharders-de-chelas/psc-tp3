#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

#define LINESIZE 256

Dictionary * dictionary_create();
void dictionary_add(Dictionary *dictionary, const char *filename);
int dictionary_lookup(Dictionary *dictionary, const char *word);
void dictionary_destroy(Dictionary *dictionary);

// Function to create a new dictionary using malloc *verify Glib library structures to create a new dictionary and use the correct functions*
Dictionary *dictionary_create(){
	Dictionary *dictionary = g_malloc((sizeof(Dictionary)));
	dictionary -> hash_table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
	return dictionary;	
}

/*
 / Function to add a word to the dictionary
 / Iterate through filename and use dictionary_lookup to check if the word is already in the dictionary
 / If the word is not in the dictionary, add the word to the dictionary
*/ 
void dictionary_add(Dictionary *dictionary, const char *filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        printf("Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    char words[LINESIZE];
    const char delims[] = " \n\t\r\v";

    while(fgets(words, sizeof(words), file)){
        char *word = strtok(words, delims);
        while(word != NULL){
            char * word_copy = g_strdup(word);
            g_hash_table_insert(dictionary->hash_table, word_copy, NULL);
            //g_free(word_copy);
            word_copy = NULL;
            word = strtok(NULL, " \n\t\r");
        }
    }

    fclose(file);
}
// Function to lookup a word in the dictionary, if the word is in the dictionary return 1, else return 0

int dictionary_lookup(Dictionary *dictionary, const char *word){
    return g_hash_table_contains(dictionary -> hash_table , word);
}


// Function to destroy the dictionary -> free all the memory of the dictionary also using malloc
void dictionary_destroy(Dictionary *dictionary){
    g_hash_table_destroy(dictionary -> hash_table);
    g_free(dictionary);
}


GList *dictionary_get(Dictionary *dictionary, const char * key) {
    return g_hash_table_lookup(dictionary -> hash_table, key);
}

void dictionary_add_word(Dictionary *dictionary, const char * key, Position *position) {
    GList * value = dictionary_get(dictionary, key);
    value = g_list_append(value, position);
    char * key_copy = g_strdup(key);
    g_hash_table_insert(dictionary -> hash_table, key_copy, value);
}

// Glib library -> https://docs.gtk.org/glib/
