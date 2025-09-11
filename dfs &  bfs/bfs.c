#include<stdio.h>
#include<stdlib.h>

int isCycle = 0, isTester = 0, opCount = 0, n, components = 0;
int queue[100], front = -1, rear = -1;

void bfs(int matrix[100][100], int *visited, int source);

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
            bfs(matrix, visited, i);
        }
    }
}

void bfs(int matrix[100][100], int *visited, int source) {
    front = rear = -1;
    queue[++rear] = source;
    visited[source] = 1;

    if(isTester) {
        printf("%d ", source);
    }

    while(front != rear) {
        int current = queue[++front];
        
        for(int i = 0; i < n; i++) {
            opCount++;
            if(matrix[current][i] && visited[i] == 0) {
                queue[++rear] = i;
                visited[i] = 1;
                if(isTester) {
                    printf("%d ", i);
                }
            } else if(matrix[current][i] && visited[i] == 1) {
                // Check for cycle (back edge found)
                isCycle = 1;
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
    isCycle = 0;
    components = 0;
    opCount = 0;

    checkConnectivity(matrix);

    printf("\n");
    printf("Number of connected components: %d\n", components);

    if(isCycle) {
        printf("Cycle detection: CYCLE FOUND\n");
    } else {
        printf("Cycle detection: NO CYCLE (tree/forest structure)\n");
    }
}

void plotter() {
    FILE *f = fopen("bfs.txt", "w");

    for(int k = 1; k <= 10; k++) {
        n = k;
        int matrix[100][100];
        
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
