#include <stdio.h>
 
int main() {
    int V, E;
 
    printf("Enter number of vertices: ");
    scanf("%d", &V);
 
    printf("Enter number of edges: ");
    scanf("%d", &E);
 
    int u[100], v[100], w[100];
 
    printf("Enter source, destination and weight of each edge:\n");
 
    for (int i = 0; i < E; i++) {
        printf("Edge %d:\n", i + 1);
 
        printf("Source: ");
        scanf("%d", &u[i]);
 
        printf("Destination: ");
        scanf("%d", &v[i]);
 
        printf("Weight: ");
        scanf("%d", &w[i]);
    }
 
    int src;
    printf("Enter source vertex: ");
    scanf("%d", &src);
 
    int dist[100];
 
    for (int i = 0; i < V; i++) {
        dist[i] = 1000000;
    }
 
    dist[src] = 0;
 
    // Relax all edges V-1 times
    for (int i = 1; i < V; i++) {
        for (int j = 0; j < E; j++) {
            if (dist[u[j]] != 1000000 &&
                dist[u[j]] + w[j] < dist[v[j]]) {
                dist[v[j]] = dist[u[j]] + w[j];
            }
        }
    }
 
    // Check for negative weight cycle
    for (int j = 0; j < E; j++) {
        if (dist[u[j]] != 1000000 &&
            dist[u[j]] + w[j] < dist[v[j]]) {
            printf("Negative weight cycle detected!");
            return 0;
        }
    }
 
    printf("\nShortest distances from source %d:\n", src);
 
    for (int i = 0; i < V; i++) {
        printf("Vertex %d : ", i);
 
        if (dist[i] == 1000000) {
            printf("INF");
        } else {
            printf("%d", dist[i]);
        }
 
        printf("\n");
    }
 
    return 0;
}
