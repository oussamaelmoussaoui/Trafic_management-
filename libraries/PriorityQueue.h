
#include "linked_lists.h"  // Include the updated linked_lists.h

typedef struct PriorityQueue {
    Node* first;
    Node* last;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (!pq) {
        fprintf(stderr, "Memory allocation failed for priority queue\n");
        exit(EXIT_FAILURE);
    }
    pq->first = NULL;
    pq->last = NULL;
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void insertWithPriority(PriorityQueue* pq, Vehicule* data) {
    if (pq->size == pq->capacity) {
        printf("Priority queue is full. Cannot enqueue vehicule %d\n", data->id);
        return;
    }
    Node* newNode = createNode(data);
    if (pq->first == NULL || data->priority < pq->first->data->priority) {
        newNode->next = pq->first;
        pq->first = newNode;
    } else {
        Node* temp = pq->first;
        while (temp->next != NULL && temp->next->data->priority <= data->priority) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
    pq->size++;
}

Vehicule* extractMax(PriorityQueue* pq) {
    if (pq->first == NULL) {
        printf("Priority queue is empty\n");
        return NULL;
    }
    Node* temp = pq->first;
    Vehicule* data = temp->data;
    pq->first = pq->first->next;
    free(temp);
    pq->size--;
    return data;
}

int isEmpty(PriorityQueue* pq) {
    return pq->first == NULL;
}

void displayPriorityQueue(PriorityQueue* pq) {
    Node* temp = pq->first;
    while (temp != NULL) {
        printVehicule(temp->data);  // Print vehicule details
        temp = temp->next;
    }
    printf("\n");
}
