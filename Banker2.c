#include <stdio.h>
#include <limits.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int n, m;

    // Input number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};  // Mark all processes as unfinished
    int safeSequence[MAX_PROCESSES];
    int index = 0;

    // Input Allocation Matrix
    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Maximum Matrix
    printf("Enter the Maximum Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available Resources
    printf("Enter the Available Resources:\n");
    for (int j = 0; j < m; j++) {
        printf("Resource %d: ", j);
        scanf("%d", &available[j]);
    }

    // Calculate the Need matrix
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Find Safe Sequence
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {  // If process i is not finished
                int flag = 1;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > available[j]) {
                        flag = 0;
                        break;
                    }
                }
                if (flag) {  // If all resources are available for process i
                    safeSequence[index++] = i;
                    for (int y = 0; y < m; y++) {
                        available[y] += allocation[i][y];
                    }
                    finish[i] = 1;
                }
            }
        }
    }

    // Check if all processes are finished
    int safe = 1;
    for (int i = 0; i < n; i++) {
        if (finish[i] == 0) {
            safe = 0;
            printf("The system is not in a safe state.\n");
            break;
        }
    }

    if (safe) {
        printf("\nSafe Sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d ", safeSequence[i]);
        }
        printf("\n");
    }

    // Display all matrices
    printf("\nAllocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    printf("\nMaximum Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }

    printf("\nAvailable Resources After Execution:\n");
    for (int j = 0; j < m; j++) {
        printf("%d ", available[j]);
    }
    printf("\n");

    return 0;
}
