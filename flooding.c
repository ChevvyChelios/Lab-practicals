#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

// Graph structure using adjacency matrix
int graph[MAX_NODES][MAX_NODES];
int visited[MAX_NODES];

// Function to simulate flooding
void flood(int node, int numNodes) {
    if (visited[node]) return;  // Avoid redundant flooding
    visited[node] = 1;
    printf("Flooding packet to node %d\n", node);

    // Send packet to all neighbors
    int i;
    for (i = 0; i < numNodes; i++) {
        if (graph[node][i] == 1) {
            flood(i, numNodes);
        }
    }
}

int main() {
    int numNodes, edges, src, dest, startNode;

    // Initialize visited array
    int i,j;
    for (i = 0; i < MAX_NODES; i++) visited[i] = 0;

    printf("Enter number of nodes: ");
    scanf("%d", &numNodes);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    // Initialize adjacency matrix
    for (i = 0; i < numNodes; i++)
        for (j = 0; j < numNodes; j++)
            graph[i][j] = 0;

    printf("Enter edges (src dest):\n");
    for (i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        graph[src][dest] = graph[dest][src] = 1;  // Undirected graph
    }

    printf("Enter the starting node: ");
    scanf("%d", &startNode);

    printf("Flooding begins from node %d\n", startNode);
    flood(startNode, numNodes);

    return 0;
}