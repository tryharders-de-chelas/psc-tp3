#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

gint compare_positions(gconstpointer a, gconstpointer b){
    const Position * pos1 = (const Position *)a;
    const Position * pos2 = (const Position *)b;

    if (pos1->row != pos2->row) {
        return pos1->row - pos2->row;
    }
    return pos1->column - pos2->column;
}

MinHeap* createMinHeap() {
    MinHeap *minHeap = g_new(MinHeap, 1);
    minHeap->elements = g_tree_new(compare_positions);
    return minHeap;
}

// Function to insert a new element into the min heap
void insert(MinHeap *minHeap, Position * key, char * value) {
    Node * node = g_new(Node, 1);
    node->key = key;
    node ->value = g_strdup(value);
    //char * value_copy = g_strdup(value);
    //printf("key-> row:%d, col: %d\n", key->row, key->column);
    //printf("value: %s\n\n", node->value);
    g_tree_insert(minHeap->elements, node->key, node);
}

gpointer heap_lookup(MinHeap * minHeap, const char * key){
    return g_tree_lookup(minHeap->elements, key);
}

// Function to extract the minimum element from the min heap
gpointer extractMin(MinHeap *minHeap) {
    if (!g_tree_nnodes(minHeap->elements)) {
        g_assert_not_reached();  // Heap is empty
        return NULL;
    }

    GTreeNode * root = g_tree_node_first(minHeap->elements);
    char * key = g_tree_node_key(root);  // Get the key of the root node
    gpointer word = g_tree_lookup(minHeap->elements, key);  // Get the value associated with the key
    g_tree_remove(minHeap->elements, key);  // Remove the node using the key
    //g_free(key);
    return word;
}

// Function to check if the min heap is empty
gboolean isEmpty(MinHeap *minHeap) {
    return g_tree_nnodes(minHeap->elements) == 0;
}

// Function to free the memory allocated for the min heap
void minHeap_destroy(MinHeap *minHeap) {
    g_tree_foreach(minHeap->elements, (GTraverseFunc)g_free, NULL);
    g_tree_destroy(minHeap->elements);
    g_free(minHeap);
}
