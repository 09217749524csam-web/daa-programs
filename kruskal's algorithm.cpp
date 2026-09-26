#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure to represent an edge
struct Edge {
    int src;
    int dest;
    int weight;
};

// Find the parent of a vertex
int find(int parent[], int i)
{
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);

    return parent[i];
}

// Combine two sets
void unionSets(int parent[], int rank[], int x, int y)
{
    int rootX = find(parent, x);
    int rootY = find(parent, y);

    if (rootX != rootY) {
        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

// Compare edges for sorting
int compare(const void *a, const void *b)
{
    struct Edge *edgeA = (struct Edge *)a;
    struct Edge *edgeB = (struct Edge *)b;

    return edgeA->weight - edgeB->weight;
}

void kruskalMST(struct Edge edges[], int V, int E)
{
    struct Edge result[MAX];

    int parent[MAX];
    int rank[MAX];

    // Initially, every vertex is its own set
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    // Sort edges by weight
    qsort(edges, E, sizeof(struct Edge), compare);

    int edgeCount = 0;
    int totalCost = 0;

    printf("\nEdges in Minimum Spanning Tree:\n");
    printf("Edge\tWeight\n");

    // Process edges in increasing order
    for (int i = 0; i < E && edgeCount < V - 1; i++) {

        int u = edges[i].src;
        int v = edges[i].dest;

        int rootU = find(parent, u);
        int rootV = find(parent, v);

        // Add edge if it does not create a cycle
        if (rootU != rootV) {
            result[edgeCount] = edges[i];

            printf("%d - %d\t%d\n",
                   u, v, edges[i].weight);

            totalCost += edges[i].weight;
            edgeCount++;

            unionSets(parent, rank, rootU, rootV);
        }
    }

    printf("Total cost of MST = %d\n", totalCost);
}

int main()
{
    int V, E;
    struct Edge edges[MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("Enter edges (source destination weight):\n");

    for (int i = 0; i < E; i++) {
        scanf("%d %d %d",
              &edges[i].src,
              &edges[i].dest,
              &edges[i].weight);
    }

    kruskalMST(edges, V, E);

    return 0;
}

