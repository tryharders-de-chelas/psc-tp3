#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

Dictionary * dictionary_create();

void dictionary_add(Dictionary *dictionary, const char *filename);

gboolean dictionary_lookup(Dictionary *dictionary, const char *word);

void dictionary_destroy(Dictionary *dictionary);

Dictionary *dictionary_create(){
	Dictionary *dictionary = g_new(Dictionary, 1);
	dictionary -> hash_table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
    /*
    default destroy function can't be defined as we use different types of values(GList and char *)
    when creating instances of the hash table.
    */ 
	return dictionary;	
}
 
void dictionary_add(Dictionary *dictionary, const char *filename){
    FILE *file = fopen(filename, "r");

    char words[LINESIZE];
    const char delims[] = " \n\t\r\v";

    while(fgets(words, sizeof(words), file) != NULL){
        char *word = strtok(words, delims);
        while(word != NULL){
            g_hash_table_add(dictionary->hash_table, g_strdup(word));
            word = strtok(NULL, delims);
        }
    }
    fclose(file);
}

gboolean dictionary_lookup(Dictionary *dictionary, const char *word){
    return g_hash_table_contains(dictionary -> hash_table , word);
}

void dictionary_destroy(Dictionary *dictionary){
    g_hash_table_destroy(dictionary -> hash_table);
    g_free(dictionary);
}


// Glib library -> https://docs.gtk.org/glib/
