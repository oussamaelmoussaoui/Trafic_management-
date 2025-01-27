#include <stdio.h>
typedef struct Vehicle {
    int vehicleId;       // Unique identifier for the vehicle
    int arrivalTime;     // Time the vehicle arrived at the intersection
    int waitingTime;     // Time the vehicle has been waiting at the intersection
} Vehicle;

typedef struct Node {
    Vehicle vehicle;     // Store vehicle data
    struct Node *next;
} Node;


Node* createNode(Vehicle vehicle) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->vehicle = vehicle;  // Store vehicle data
    newNode->next = NULL;
    return newNode;
}


void insertAtBeginning(Node **head, Vehicle vehicle) {
    Node *newNode = createNode(vehicle);
    newNode->next = *head;
    *head = newNode;
}


void insertAtEnd(Node **head, Vehicle vehicle) {
    Node *newNode = createNode(vehicle);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}
void deleteNode(Node **head, int vehicleId) {
    Node *temp = *head;
    Node *prev = NULL;

    if (temp != NULL && temp->vehicle.vehicleId == vehicleId) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->vehicle.vehicleId != vehicleId) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Vehicle with ID %d not found\n", vehicleId);
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void printList(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("Vehicle ID: %d, Arrival Time: %d, Waiting Time: %d\n",
               temp->vehicle.vehicleId,
               temp->vehicle.arrivalTime,
               temp->vehicle.waitingTime);
        temp = temp->next;
    }
}
