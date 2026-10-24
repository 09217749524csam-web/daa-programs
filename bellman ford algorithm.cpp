
#include <stdio.h>
#include <limits.h>

#define MAX 100

struct Edge {
    int src, dest, weight;
};

int main() {
    int V, E, source;
    struct Edge edges[MAX];
    int dist[MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("Enter source, destination and weight:\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d",
              &edges[i].src,
              &edges[i].dest,
              &edges[i].weight);
    }

    printf("Enter source vertex: ");
    scanf("%d", &source);

    // Initialize distances
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;

    dist[source] = 0;

    printf("\nIteration 0: ");
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX)
            printf("INF ");
        else
            printf("%d ", dist[i]);
    }
    printf("\n");

    // Relax edges V-1 times
    for (int i = 1; i < V; i++) {
        int updated = 0;

        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            if (dist[u] != INT_MAX &&
                dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                updated = 1;
            }
        }

        printf("Iteration %d: ", i);
        for (int k = 0; k < V; k++) {
            if (dist[k] == INT_MAX)
                printf("INF ");
            else
                printf("%d ", dist[k]);
        }
        printf("\n");

        if (!updated)
            break;
    }

    // Detect negative-weight cycle
    for (int i = 0; i < E; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int w = edges[i].weight;

        if (dist[u] != INT_MAX &&
            dist[u] + w < dist[v]) {
            printf("\nNegative weight cycle detected!\n");
            return 0;
        }
    }

    printf("\nFinal shortest distances:\n");
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX)
            printf("Vertex %d: INF (Unreachable)\n", i);
        else
            printf("Vertex %d: %d\n", i, dist[i]);
    }

    printf("\nTime Complexity: O(V * E)\n");
    printf("Space Complexity: O(V + E)\n");

    return 0;
}

