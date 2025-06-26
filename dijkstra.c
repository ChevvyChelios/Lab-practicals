#include <stdio.h>

#define V 5 // Number of vertices in the graph
#define INF 99999 // A large value representing infinity

int minDistance(int dist[], int visited[])
{
    int min = INF, min_index;
    int v;
    for (v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int graph[V][V], int src)
{
    int dist[V];    
    int visited[V]; 
    int i, count, v;
    for (i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    
    dist[src] = 0;

    for (count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = 1;
        
        for (v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("Vertex \t Distance from Source\n");
    for (i = 0; i < V; i++) {
        printf("%d \t %d\n", i, dist[i]);
    }
}

int main()
{
    int graph[V][V];
    int i, j;
    printf("Enter the adjacency matrix for the graph (use 0 for no connection):\n");
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    
    int src;
    printf("Enter the source vertex: ");
    scanf("%d", &src);

    dijkstra(graph, src);

    return 0;
}