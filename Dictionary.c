#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#define LINESIZE 256
#define TRUE 1
#define FALSE 0


// Structure of dictionary 
typedef struct Dictionary { … } Dictionary

// Function to create a new dictionary using malloc *verify Glib library structures to create a new dictionary and use the correct functions*
Dictionary *dictionary_create()

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
            if(dictionary_lookup(dictionary, word) == 0){
                g_hash_table_insert(dictionary -> hash_table , word, NULL);
            }
            word = strtok(NULL, " \n\t\r");
        }
    }

    fclose(file);
    return;
}
// Function to lookup a word in the dictionary, if the word is in the dictionary return 1, else return 0

int dictionary_lookup(Dictionary *dictionary, const char *word){
    return g_hash_table_lookup(dictionary -> hash_table , word);
}

// Function to destroy the dictionary -> free all the memory of the dictionary also using malloc
void dictionary_destroy(Dictionary *dictionary){
    g_hash_table_remove_all(dictionary -> hash_table);
    free(dictionary);
    return;
}

// Glib library -> https://docs.gtk.org/glib/