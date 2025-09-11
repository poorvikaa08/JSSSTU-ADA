#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 20
#define INT_MAX 999

int opCount = 0;

int findMinKey(int key[], int mstSet[], int n) {
    int min = INT_MAX, minIndex = -1;
    
    for(int v = 0; v < n; v++) {
        opCount++;
        if(mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void prims(int graph[MAX][MAX], int n) {
    int parent[MAX];
    int key[MAX];
    int mstSet[MAX];
    
    // Initialize all keys as infinite
    for(int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
        parent[i] = -1;
    }
    
    // Start with first vertex
    key[0] = 0;
    parent[0] = -1;
    
    for(int count = 0; count < n - 1; count++) {
        int u = findMinKey(key, mstSet, n);
        mstSet[u] = 1;
        
        for(int v = 0; v < n; v++) {
            opCount++;
            if(graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    
    // Print MST
    printf("Edge \tWeight\n");
    int totalWeight = 0;
    for(int i = 1; i < n; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
        totalWeight += graph[i][parent[i]];
    }
    printf("Total weight of MST: %d\n", totalWeight);
}

void tester() {
    printf("Enter the number of vertices: ");
    int n;
    scanf("%d", &n);
    
    int graph[MAX][MAX];
    
    printf("Enter the adjacency matrix (use 0 for no edge):\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    
    printf("Minimum Spanning Tree using Prim's algorithm:\n");
    prims(graph, n);
}

void plotter() {
    FILE *f = fopen("prims.txt", "w");
    
    for(int k = 1; k <= 10; k++) {
        int graph[MAX][MAX];
        
        // Create a complete graph with random weights
        for(int i = 0; i < k; i++) {
            for(int j = 0; j < k; j++) {
                if(i == j) {
                    graph[i][j] = 0;
                } else {
                    graph[i][j] = rand() % 10 + 1;
                }
            }
        }
        
        opCount = 0;
        prims(graph, k);
        fprintf(f, "%d\t%d\n", k, opCount);
    }
    
    fclose(f);
}

int main() {
    int choice;
    
    printf("\n(1) Tester\n(2) Plotter\n(3) Exit\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            tester();
            break;
        case 2:
            plotter();
            break;
        case 3:
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
    }
    
    return 0;
}
