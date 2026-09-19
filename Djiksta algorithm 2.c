#include <stdio.h>
#include <limits.h>

int main() {
    int n, e;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    int graph[n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    printf("Enter edges (source destination weight):\n");

    for (int i = 0; i < e; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;
    }

    int source;
    printf("Enter source vertex: ");
    scanf("%d", &source);

    int dist[n], visited[n];

    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[source] = 0;

    for (int count = 0; count < n - 1; count++) {
        int min = INT_MAX;
        int u = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] != 0 &&
                dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("\nShortest distances from vertex %d:\n", source);

    for (int i = 0; i < n; i++) {
        if (dist[i] == INT_MAX)
            printf("%d -> INF\n", i);
        else
            printf("%d -> %d\n", i, dist[i]);
    }

    printf("\nTime Complexity: O(V^2)\n");

    return 0;
}
