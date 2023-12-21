// Structure of dictionary 
typedef struct Dictionary { … } Dictionary

// Function to create a new dictionary using malloc *verify Glib library structures to create a new dictionary and use the correct functions*
Dictionary *dictionary_create()

/*
 / Function to add a word to the dictionary
 / Iterate through filename and use dictionary_lookup to check if the word is already in the dictionary
 / If the word is not in the dictionary, add the word to the dictionary
*/ 
void dictionary_add(Dictionary *dictionary, const char *filename)

// Function to lookup a word in the dictionary, if the word is in the dictionary return 1, else return 0
int dictionary_lookup(Dictionary *dictionary, const char *word)

// Function to destroy the dictionary -> free all the memory of the dictionary also using malloc
void dictionary_destroy(Dictionary *dictionary)

// Glib library -> https://docs.gtk.org/glib/