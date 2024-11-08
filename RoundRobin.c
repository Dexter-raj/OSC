#include <stdio.h>

int main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrivalTime[n], burstTime[n], remainingTime[n];
    int completionTime[n], turnaroundTime[n], waitingTime[n];
    int currentTime = 0, totalWaitingTime = 0, totalTurnaroundTime = 0;
    int completed = 0;

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &arrivalTime[i], &burstTime[i]);
        remainingTime[i] = burstTime[i];
        completionTime[i] = -1;  // Indicates not completed
    }

    while (completed < n) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (arrivalTime[i] <= currentTime && remainingTime[i] > 0) {
                done = 0;  // There's still work to do
                if (remainingTime[i] > quantum) {
                    currentTime += quantum;
                    remainingTime[i] -= quantum;
                } else {
                    currentTime += remainingTime[i];
                    completionTime[i] = currentTime;
                    turnaroundTime[i] = completionTime[i] - arrivalTime[i];
                    waitingTime[i] = turnaroundTime[i] - burstTime[i];

                    totalWaitingTime += waitingTime[i];
                    totalTurnaroundTime += turnaroundTime[i];
                    remainingTime[i] = 0;  // Process is completed
                    completed++;
                }
            }
        }
        if (done) currentTime++;  // Advance time if no process is ready
    }

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrivalTime[i], burstTime[i], completionTime[i], turnaroundTime[i], waitingTime[i]);
    }

    printf("\nAverage Turnaround Time = %.2f\n", (float)totalTurnaroundTime / n);
    printf("Average Waiting Time = %.2f\n", (float)totalWaitingTime / n);

    return 0;
}
