#include <stdio.h>
#include <stdlib.h>
#include "linked_lists.h"

typedef struct Graph {
    int numVertices;
    int** adjMatrix;
} Graph;

Graph* createGraph(int numVertices) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->adjMatrix = (int**)malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; i++) {
        graph->adjMatrix[i] = (int*)calloc(numVertices, sizeof(int));
    }
    return graph;
}

void addEdge(Graph *graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;  // For undirected graph
}

void printGraph(Graph *graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        printf("Vertex %d: ", i);
        for (int j = 0; j < graph->numVertices; j++) {
            if (graph->adjMatrix[i][j] == 1) {
                printf("%d ", j);
            }
        }
        printf("\n");
    }
}
