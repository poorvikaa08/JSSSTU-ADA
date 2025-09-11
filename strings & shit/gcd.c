#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int opCount = 0;

int euclid(int m, int n) {
    int rem;
    opCount = 0;
    while(n > 0) {
        opCount++;
        rem = m % n;
        m = n;
        n = rem;
    }

    printf("\nGCD (Euclid's algorithm) = %d\n", m);
    return opCount;
}

int consecutiveIntegerCheck(int m, int n) {
    int t = (m > n) ? n : m;
    opCount = 0;

    while(t > 0) {
        opCount++;
        if(m % t == 0 ) {
            opCount++;
            if(n % t == 0) {
                printf("GCD (by Consecutive Integer Check) = %d\n", t);
                return opCount;
            }
        }
        t--;
    }
}

int modifiedEuclid(int m, int n) {
    opCount = 0;

    while(m != n) {
        if(m > n) m = m - n;
        else n = n - m;
        opCount++;
    }

    printf("GCD (Modified Euclid's algorithm) = %d\n", m);

    return opCount;
}

void tester() {
    int m, n;

    printf("Enter two numbers: ");
    scanf("%d %d", &m, &n);

    if(m <= 0 || n <= 0) {
        printf("Cannot compute GCD for non-positive integers. Invalid inputs!\n");
        return;
    }

    printf("Number of operations:\n");
    printf("Euclid's Algorithm: %d\n", euclid(m, n));
    printf("Consecutive Integer Check: %d\n", consecutiveIntegerCheck(m, n));
    printf("Modified Euclid's Algorithm: %d\n", modifiedEuclid(m, n));
    
}

void plotter() {
    FILE *f1, *f2, *f3, *f4, *f5, *f6;

    f1 = fopen("euclidBest.txt", "w");
    f2 = fopen("euclidWorst.txt", "w");
    f3 = fopen("consecutiveBest.txt", "w");
    f4 = fopen("consecutiveWorst.txt", "w");
    f5 = fopen("modifiedBest.txt", "w");
    f6 = fopen("modifiedWorst.txt", "w");

    for(int i = 10; i <= 100; i += 10) {
        int min = INT_MAX, max = INT_MIN;
        for(int j = 1; j <= i; j++) {
            for(int k = 1; k <= i; k++) {
                euclid(j, k);
                if(opCount < min) min = opCount;
                if(opCount > max) max = opCount;
            }
        }

        fprintf(f1, "%d\t%d\n", i, min);
        fprintf(f2, "%d\t%d\n", i, max);
    }

    for(int i = 10; i <= 100; i += 10) {
        int min = INT_MAX, max = INT_MIN;
        for(int j = 1; j <= i; j++) {
            for(int k = 1; k <= i; k++) {
                consecutiveIntegerCheck(j, k);
                if(opCount < min) min = opCount;
                if(opCount > max) max = opCount;
            }
        }

        fprintf(f3, "%d\t%d\n", i, min);
        fprintf(f4, "%d\t%d\n", i, max);
    }

    for(int i = 10; i <= 100; i += 10) {
        int min = INT_MAX, max = INT_MIN;
        for(int j = 1; j <= i; j++) {
            for(int k = 1; k <= i; k++) {
                modifiedEuclid(j, k);
                if(opCount < min) min = opCount;
                if(opCount > max) max = opCount;
            }
        }

        fprintf(f5, "%d\t%d\n", i, min);
        fprintf(f6, "%d\t%d\n", i, max);
    }
}


int main() {
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
    return 0;
}
