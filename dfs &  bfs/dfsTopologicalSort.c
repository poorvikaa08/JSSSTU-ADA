#include <stdio.h>
#include <stdlib.h>

int n, opCount = 0, top = -1, isCycle = 0, components = 0;

// DFS function for topological sorting with cycle detection
int dfs(int mat[100][100], int *vis, int *track, int source, int *stack) {
    vis[source] = 1;
    track[source] = 1;  // Mark as currently being processed

    for (int i = 0; i < n; i++) {
        opCount++;
        if (mat[source][i]) {
            // If adjacent node is in current path (back edge) -> cycle found
            if (track[i]) {
                return 1;  // Cycle detected
            }
            
            // If not visited, recursively visit and check for cycle
            if (!vis[i] && dfs(mat, vis, track, i, stack)) {
                return 1;  // Cycle found in recursive call
            }
        }
    }

    stack[++top] = source;  // Add to stack when completely processed
    track[source] = 0;      // Remove from current path
    return 0;               // No cycle found
}

// Check connectivity and perform topological sorting
int* checkConnectivity(int mat[100][100]) {
    int vis[n], track[n];
    int* stack = (int*)malloc(n * sizeof(int));
    
    // Initialize arrays
    for (int i = 0; i < n; i++) {
        vis[i] = 0;
        track[i] = 0;
    }

    components = 0;
    
    // Check each unvisited node
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            components++;
            if (dfs(mat, vis, track, i, stack)) {
                isCycle = 1;
                free(stack);
                return NULL;  // Cycle found, topological sort impossible
            }
        }
    }

    return stack;
}

void tester() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    
    int adjMat[100][100];

    printf("Enter the adjacency matrix (for directed graph):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &adjMat[i][j]);
        }
    }

    // Reset global variables
    opCount = 0;
    top = -1;
    isCycle = 0;
    components = 0;

    int *stack = checkConnectivity(adjMat);
  
    if (components == 1) {
        printf("Graph connectivity: CONNECTED (all nodes reachable)\n");
    } else {
        printf("Graph connectivity: DISCONNECTED (%d separate groups)\n", components);
    }
    
    if (stack == NULL) {
        printf("Cannot perform topological sorting (cycles exist)!\n");
    } else {
        printf("Topological sorting order: ");
        
        while (top != -1) {
            printf("%d ", stack[top--]);
        }
        printf("\n");
        free(stack);
    }
}

void plotter() {
    FILE *f = fopen("topologicalSort.txt", "w");

    for (int k = 1; k <= 10; k++) {
        n = k;
        int adjMat[n][n];


        // Create a DAG (Directed Acyclic Graph) for testing
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                adjMat[i][j] = 0;  // Edges from lower to higher numbered nodes
            }
        }

        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                adjMat[i][j] = 0;
            }
        }

        // Reset variables
        opCount = 0;
        top = -1;
        isCycle = 0;
        components = 0;
        
        int* result = checkConnectivity(adjMat);
        if (result != NULL) {
            free(result);
        }
        
        fprintf(f, "%d\t%d\n", n, opCount);
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