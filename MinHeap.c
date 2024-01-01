#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

gint compare_positions(gconstpointer a, gconstpointer b, gpointer user_data){
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
void insert(MinHeap *minHeap, const char *key, GList * value) {
    Node * node = g_new(Node, 1);
    node->positions = value;
    g_tree_insert(minHeap->elements, g_strdup(key), node);
}

gpointer heap_lookup(MinHeap * minHeap, const char * key){
    return g_tree_lookup(minHeap->elements, key);
}

// Function to extract the minimum element from the min heap
Node * extractMin(MinHeap *minHeap) {
    if (!g_tree_nnodes(minHeap->elements)) {
        g_assert_not_reached();  // Heap is empty
        return NULL;
    }

    GTreeIter iter;
    g_tree_get_root(minHeap->elements, &iter);
    gpointer minValue = g_tree_key(&iter);

    Node * node = g_tree_remove(minHeap->elements, minValue);

    return node;
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

void freeNode(Node * node){
    g_list_free_full(node->positions, g_free);
    g_free(node);
}

void printPositions(GList *positions) {
    while (positions != NULL) {
        Position *pos = (Position*)positions->data;
        printf("(%d, %d) ", pos->row, pos->column);
        positions = g_list_next(positions);
    }
    printf("\n");
}
