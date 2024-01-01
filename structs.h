#include <glib.h>

// Structure of dictionary
typedef struct Dictionary {
    GHashTable *hash_table;
} Dictionary;


typedef struct Position {
    int row;
    int column;
} Position;

typedef struct Node {
    Position * key;
    char * value; // GList of Position structures
} Node;

typedef struct {
    GTree *elements;
} MinHeap;
