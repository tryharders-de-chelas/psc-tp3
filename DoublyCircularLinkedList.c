#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"


Node* createNode(Position * data) {
    Node* newNode = g_new(Node, 1);
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertEnd(Node** head, Position * data) {
    Node* newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
        (*head)->next = *head;
        (*head)->prev = *head;
    } else {
        Node* last = (*head)->prev;
        last->next = newNode;
        newNode->prev = last;
        newNode->next = *head;
        (*head)->prev = newNode;
    }
}

void destroy(Node * node){
    Node * current = node;
    do {
        Node * next = current -> next;
        g_free(current);
        current = next;
    } while (current != NULL);
}

void printList(Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    Node* current = head;
    do {
        printf("%s ", current->data);
        current = current->next;
    } while (current != head);
    printf("\n");
}
