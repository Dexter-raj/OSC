#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];               // Available instances of each resource
int maximum[MAX_PROCESSES][MAX_RESOURCES];   // Maximum demand of each process
int allocation[MAX_PROCESSES][MAX_RESOURCES]; // Resources currently allocated to each process
int need[MAX_PROCESSES][MAX_RESOURCES];      // Remaining needs of each process

// Function to check if the system is in a safe state
bool isSafe(int num_processes, int num_resources) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {0};  // Finish flag for each process
    int safeSequence[MAX_PROCESSES];   // Array to store the safe sequence
    int count = 0;                     // Counter for the safe sequence

    // Initialize work with available resources
    for (int i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    while (count < num_processes) {
        bool found = false;
        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {  // Process is not yet finished
                bool canProceed = true;
                for (int j = 0; j < num_resources; j++) {
                    if (need[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }

                // If the process can proceed
                if (canProceed) {
                    for (int j = 0; j < num_resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        // If no process could proceed, the system is in an unsafe state
        if (!found) {
            printf("The system is not in a safe state.\n");
            return false;
        }
    }

    // If all processes could proceed, the system is in a safe state
    printf("The system is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < num_processes; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
    return true;
}

int main() {
    int num_processes, num_resources;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter the available resources: \n");
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum demand of each process: \n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    printf("Enter the allocated resources of each process: \n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = maximum[i][j] - allocation[i][j]; // Calculate need matrix
        }
    }

    isSafe(num_processes, num_resources);

    return 0;
}
