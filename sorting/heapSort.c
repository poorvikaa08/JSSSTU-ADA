#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n, count1, count2 = 0;

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int *arr, int i, int size){
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int parent = i;

    if (left < size && ++count1 && arr[left] > arr[parent]){
        parent = left;
    }

    if (right < size && ++count1 && arr[right] > arr[parent]){
        parent = right;
    }

    if (parent != i){
        swap(&arr[i], &arr[parent]);
        heapify(arr, parent, size);
    }
}

void heapSort(int *arr, int n){
    for (int i = (n / 2) - 1; i >= 0; i--){
        heapify(arr, i, n);
    }

    count2 = count1;
    count1 = 0;

    for (int i = n - 1; i >= 0; i--){
        swap(&arr[0], &arr[i]);
        heapify(arr, 0, i);
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

    heapSort(arr, n);

    printf("Sorted array: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}

void plotter()
{
    srand(time(NULL));
    FILE *f1, *f2, *f3;
    f1 = fopen("heapBest.txt", "w");
    f2 = fopen("heapWorst.txt", "w");
    f3 = fopen("heapAvg.txt", "w");

    int n = 100;

    while (n <= 1000)
    {
        int arr[n];

        for (int i = 0; i < n; i++)
            arr[i] = n - i + 1;
        count1 = 0;
        heapSort(arr, n);
        fprintf(f1, "%d\t%d\n", n, count1 > count2 ? count1 : count2);

        for (int i = 0; i < n; i++)
            arr[i] = i + 1;
        count1 = 0;
        heapSort(arr, n);
        fprintf(f2, "%d\t%d\n", n, count1 > count2 ? count1 : count2);

        for (int i = 0; i < n; i++)
            arr[i] = rand() % n;
        count1 = 0;
        heapSort(arr, n);
        fprintf(f3, "%d\t%d\n", n, count1 > count2 ? count1 : count2);

        n += 100;
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