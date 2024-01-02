#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

#define LINESIZE 256

Dictionary * dictionary_create();
void dictionary_add(Dictionary *dictionary, const char *filename);
int dictionary_lookup(Dictionary *dictionary, const char *word);
void dictionary_destroy(Dictionary *dictionary);

// Function to create a new dictionary using malloc *verify Glib library structures to create a new dictionary and use the correct functions*
Dictionary *dictionary_create(){
	Dictionary *dictionary = (Dictionary *)malloc((sizeof(Dictionary)));
	dictionary -> hash_table = g_hash_table_new(g_str_hash, g_str_equal);
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
        return;
    }

    char words[LINESIZE];
    const char delims[] = " \n\t\r\v";
     
     while(fgets(words,sizeof(words),file) != NULL){
        char *word = strtok(words, delims);
        while(word != NULL){
            g_hash_table_insert(dictionary -> hash_table , word, NULL);
            word = strtok(NULL, delims);
        }
    }
    fclose(file);
    return;
}
// Function to lookup a word in the dictionary, if the word is in the dictionary return 1, else return 0

int dictionary_lookup(Dictionary *dictionary, const char *word){
    //printf("%d\n", g_hash_table_size(dictionary -> hash_table));
    if(g_hash_table_contains(dictionary -> hash_table , word) == TRUE){
        return TRUE;
    }
    //printf("FALSEEEEEEEEEEEE\n");
    return FALSE;
}

// Function to destroy the dictionary -> free all the memory of the dictionary also using malloc
void dictionary_destroy(Dictionary *dictionary){
    g_hash_table_remove_all(dictionary -> hash_table);
    free(dictionary);
    return;
}

// Glib library -> https://docs.gtk.org/glib/
