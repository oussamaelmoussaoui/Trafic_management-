#include <stdio.h>
#include <stdlib.h>

typedef enum{
    CAR,
    BUS,
    BIKE,
    Emergency
}VehiculeType;

typedef struct Vehicule {
    int id;
    VehiculeType type; 
    int arrivalTime;
    struct Vehicule* next;
} Vehicule;


Vehicule *createVehicule(int id,VehiculeType type ,int arrivalTime){
    Vehicule* v = (Vehicule*)malloc(sizeof(Vehicule));
    v->id = id;
    v->type = type;
    v->arrivalTime = arrivalTime;
    v->next = NULL;
    return v;
}

typedef struct Queue{
    Vehicule* first;
    Vehicule* last;
    int size;
    int Maxcapacity;
}Queue;

Queue* createQueue(int max) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->first = NULL;
    q->last = NULL;
    q->size = 0;
    q->Maxcapacity = max;  // 10 vehicules max
    return q;
}

int isFull(Queue* q) {
    return q->size == q->Maxcapacity;
}

int isEmpty(Queue* q) {
    return q->size == 0;
}
void addToTop(Queue* q, Vehicule* v) {
    // Check if the queue is full
    if (isFull(q)) {
        // Queue is full, remove the last vehicle to make space for the emergency vehicle
        printf("Queue is full. Removing the last vehicle to add emergency vehicle.\n");

        // Remove the last vehicle from the queue
        Vehicule* temp = q->last;
        
        // If the queue has more than one vehicle, we need to traverse to the second last one
        if (q->size > 1) {
            Vehicule* secondLast = q->first;
            while (secondLast->next != q->last) {
                secondLast = secondLast->next;
            }
            secondLast->next = NULL;  // Remove the last vehicle
            q->last = secondLast;     // Update last pointer to the second last vehicle
        } else {
            // If only one vehicle is in the queue, reset both first and last to NULL
            q->first = q->last = NULL;
        }

        free(temp);  // Free the memory of the removed vehicle
        q->size--;   // Decrease the size of the queue after removal
    }
    v->next = q->first;  // Point to the current first vehicle
    q->first = v;         // The new vehicle becomes the first
    if (q->size == 0) {   // If the queue was empty, also set last to the new vehicle
        q->last = v;
    }
    q->size++;  
}


void enqueue(Queue* q, Vehicule* v) {
    if (v->type == 3) { //3 for emergency 
        // If it's an emergency
        addToTop(q, v);
        return;
    }

    // pas d urgence et queue full
    if (isFull(q)) {
        printf("Queue is full. Cannot enqueue non-emergency vehicle.\n");
        return;
    }

    // Normal enqueue 
    if (isEmpty(q)) {
        q->first = v;
    } else {
        q->last->next = v;
    }
    q->last = v;
    q->size++;
}


Vehicule* dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return NULL;
    }
    Vehicule* v = q->first;
    q->first = q->first->next;
    q->size--;
    return v;
}

void displayQueue(Queue* q) {
    Vehicule* v = q->first;
    while (v != NULL) {
        printf("Vehicule ID: %d, Type: %d, Arrival Time: %d\n", v->id, v->type, v->arrivalTime);
        v = v->next;
    }
}



