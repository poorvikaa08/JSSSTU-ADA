#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count;
int i, j;

int linearsearch(int *arr, int n, int key){
    count = 0;
    for(i = 0; i < n; i++){
        count++;
        if(*(arr + i) == key)
            return i + 1;
    }
    return -1;
}

void tester(){
    int n, key, *arr;
    int ans;

    printf("\n Enter the number of elements");
    scanf("%d", &n);

    arr = (int *)malloc(n * sizeof(int));

    printf("\n Enter the array elements");
    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("\n Enter the key element");
    scanf("%d", &key);

    ans = linearsearch(arr, n, key);
    if(ans == -1)
        printf("\n not found");
    else
        printf("\n Found at %d ", ans);
}

void plotter(){
    int *arr, r, key;

    FILE *f1 = fopen("linearbest.txt", "w");
    FILE *f2 = fopen("linearavg.txt", "w");
    FILE *f3 = fopen("linearworst.txt", "w");

    int n = 2;

    while(n <= 1024){
        arr = (int *)malloc(n * sizeof(int));

        // best case
        for(i = 0; i < n; i++)
            *(arr + i) = 1;
        r = linearsearch(arr, n, 1);
        fprintf(f1, "%d\t%d\n", n, count);

        // average case
        for(i = 0; i < n; i++)
            *(arr + i) = rand() % n;
        key = rand() % n; 
        r = linearsearch(arr, n, key);
        fprintf(f2, "%d\t%d\n", n, count);

        // worst case
        for(i = 0; i < n; i++)
            *(arr + i) = 0;
        r = linearsearch(arr, n, 1);
        fprintf(f3, "%d\t%d\n", n, count);

        n = n * 2;
        free(arr);
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
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