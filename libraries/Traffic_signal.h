#include <stdio.h>
#include <stdlib.h>

#include "queue.h"



typedef struct TrafficSignal {
    int intersectionId;   // Intersection ID
    int greenDuration;    // Duration of green light in seconds
    int redDuration;      // Duration of red light in seconds
    int currentState;     // 1 for green, 0 for red
    int timeElapsed;      // Time elapsed in the current state
    int maxQueueSize;     // Maximum queue size before the intersection is considered jammed
    int capacityThreshold; // Threshold of vehicles that indicates a jam
} TrafficSignal;

// Function to create a traffic signal
TrafficSignal* createSignal(int intersectionId, int greenDuration, int redDuration, int maxQueueSize, int capacityThreshold) {
    TrafficSignal* signal = (TrafficSignal*)malloc(sizeof(TrafficSignal));
    signal->intersectionId = intersectionId;
    signal->greenDuration = greenDuration;
    signal->redDuration = redDuration;
    signal->currentState = 1; // Start with green light
    signal->timeElapsed = 0;
    signal->maxQueueSize = maxQueueSize;
    signal->capacityThreshold = capacityThreshold;
    return signal;
}


void updateSignalState(TrafficSignal* signal, Queue* vehicleQueue) {
    signal->timeElapsed++;
    
    // Check if the intersection is jammed
    int queueSize = queue_size(vehicleQueue);
    if (queueSize >= signal->capacityThreshold) {
        // Adjust the red light duration to allow more vehicles to pass
        signal->redDuration = signal->redDuration > 10 ? signal->redDuration - 10 : signal->redDuration; // Reduce red duration by 10 seconds
    } else {
        // If the jam is cleared, reset to the normal red duration
        signal->redDuration = signal->redDuration + 10; // Restore original red duration
    }

    // Check if green light should turn red
    if (signal->currentState == 1 && signal->timeElapsed >= signal->greenDuration) {
        signal->currentState = 0;  // Switch to red light
        signal->timeElapsed = 0;
    } 
    // Check if red light should turn green
    else if (signal->currentState == 0 && signal->timeElapsed >= signal->redDuration) {
        signal->currentState = 1;  // Switch to green light
        signal->timeElapsed = 0;
    }
}

// Function to get the current state of the signal
const char* getSignalState(TrafficSignal* signal) {
    return signal->currentState == 1 ? "Green" : "Red";
}

// Function to display the current status of the traffic signal
void displaySignal(TrafficSignal* signal, Queue* vehicleQueue) {
    int queueSize = queue_size(vehicleQueue);
    printf("Intersection %d: State = %s, Time Elapsed = %d seconds\n",
           signal->intersectionId,
           getSignalState(signal),
           signal->timeElapsed);
    printf("Green Duration: %d seconds, Red Duration: %d seconds\n", 
           signal->greenDuration, signal->redDuration);
    printf("Queue Size: %d\n", queueSize);
}

// Function to delete the signal (free memory)


const char* getSignalState(TrafficSignal* signal) {
    return signal->currentState == 1 ? "Green" : "Red";
}

void adjustSignalTiming(TrafficSignal* signal, int newGreenDuration, int newRedDuration) {
    signal->greenDuration = newGreenDuration;
    signal->redDuration = newRedDuration;
}

void displaySignal(TrafficSignal* signal) {
    printf("Intersection %d: State = %s, Time Elapsed = %d seconds\n",
           signal->intersectionId,
           getSignalState(signal),
           signal->timeElapsed);
    printf("Green Duration: %d seconds, Red Duration: %d seconds\n",
           signal->greenDuration,
           signal->redDuration);
}

void deleteSignal(TrafficSignal* signal) {
    free(signal);
}
