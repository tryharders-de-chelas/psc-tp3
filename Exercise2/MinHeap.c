#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void check_if_allocated(void * ptr);

gint compare_positions(gconstpointer a, gconstpointer b){
    const Position * pos1 = (const Position *)a;
    const Position * pos2 = (const Position *)b;
    if (pos1->row == pos2->row) 
        return pos1->column - pos2->column;
    return pos1->row - pos2->row;
}

MinHeap * createMinHeap() {
    MinHeap *min_heap = g_new(MinHeap, 1);
    check_if_allocated(min_heap);
    min_heap->elements = g_tree_new(compare_positions);
    return min_heap;
}

void min_heap_insert(MinHeap *minHeap, Position * key, char * value) {
    Node * node = g_new(Node, 1);
    check_if_allocated(node);
    node->position = key;
    node->word = g_strdup(value);
    g_tree_insert(minHeap->elements, node->position, node);
}

gpointer heap_lookup(MinHeap * minHeap, const char * key){
    return g_tree_lookup(minHeap->elements, key);
}

gboolean min_heap_is_empty(MinHeap * min_heap) {
    return g_tree_nnodes(min_heap->elements) == 0;
}

Node * extractMin(MinHeap * min_heap) {
    GTreeNode * root = g_tree_node_first(min_heap->elements);
    char * key = g_tree_node_key(root);
    Node * value = g_tree_node_value(root);
    g_tree_remove(min_heap->elements, key);
    return value;
}


void min_heap_destroy(MinHeap * min_heap) {
    g_tree_foreach(min_heap->elements, (GTraverseFunc)g_free, NULL);
    g_tree_destroy(min_heap->elements);
    g_free(min_heap);
}

void min_heap_node_destroy(Node * node){
    /*
     * we don't free node->key as it will a pointer to a Position in the missing_words_dict
     * and will be freed there.
     */
    g_free(node->word);
    g_free(node);
}
