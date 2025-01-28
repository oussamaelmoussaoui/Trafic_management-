#include <stdio.h>
#include <stdlib.h>

// Définir le type de véhicule
typedef enum{
    CAR,        // Voiture
    BUS,        // Bus
    BIKE,       // Vélo
    Emergency   // Urgence
} VehiculeType;

// Définir l'état des feux de circulation
typedef enum {
    RED,        // Rouge
    YELLOW,     // Jaune
    GREEN       // Vert
} TrafficLightState;

// Structure représentant un véhicule
typedef struct Vehicule {
    int id;               // ID du véhicule
    VehiculeType type;    // Type de véhicule
    int arrivalTime;      // Temps d'arrivée
    struct Vehicule* next; // Prochain véhicule
} Vehicule;

// Fonction pour créer un véhicule
Vehicule *createVehicule(int id, VehiculeType type, int arrivalTime) {
    Vehicule* v = (Vehicule*)malloc(sizeof(Vehicule));
    v->id = id;
    v->type = type;
    v->arrivalTime = arrivalTime;
    v->next = NULL;
    return v;
}

// Structure représentant la file d'attente des véhicules
typedef struct Queue {
    Vehicule* first;       // Premier véhicule dans la file d'attente
    Vehicule* last;        // Dernier véhicule dans la file d'attente
    int size;              // Taille de la file d'attente
    int Maxcapacity;       // Capacité maximale de la file d'attente
    TrafficLightState lightState; // État du feu de circulation
} Queue;

// Fonction pour créer une file d'attente
Queue* createQueue(int max) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->first = NULL;
    q->last = NULL;
    q->size = 0;
    q->Maxcapacity = max;
    q->lightState = RED; // Initialiser le feu de circulation à ROUGE
    return q;
}

// Fonction pour vérifier si la file d'attente est pleine
int isFull(Queue* q) {
    return q->size == q->Maxcapacity;
}

// Fonction pour vérifier si la file d'attente est vide
int isEmpty(Queue* q) {
    return q->size == 0;
}

// Fonction pour ajouter un véhicule au début de la file d'attente
void addToTop(Queue* q, Vehicule* v) {
    // Vérifier si la file d'attente est pleine
    if (isFull(q)) {
        // La file d'attente est pleine, supprimer le dernier véhicule pour faire de la place pour un véhicule d'urgence
        printf("La file d'attente est pleine. Suppression du dernier véhicule pour ajouter un véhicule d'urgence.\n");

        // Supprimer le dernier véhicule de la file d'attente
        Vehicule* temp = q->last;

        // Si la file d'attente contient plus d'un véhicule, nous devons parcourir jusqu'à l'avant-dernier
        if (q->size > 1) {
            Vehicule* secondLast = q->first;
            while (secondLast->next != q->last) {
                secondLast = secondLast->next;
            }
            secondLast->next = NULL;  // Supprimer le dernier véhicule
            q->last = secondLast;     // Mettre à jour le pointeur last pour le deuxième dernier véhicule
        } else {
            // Si la file d'attente contient un seul véhicule, réinitialiser first et last à NULL
            q->first = q->last = NULL;
        }

        free(temp);  // Libérer la mémoire du véhicule supprimé
        q->size--;   // Réduire la taille de la file d'attente après la suppression
    }

    v->next = q->first;  // Pointer vers le premier véhicule actuel
    q->first = v;         // Le nouveau véhicule devient le premier
    if (q->size == 0) {   // Si la file était vide, définir last également sur le nouveau véhicule
        q->last = v;
    }
    q->size++;
}

// Fonction pour simuler le cycle des feux de circulation
void simulateTrafficLightCycle(Queue* q, int duration) {
    for (int i = 0; i < duration; i++) {
        switch (q->lightState) {
            case RED:
                changeTrafficLight(q, YELLOW);
                break;
            case YELLOW:
                changeTrafficLight(q, GREEN);
                break;
            case GREEN:
                changeTrafficLight(q, YELLOW);
                break;
        }
        sleep(2); // Simuler un délai de 2 secondes entre les changements d'état
    }
}

