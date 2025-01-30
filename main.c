#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main() {
    // Initialiser la file d'attente avec une capacité maximale de 5
    Queue* q = createQueue(8); 

    // Ouvrir le fichier de log pour enregistrer les événements
    FILE* logFile = initializeLogFile();

    // Créer des véhicules avec des priorités différentes
    Vehicule* car = createVehicule(1, CAR, 10);
    Vehicule* bus = createVehicule(2, BUS, 15);
    Vehicule* emergency = createVehicule(3, Emergency, 20);
    Vehicule* bike = createVehicule(4, BIKE, 5);
    Vehicule* bike_1 = createVehicule(5, BIKE, 3);
    Vehicule* car_1 = createVehicule(6, CAR, 11);

    // Ajouter les véhicules à la file d'attente
    enqueue(q, car, logFile);
    enqueue(q, bus, logFile);
    enqueue(q, emergency, logFile);
    enqueue(q, bike, logFile);
    enqueue(q, bike_1, logFile);
    enqueue(q, car_1, logFile);

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
    

    // Create a multi-lane system with 4 lanes
    MultiLaneSystem* system = createMultiLaneSystem(4);
    
    // Create vehicles with different directions
    Vehicule* car1 = createVehicule(1, CAR, 10);
    Vehicule* bus1 = createVehicule(2, BUS, 15);
    Vehicule* emergency1 = createVehicule(3, Emergency, 20);
    Vehicule* bike1 = createVehicule(4, BIKE, 5);
    Vehicule* car2 = createVehicule(5, CAR, 25);
    Vehicule* bus2 = createVehicule(6, BUS, 30);
    
    // Add vehicles to different lanes
    addVehicleToLane(system, car1, 'N', logFile);      // North lane
    addVehicleToLane(system, bus1, 'S', logFile);      // South lane
    addVehicleToLane(system, emergency1, 'E', logFile); // East lane
    addVehicleToLane(system, bike1, 'W', logFile);     // West lane
    addVehicleToLane(system, car2, 'N', logFile);      // North lane
    addVehicleToLane(system, bus2, 'S', logFile);      // South lane
    
    // Logger l'état initial
    fprintf(logFile, "\nÉtat initial du système:\n");
    logMultiLaneState(logFile, system);
    
    // Run simulation
    simulateMultiLaneTraffic(system, 4, logFile); // Run for 4 cycles
    
    // Logger l'état final
    fprintf(logFile, "\nÉtat final du système:\n");
    logMultiLaneState(logFile, system);
    
    // Nettoyage
    for(int i = 0; i < system->laneCount; i++) {
        while(!isEmpty(system->lanes[i]->queue)) {
            Vehicule* v = dequeue(system->lanes[i]->queue, logFile);
            if(v != NULL) free(v);
        }
        free(system->lanes[i]->queue);
        free(system->lanes[i]);
    }
    free(system->lanes);
    free(system);
    
    fprintf(logFile, "\nFin de la session\n\n");
    fclose(logFile);
    
    printf("\nSimulation terminée. Consultez traffic_log.txt pour les détails.\n");
    return 0;
}
