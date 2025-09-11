#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

int opCount = 0;

bool stringMatching(char *text, char *pattern, int m, int n) {
    opCount = 0;

    for(int i = 0; i <= n - m; i++) {
        int j = 0;
        while(j < m) {
            opCount++;
            if(pattern[j] != text[i + j]) {
                break;
            }
            j++;
        }

        if(j == m) {
            return true;
        }
    }

    return false;
}

void tester() {

    int m, n;
    char text[100], pattern[100];

    printf("Enter the text length: ");
    scanf("%d", &n);
    getchar(); // to consume the newline character after integer input

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove the newline character from the input

    printf("Enter the pattern length: ");
    scanf("%d", &m);
    getchar(); 

    printf("Enter the pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';

    bool isFound = stringMatching(text, pattern, m, n);

    if(isFound) {
        printf("Pattern found in the text.\n");
    } else {
        printf("Pattern not found in the text.\n");
    }

}

void plotter() {
    FILE *f1, *f2, *f3;

    f1 = fopen("bestCase.txt", "w");
    f2 = fopen("averageCase.txt", "w");
    f3 = fopen("worstCase.txt", "w");

    char *text = (char *)malloc(1000 * sizeof(char));
    for(int i = 0; i < 1000; i++) {
        text[i] = 'a';
    }

    srand(time(NULL));

    for(int i = 10; i <= 1000; i +=10){
        char *pattern = (char *)malloc((i + 1) * sizeof(char));

        // Best Case: Pattern matches at the start
        for(int j = 0; j < i; j++) {
            pattern[j] = 'a';
        }
        pattern[i] = '\0';
        stringMatching(text, pattern, i, 1000);
        fprintf(f1, "%d\t%d\n", i, opCount);

        // Average Case: Random pattern
        for(int j = 0; j < i; j++) {    
            pattern[j] = 'a' + (rand() % 26);
        }    
        pattern[i] = '\0';
        stringMatching(text, pattern, i, 1000);
        fprintf(f2, "%d\t%d\n", i, opCount);

        // Worst Case: Pattern does not match
        for(int j = 0; j < i - 1; j++) {
            pattern[j] = 'a';
        }       
        pattern[i - 1] = 'b';
        pattern[i] = '\0';
        stringMatching(text, pattern, i, 1000);
        fprintf(f3, "%d\t%d\n", i, opCount);

        free(pattern);
    }

    free(text);

    fclose(f1); 
    fclose(f2);
    fclose(f3);
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
            printf("Invalid choice!\n");
    }
    return 0;
}
    