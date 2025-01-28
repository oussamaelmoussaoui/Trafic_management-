#include <stdio.h>
#include <stdlib.h>
#include "libraries/queue.h"
 
int main() {
    // Initialiser la file d'attente avec une capacité maximale de 5
    Queue* q = createQueue(5);

    // Ouvrir le fichier de log pour enregistrer les événements
    FILE* logFile = initializeLogFile();

    // Créer des véhicules avec des priorités différentes
    Vehicule* car = createVehicule(1, CAR, 10);
    Vehicule* bus = createVehicule(2, BUS, 15);
    Vehicule* emergency = createVehicule(3, Emergency, 20);
    Vehicule* bike = createVehicule(4, BIKE, 5);

    // Ajouter les véhicules à la file d'attente
    enqueue(q, car, logFile);
    enqueue(q, bus, logFile);
    enqueue(q, emergency, logFile);
    enqueue(q, bike, logFile);

    // Afficher l'état initial de la file d'attente
    printf("\nÉtat initial de la file d'attente:\n");
    display(q);

    // Simuler le cycle des feux de circulation
    printf("\nSimulation du cycle des feux de circulation:\n");
    simulateTrafficLightCycle(q, 3); // Simuler 3 cycles

    // Changer le feu de circulation à VERT pour permettre l'enlèvement des véhicules
    changeTrafficLight(q, GREEN);

    // Retirer les véhicules de la file d'attente
    printf("\nRetrait des véhicules:\n");
    while (!isEmpty(q)) {
        Vehicule* v = dequeue(q, logFile);
        if (v != NULL) {
            free(v); // Libérer la mémoire du véhicule retiré
        }
    }

    // Afficher l'état final de la file d'attente
    printf("\nÉtat final de la file d'attente:\n");
    display(q);

    // Fermer le fichier de log
    fclose(logFile);

    // Libérer la file d'attente
    free(q);

    printf("\nSimulation du trafic terminée. Vérifiez 'traffic_log.txt' pour le log.\n");
    return 0;
}
