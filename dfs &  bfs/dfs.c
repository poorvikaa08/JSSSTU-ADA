#include<stdio.h>
#include<stdlib.h>

int isCycle = 0, isTester = 0, opCount = 0, n, components = 0;

void dfs(int matrix[100][100], int *visited, int source, int parent);

void checkConnectivity(int matrix[100][100]){
    int visited[100], k = 1;

    for(int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    for(int i = 0; i < n; i++) {
        if(visited[i] == 0) {
            components++;
            if(isTester) {
                printf("Component %d: ", k++);
            }
            dfs(matrix, &visited[0], i, -1);
        }
    }
}

void dfs(int matrix[100][100], int *visited, int source, int parent) {
    visited[source] = 1;

    if(isTester) {
        printf("%d ", source);
    }

    for(int i = 0; i < n; i++) {
        opCount++;
        if(matrix[source][i]) {
            if(visited[i] == 1 && i != parent) {
                isCycle = 1;
            } else if(visited[i] == 0) {
                dfs(matrix, visited, i, source);
            }
        }
    }
}

void tester() {
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    int matrix[100][100];

    printf("Enter the adjacency matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    isTester = 1;
    printf("DFS Traversal: ");
    checkConnectivity(matrix);

    printf("\n");
    printf("Number of connected components: %d\n", components);

    if(isCycle) {
        printf("The graph contains a cycle.\n");
    } else {
        printf("The graph does not contain a cycle.\n");
    }
}

void plotter() {
    FILE *f = fopen("dfs.txt", "w");

    for(int k = 1; k <= 10; k++) {
        n = k;
        int matrix[100][100];
        
        for(int i = 0; i < 100; i++) {
            for(int j = 0; j < 100; j++) {
                matrix[i][j] = 0;
            }
        }
        
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                matrix[i][j] = (i != j) ? 1 : 0;
            }
        }

        opCount = 0;
        isTester = 0;
        isCycle = 0;
        components = 0;
        checkConnectivity(matrix);
        fprintf(f, "%d\t%d\n", n, opCount);
    }

    fclose(f);
}


int main(){
    int choice;

    printf("\n(1) Tester\n(2) Plotter\n(3) Exit\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch(choice){
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