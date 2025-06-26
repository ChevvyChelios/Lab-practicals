#include <stdio.h>
#include <stdbool.h>

#define MAX_V 100
#define INFINITY 9999999

int distance[MAX_V];
int previous[MAX_V];
int graph[MAX_V][MAX_V]; // adjacency matrix representation

bool bellmanFord(int G[MAX_V][MAX_V], int V, int S) {
    int i, j,k;

    // Initialization
    for (i = 1; i <= V; i++) {
        distance[i] = INFINITY;
        previous[i] = -1; // using -1 to indicate NULL or undefined
    }
    distance[S] = 0;

    // Relaxation
    for (i = 1; i <= V - 1; i++) {
        for (j = 1; j <= V; j++) {
            for (k = 1; k <= V; k++) {
                if (G[j][k] != INFINITY) {
                    int tempDistance = distance[j] + G[j][k];
                    if (tempDistance < distance[k]) {
                        distance[k] = tempDistance;
                        previous[k] = j;
                    }
                }
            }
        }
    }

    // Check for negative cycles
    for (j = 1; j <= V; j++) {
        for (k = 1; k <= V; k++) {
            if (G[j][k] != INFINITY && distance[j] + G[j][k] < distance[k]) {
                printf("Error: Negative Cycle Exists\n");
                return false;
            }
        }
    }
 
    return true;
}

int main() {
    int V, E, i, j, u, v, w;
    
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    // Initializing graph with INFINITY
    for(i = 1; i <= V; i++) {
        for(j = 1; j <= V; j++) {
            if(i == j) graph[i][j] = 0;
            else graph[i][j] = INFINITY;
        }
    }

    printf("Enter the number of edges: ");
    scanf("%d", &E);

    printf("Enter the edges and their weights (u v w): \n");
    for(i = 1; i <= E; i++) {
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
    }

    int source;
    printf("Enter the source vertex: ");
    scanf("%d", &source);
    
    if (bellmanFord(graph, V, source)) {
        printf("Distances from source: \n");
        for(i = 1; i <= V; i++) {
            printf("Distance to %d = %d\n", i, distance[i]);
        }
    }

    return 0;
}