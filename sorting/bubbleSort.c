#include <stdio.h>
#include <stdlib.h>

int n, opCount = 0;

int bubbleSort(int *arr){
    opCount = 0;
    for(int i = 0; i < n - 1, i++) {
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