#include <stdio.h>
#include <stdlib.h>
#include "linked_lists.h"

typedef struct Queue{
    Node* first;
    Node* last;
    int size;
    int capacity;
}Queue;

int queue_size(Queue* q) {
    return q->size;
}

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->first = NULL;
    q->last = NULL;
    q->size = 0;
    q->capacity = 100;  // Set a capacity if needed
    return q;
}

void enqueue(Queue* q, Vehicle vehicle) {
    Node* newNode = createNode(vehicle);
    if (q->first == NULL) {
        q->first = newNode;
        q->last = newNode;
    } else {
        q->last->next = newNode;
        q->last = newNode;
    }
    q->size++;
}

Vehicle dequeue(Queue* q) {
    if (q->first == NULL) {
        printf("Queue is empty\n");
        return (Vehicle){-1, -1, -1}; // Return a "null" vehicle if empty
    }
    Node* temp = q->first;
    Vehicle vehicle = temp->vehicle;
    q->first = q->first->next;
    free(temp);
    q->size--;
    return vehicle;
}

int check_first(Queue* q) {
    if (q->first == NULL) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->first->vehicle.vehicleId;
}

int queue_size(Queue* q) {
    return q->size;
}

void displayQueue(Queue* q) {
    Node* temp = q->first;
    while (temp != NULL) {
        printf("Vehicle ID: %d, Arrival Time: %d, Waiting Time: %d\n",
               temp->vehicle.vehicleId,
               temp->vehicle.arrivalTime,
               temp->vehicle.waitingTime);
        temp = temp->next;
    }
}

int isEmpty(Queue* q) {
    return q->size == 0;
}

int isFull(Queue* q) {
    return q->size == q->capacity;
}

void deleteQueue(Queue* q) {
    Node* temp = q->first;
    while (temp != NULL) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    free(q);
}
