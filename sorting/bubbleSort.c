#include <stdio.h>
#include <stdlib.h>

int n, opCount = 0;

int bubbleSort(int *arr){
    opCount = 0;
    for(int i = 0; i < n - 1; i++) {
        int flag = 1;
        for(int j = 0; j < n - i - 1; j++) {
            opCount++;
            if(arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                flag = 0;
            }
        }
        if(flag) break;
    }
}

void tester() {

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int *arr = (int*)malloc(n * sizeof(int));

    printf("Enter the elements of the array: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    bubbleSort(arr);

    printf("Sorted array: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}

void plotter() {
    int *arr, n;
    srand(time(NULL));

    FILE *f1, *f2, *f3;

    f1 = fopen("Bubblebest.txt", "w");
    f2 = fopen("Bubbleworst.txt", "w");
    f3 = fopen("Bubbleavg.txt", "w");

    n = 10;

    while (n <= 30000){
        arr = (int *)malloc(sizeof(int) * n);
        
        for (int i = 0; i < n; i++) {
            *(arr + i) = n - i;
        }
        bubblesort(arr, n); // worst case
        fprintf(f2, "%d\t%d\n", n, opCount);


        for (int i = 0; i < n; i++){
            *(arr + i) = i + 1;
        }
        bubblesort(arr, n); // best case
        fprintf(f1, "%d\t%d\n", n, opCount);

        for (int i = 0; i < n; i++){
            *(arr + i) = rand() % n;
        }
        bubblesort(arr, n); // average case
        fprintf(f3, "%d\t%d\n", n, opCount);


        if (n < 10000)
            n *= 10;
        else
            n += 10000;
        free(arr);
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
    
}


void main() {
    int choice;

    printf("\n(1)Tester\n(2)Plotter\n(3)Exit\n\nEnter the choice: ");
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
            printf("Invalid choice\n");
    }
}