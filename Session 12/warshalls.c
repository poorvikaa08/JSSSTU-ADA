#include<stdio.h>
#include<stdlib.h>

int n, opCount = 0, path[100][100];

void warshall(int adj[n][n], int n){

    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            if(path[i][k]){
                for(int j = 0; j < n; j++){
                    opCount++;
                    path[i][j] = path[i][j] || (path[i][k] && path[k][j]);
                }
            }
        }
    }
}


void tester() {
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    int adj[n][n];

    printf("Enter the adjacency matrix: ");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &adj[i][j])
        }
    }

    warshall(adj, n);

    printf("Transitive closure of the graph is:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", path[i][j]);
        }
        printf("\n");
    }
}


void plotter() {

    FILE *f1 = fopen("warshallBest.txt", "w");
    FILE *f2 = fopen("warshallWorst.txt", "r");

    for(int k = 1; k<=10; k++ ){
        n = k;

        int adj[n][n];

        // Best case
        for(int j=0; j<n; j++){
            for(int i=0; i<n; i++){
                if (i != j) adj[j][i] = 1;
                else adj[j][i] = 0;
            }
        }

        warshall(adj, n);
        fprintf(f1, "%d\t%d\n", n, opCount);

        // Worst case
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n;j++){
                adj[i][j] = 0;
            }
        }

        for(int i=0; i<n-1; i++){
            adj[i][i+1] = 1
        }
        adj[n-1][0] = 1; // Making it a cycle

        warshall(adj, n);
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