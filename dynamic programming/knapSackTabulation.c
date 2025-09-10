#include <stdio.h>
#include <stdlib.h>
#define MAX 50
int n, dp[MAX][MAX], capacity, values[MAX], weight[MAX], count = 0;

int max(int a, int b){
    return (a > b) ? a : b;
}

int knapSack(){
    for(int i=0; i<=n; i++){
        for(int j=0; j<=capacity; j++){
            if( i == 0 || j == 0){
                dp[i][j] = 0;
            } else {
                count++;
                if(j < weight[i-1]) dp[i][j] = dp[i-1][j];
                else dp[i][j] = max(dp[i-1][j], values[i-1] + dp[i-1][j-weight[i-1]]);
            }
        }
    }
    return dp[n][capacity];
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

    int maxValue = knapSack();

    printf("\nDP Table:\n");
    for(int i=0; i<=n; i++){
        for(int j=0; j<=capacity; j++){
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }

    printf("\nMaximum value in knapsack: %d\n", maxValue);

    printf("Composition of knapsack/items selected:\n");
    int temp = capacity;
    for(int i=n; i>0; i--){
        if( dp[i][temp] != dp[i-1][temp]){
            printf("Item %d - Value: %d, Weight: %d\n", i, values[i-1], weight[i-1]);
            temp -= weight[i-1];
        }
    }
}

void plotter(){
    FILE *f = fopen("knapSack.txt", "w");

    for(int i = 1; i<=10; i++){
        count = 0;
        capacity = i * 2;
        n = i * 2;

        for(int j = 0; j < n; j++){
            values[j] = rand() % capacity + 1;
            weight[j] = rand() % 50 + 1;
        }

        knapSack();
        fprintf(f, "%d\t%d\n", n, count);
    }

    fclose(f);
    printf("Data written to knapSack.txt\n");
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