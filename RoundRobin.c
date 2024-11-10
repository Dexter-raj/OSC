#include<stdio.h>
#include<stdbool.h>

struct Process {
    int id;   // Process ID
    int at;   // Arrival Time
    int bt;   // Burst Time (remaining time)
    int bt_original; // Original Burst Time
    int wt;   // Waiting Time
    int tat;  // Turnaround Time
    int remaining_bt; // Remaining burst time
};

int main() {
    int n, tq, time = 0;
    printf("\nEnter number of processes: ");
    scanf("%d", &n);
    printf("\nEnter time quantum: ");
    scanf("%d", &tq);

    struct Process p[10];  // Array to store processes
    bool in_queue[10] = {false};  // To track if a process is in the queue
    int q[10];  // Queue to store process indices
    int front = 0, rear = 0;  // Queue front and rear pointers

    // Get process details
    for (int j = 0; j < n; j++) {
        p[j].id = j + 1;  // Assign process ID starting from 1
        printf("\nEnter arrival time of process %d: ", p[j].id);
        scanf("%d", &p[j].at);
        printf("Enter burst time of process %d: ", p[j].id);
        scanf("%d", &p[j].bt);
        p[j].bt_original = p[j].bt;  // Store the original burst time
        p[j].wt = 0;
        p[j].tat = 0;
        p[j].remaining_bt = p[j].bt; // Set remaining burst time
    }

    // Enqueue processes that have arrived at the start
    for (int j = 0; j < n; j++) {
        if (p[j].at <= time && !in_queue[j]) {
            q[rear++] = j;  // Add process to queue
            in_queue[j] = true;  // Mark process as added
        }
    }

    // Keep track of the last finish time of the process to calculate WT and TAT properly
    int last_finish_time[10] = {0};

    while (front != rear) {  // While the queue is not empty
        int i = q[front++];  // Dequeue process from the front
        
        // Execute the current process
        if (p[i].remaining_bt > tq) {
            p[i].remaining_bt -= tq;
            time += tq;
        } else {
            time += p[i].remaining_bt;
            p[i].remaining_bt = 0;

            // Calculate waiting time and turnaround time
            p[i].tat = time - p[i].at;
            p[i].wt = p[i].tat - p[i].bt_original;
            printf("Process %d ended at %d\n", p[i].id, time);
        }

        // Enqueue processes that have arrived during the current time quantum
        for (int j = 0; j < n; j++) {
            if (p[j].at <= time && !in_queue[j]) {
                q[rear++] = j;  // Add process to queue
                in_queue[j] = true;
            }
        }

        // If the process is not finished, push it back into the queue
        if (p[i].remaining_bt > 0) {
            q[rear++] = i;
        }
    }

    // Display process information and calculate averages
    printf("\nProcess Table:\n");
    printf("PID\tAT\tBT\tWT\tTAT\n");
    float avgWt = 0, avgTat = 0;
    for (int j = 0; j < n; j++) {
        printf("%d\t%d\t%d\t%d\t%d\n", p[j].id, p[j].at, p[j].bt_original, p[j].wt, p[j].tat);
        avgWt += p[j].wt;
        avgTat += p[j].tat;
    }

    // Calculate and print average waiting time and turnaround time
    avgWt /= n;
    avgTat /= n;
    printf("\nAverage Waiting Time: %.2f\n", avgWt);
    printf("Average Turnaround Time: %.2f\n", avgTat);

    return 0;
}
