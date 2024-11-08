#include <stdio.h>

void FCFS(int pages[], int n, int frames) {
    int frame[frames];
    int front = 0, faults = 0;

    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;

        // Check if page is already in frame
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frame[front] = pages[i];  // Replace oldest page
            front = (front + 1) % frames;  // Update front pointer
            faults++;
        }

        printf("Frames: ");
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults (FCFS): %d\n", faults);
}

int main() {
    int frames, n;
    printf("Enter number of frames (minimum 3): ");
    scanf("%d", &frames);

    printf("Enter number of pages: ");
    scanf("%d", &n);
    
    int pages[n];
    printf("Enter the pages: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    FCFS(pages, n, frames);
    return 0;
}