// Fonction pour changer l'état du feu de circulation
void changeTrafficLight(Queue* q, TrafficLightState newState) {
    q->lightState = newState;
    switch (newState) {
        case RED:
            printf("Le feu de circulation est devenu ROUGE.\n");
            break;
        case YELLOW:
            printf("Le feu de circulation est devenu JAUNE.\n");
            break;
        case GREEN:
            printf("Le feu de circulation est devenu VERT.\n");
            break;
    }
}

// Fonction pour obtenir la priorité d'un véhicule
int getPriority(VehiculeType type) {
    switch (type) {
        case Emergency: return 3; // Priorité la plus élevée
        case BUS: return 2;       // Priorité moyenne
        case CAR: return 1;       // Priorité basse
        case BIKE: return 0;      // Priorité la plus basse
        default: return 0;        // Priorité par défaut pour les types inconnus
    }
}

// Fonction pour ajouter un véhicule à la file d'attente
void enqueue(Queue* q, Vehicule* v, FILE* logFile) {
    if (v->type == Emergency) { 
        fprintf(logFile, "Véhicule d'urgence (ID: %d) arrivé et priorisé.\n", v->id);
        addToTop(q, v);
        return;
    }

    if (isFull(q)) {
        fprintf(logFile, "La file d'attente est pleine. Véhicule ID: %d n'a pas pu être ajouté.\n", v->id);
        return;
    }

    Vehicule* current = q->first;
    Vehicule* previous = NULL;

    while (current != NULL && getPriority(current->type) >= getPriority(v->type)) {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) {
        v->next = q->first;
        q->first = v;
        if (q->size == 0) {
            q->last = v;
        }
    } else {
        v->next = current;
        previous->next = v;
        if (current == NULL) {
            q->last = v;
        }
    }

    q->size++;
    fprintf(logFile, "Véhicule ID: %d ajouté à la file d'attente (Type: %d).\n", v->id, v->type);
}

// Fonction pour retirer un véhicule de la file d'attente
Vehicule* dequeue(Queue* q, FILE* logFile) {
    if (isEmpty(q)) {
        fprintf(logFile, "La file d'attente est vide. L'opération de retrait a échoué.\n");
        printf("La file d'attente est vide. Impossible de retirer un véhicule.\n");
        return NULL;
    }
    if (q->lightState != GREEN) {
        fprintf(logFile, "Le feu de circulation n'est pas VERT. Les véhicules ne peuvent pas avancer.\n");
        printf("Le feu de circulation n'est pas VERT. Les véhicules ne peuvent pas avancer.\n");
        return NULL;
    }

    Vehicule* v = q->first;
    q->first = q->first->next;
    q->size--;

    fprintf(logFile, "Véhicule ID: %d retiré de la file d'attente (Type: %d).\n", v->id, v->type);
    printf("Véhicule %d retiré.\n", v->id);
    return v;
}

// Fonction pour initialiser le fichier de log
FILE* initializeLogFile() {
    FILE* logFile = fopen("traffic_log.txt", "w");
    if (logFile == NULL) {
        printf("Erreur : Impossible de créer le fichier de log.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(logFile, "Log de la simulation du trafic\n");
    fprintf(logFile, "============================\n\n");
    return logFile;
}

// Fonction pour afficher l'état actuel de la file d'attente
void display(Queue* q) {
    printf("\nFeu de circulation: ");
    switch (q->lightState) {
        case RED:
            printf("[ROUGE]\n");
            break;
        case YELLOW:
            printf("[JAUNE]\n");
            break;
        case GREEN:
            printf("[VERT]\n");
            break;
    }

    Vehicule* current = q->first;
    printf("File d'attente: ");
    while (current != NULL) {
        switch (current->type) {
            case CAR: printf("[C] -> "); break;
            case BUS: printf("[B] -> "); break;
            case BIKE: printf("[V] -> "); break;
            case Emergency: printf("[U] -> "); break;
        }
        current = current->next;
    }
    printf("NULL\n");
}
