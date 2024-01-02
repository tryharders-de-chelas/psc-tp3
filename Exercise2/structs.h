#include <glib.h>

#define LINESIZE 5012

typedef struct Dictionary {
    GHashTable *hash_table;
} Dictionary;


typedef struct Position {
    int row;
    int column;
} Position;

typedef struct Node {
    Position * position;
    char * word;
} Node;

typedef struct {
    GTree *elements;
} MinHeap;
