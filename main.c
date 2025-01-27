#include <stdio.h>
#include <stdlib.h>
#include "libraries/queue.h"
 
int main() {
    Queue* q = createQueue(2);
    Vehicule* vehicule = createVehicule(1, CAR, 10);
    Vehicule* vehicule1 = createVehicule(2, BUS, 15);
    Vehicule* vehicule2 = createVehicule(3, Emergency , 20);
    vehicule2->next = NULL;
    vehicule->next = vehicule1;
    vehicule1->next = vehicule2;
    enqueue(q, vehicule);
    enqueue(q, vehicule1);
    enqueue(q, vehicule2);
    displayQueue(q);
    if (q->Maxcapacity <= q->size){
        printf("Traffic Jam in this road !.\n");
    }
    getchar();

 
    return 0;
}
