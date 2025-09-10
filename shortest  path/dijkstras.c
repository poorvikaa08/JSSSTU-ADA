#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 20
#define INT_MAX 999

int opCount = 0;

void dijkstras(int n, int cost[MAX][MAX], int distance[MAX], int source) {
    int visited[MAX], u;

    for(int i =0; i<n; i++){
        distance[i] = cost[source][i];
        visited[i] = 0;
    }

    visited[source] = 1;
    distance[source] = 0;

    for(int i=1; i<n; i++){
        int min = INT_MAX;
        
        for(int j=0; j<n; j++){
            if(visited[j] == 0 && distance[j] < min){
                min = distance[j];
                u = j;
            }
        }

        visited[u] = 1;

        for(int v=0; v<n; v++){
            opCount++;

            if(visited[v] == 0 && distance[v] > distance[u] + cost[u][v]){
                distance[v] = distance[u] + cost[u][v];
            }
        }
    }
}

void tester(){
    printf("Enter the number of nodes: ");
    int n, source, cost[MAX][MAX], distance[MAX];
    scanf("%d", &n);

    printf("Enter the adjacency matrix (use -1 for infinity):\n");
    int adj[MAX][MAX];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
            if (adj[i][j] == -1) {
                adj[i][j] = INT_MAX;
            }
        }
    }

    printf("Enter the source node: ");
    scanf("%d", &source);

    dijkstras(n, adj, distance, source);

    printf("Shortest distances from node %d:\n", source);
    printf("Source\tDestination\tDistance\n");
    for(int i =0; i<n; i++) {
        printf("%d\t%d\t\t%d\n", source, i+1, distance[i]);
    }
}

void plotter() {
    FILE *f = fopen("dijkstras.txt", "w");

    for(int k = 1; k<=10; k++){
        int cost[MAX][MAX], distance[MAX];
        for(int i=0; i<k; i++){
            for(int j=0; j<k; j++){
                if(i == j) {
                    cost[i][j] = 0;
                } else {
                    cost[i][j] = rand() % 10 + 1; // Random weights between 1 and 10
                }
            }
            opCount = 0;

            dijkstras(k, cost, distance, i);
            fprintf(f, "%d\t%d\t%d\n", i, k, opCount);
        }
    }
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