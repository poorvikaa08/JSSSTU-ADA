#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count = 0;

int binarySearch(int key, int *a, int high, int low){
    count++;
    int mid = (high + low) / 2;

    if (low > high)
        return -1;
    if (*(a + mid) == key)
        return mid;
    else if (*(a + mid) > key)
        return binarySearch(key, a, mid - 1, low);
    else
        return binarySearch(key, a, high, mid + 1);
}

void tester() {
    int *arr, n, key, ans;

    printf("\nEnter array size: ");
    scanf("%d", &n);

    arr = (int *)malloc(n * sizeof(int));

    printf("\nEnter array elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", (arr + i));
    }

    printf("\nEnter key to be searched : ");
    scanf("%d", &key);

    ans = binarySearch(key, arr, n - 1, 0);
    if (ans == -1)
        printf("\nKey not found!\n");
    else
        printf("\nKey found at %d index\n", ans);
}

void plotter() {
    srand(time(NULL));
    int *arr;
    int n, key, res;

    FILE *f1, *f2, *f3;

    f1 = fopen("binarybest.txt", "w");
    f2 = fopen("binaryavg.txt", "w");
    f3 = fopen("binaryworst.txt", "w");

    n = 2;

    while (n <= 1024){
        arr = (int *)malloc(n * sizeof(int));

        // best case
        for (int i = 0; i < n; i++)
            *(arr + i) = 1;
        int mid = (n - 1) / 2;
        *(arr + mid) = 0;
        count = 0;
        res = binarySearch(0, arr, n - 1, 0);
        fprintf(f1, "%d\t%d\n", n, count);

        // average case
        for (int i = 0; i < n; i++)
            *(arr + i) = i+1;
        key = rand() % n + 1;
        count = 0;
        res = binarySearch(key, arr, n - 1, 0);
        fprintf(f2, "%d\t%d\n", n, count);

        // worst case
        for (int i = 0; i < n; i++)
            *(arr + i) = 0;
        count = 0;
        res = binarySearch(1, arr, n - 1, 0);
        fprintf(f3, "%d\t%d\n", n,count);


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