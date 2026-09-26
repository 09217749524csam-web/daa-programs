#include <stdio.h>
#include <limits.h>

#define MAX 100

void primMST(int graph[MAX][MAX], int n)
{
    int parent[MAX];       // Stores MST
    int key[MAX];          // Minimum edge weight
    int mstSet[MAX];       // Included in MST or not
    int totalCost = 0;

    // Initialize
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    // Start from vertex 0
    key[0] = 0;
    parent[0] = -1;

    // MST contains n-1 edges
    for (int count = 0; count < n - 1; count++) {

        // Find vertex with minimum key value
        int min = INT_MAX;
        int u = -1;

        for (int v = 0; v < n; v++) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }

        // Include vertex u in MST
        mstSet[u] = 1;

        // Update key values of adjacent vertices
        for (int v = 0; v < n; v++) {
            if (graph[u][v] != 0 &&
                !mstSet[v] &&
                graph[u][v] < key[v]) {

                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print MST
    printf("\nEdges in Minimum Spanning Tree:\n");
    printf("Edge\tWeight\n");

    for (int i = 1; i < n; i++) {
        printf("%d - %d\t%d\n",
               parent[i], i, graph[i][parent[i]]);

        totalCost += graph[i][parent[i]];
    }

    printf("Total cost of MST = %d\n", totalCost);
}

int main()
{
    int n;
    int graph[MAX][MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 if no edge):\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    primMST(graph, n);

    return 0;
}

