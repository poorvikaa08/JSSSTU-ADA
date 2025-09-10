#include<stdio.h>
#include<stdlib.h>

int n, opCount = 0, cost[100][100];

void flyod(int adj[n][n], int n) {
    // Initialize the cost matrix with the adjacency matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(adj[i][j] == -1) {
                cost[i][j] = _INTEGRAL_MAX_BITS; // Use a large number instead of infinity
            } else {
                cost[i][j] = adj[i][j];
            }
        }
    }   
  
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {

            int temp = cost[i][k];
            for(int j = 0; j < n; j++) {
                if(cost[i][j] > temp){
                    opCount++;
                    if(cost[k][j] + cost[k][j] < cost[i][j]) {
                        cost[i][j] = cost[i][k] + cost[k][j];
                    }
                }
            }
                
        }
    }
    
}

void tester() {
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    int adj[n][n];

    printf("Enter the adjacency matrix: \n");
    printf("Use -1 to represent infinity\n\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &adj[i][j]);
        }
    }

    flyod(adj, n);

    printf("Transitive closure of the graph is:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", cost[i][j]);
        }
        printf("\n");
    }
}


void plotter() {

    FILE *f1 = fopen("warshallBest.txt", "w");
    FILE *f2 = fopen("warshallWorst.txt", "w");

    for(int k = 1; k<=10; k++ ){
        n = k;
        opCount = 0; // Reset operation count

        int adj[n][n];

        // Best case
        for(int j=0; j<n; j++){
            for(int i=0; i<n; i++){
                if (i != j) adj[j][i] = 1;
                else adj[j][i] = 0;
            }
        }

        flyod(adj, n);
        fprintf(f1, "%d\t%d\n", n, opCount);

        // Worst case
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n;j++){
                adj[i][j] = 0;
            }
        }

        for(int i=0; i<n-1; i++){
            adj[i][i+1] = 1;
        }
        adj[n-1][0] = 1; // Making it a cycle

        flyod(adj, n);
        fprintf(f2, "%d\t%d\n", n, opCount);
    }

    fclose(f1);
    fclose(f2);
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