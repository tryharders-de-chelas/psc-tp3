#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

gint compare_strings(gconstpointer a, gconstpointer b, gpointer user_data) {
    return g_strcmp0(a, b);
}

MinHeap* createMinHeap() {
    MinHeap *minHeap = g_new(MinHeap, 1);
    minHeap->elements = g_tree_new(compare_strings);
    return minHeap;
}

// Function to insert a new element into the min heap
void insert(MinHeap *minHeap, const char *key, const char * value) {
    g_tree_insert(minHeap->elements, g_strdup(key), g_strdup(value));
}

int heap_lookup(MinHeap * minHeap, const char * word){
    return g_tree_lookup(minHeap->elements, word);
}

// Function to extract the minimum element from the min heap
const char* extractMin(MinHeap *minHeap) {
    if (!g_tree_nnodes(minHeap->elements)) {
        g_assert_not_reached();  // Heap is empty
        return NULL;
    }

    GTreeIter iter;
    g_tree_get_root(minHeap->elements, &iter);
    gpointer minValue = g_tree_key(&iter);

    g_tree_remove(minHeap->elements, minValue);

    return minValue;
}

// Function to check if the min heap is empty
gboolean isEmpty(MinHeap *minHeap) {
    return g_tree_nnodes(minHeap->elements) == 0;
}

// Function to free the memory allocated for the min heap
void freeMinHeap(MinHeap *minHeap) {
    g_tree_destroy(minHeap->elements);
    g_free(minHeap);
}
