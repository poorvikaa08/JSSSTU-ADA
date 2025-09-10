#include <stdio.h>
#include <stdlib.h>
#define MAX 50
int n, memo[MAX][MAX], capacity, values[MAX], weight[MAX], count = 0;

int max(int a, int b){
    return (a > b) ? a : b;
}

int knapSackMemo(int i, int w){
    if(i == 0 || w == 0) return 0;
    
    if(memo[i][w] != -1) return memo[i][w];
    
    count++;
    
    if(weight[i-1] > w){
        memo[i][w] = knapSackMemo(i-1, w);
    } else {
        memo[i][w] = max(knapSackMemo(i-1, w), values[i-1] + knapSackMemo(i-1, w-weight[i-1]));
    }
    
    return memo[i][w];
}

void tester(){
    printf("Enter the number of items: ");
    scanf("%d", &n);

    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &capacity);

    printf("Enter the values and weights of the items:\n");
    for(int i = 0; i < n; i++){
        printf("Item %d - Value: ", i + 1);
        scanf("%d", &values[i]);
        printf("Item %d - Weight: ", i + 1);
        scanf("%d", &weight[i]);
    }

    // Initialize memoization table
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= capacity; j++){
            memo[i][j] = -1;
        }
    }

    count = 0;
    int maxValue = knapSackMemo(n, capacity);

    printf("\nMaximum value in knapsack: %d\n", maxValue);
    printf("Number of recursive calls: %d\n", count);
}

void plotter(){
    FILE *f = fopen("knapSackMemo.txt", "w");

    for(int i = 1; i <= 10; i++){
        count = 0;
        capacity = i * 2;
        n = i * 2;

        for(int j = 0; j < n; j++){
            values[j] = rand() % capacity + 1;
            weight[j] = rand() % 50 + 1;
        }

        // Initialize memoization table
        for(int x = 0; x <= n; x++){
            for(int y = 0; y <= capacity; y++){
                memo[x][y] = -1;
            }
        }

        knapSackMemo(n, capacity);
        fprintf(f, "%d\t%d\n", n, count);
    }

    fclose(f);
    printf("Data written to knapSackMemo.txt\n");
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
