#include <stdio.h>

void LRU(int pages[], int n, int frames) {
    int frame[frames], time[frames];
    int faults = 0, t = 0;

    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0, lru = 0;

        // Check if page is already in frame
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                time[j] = ++t;
                break;
            }
        }

        if (!found) {
            int min_time = time[0];
            for (int j = 1; j < frames; j++) {
                if (time[j] < min_time) {
                    min_time = time[j];
                    lru = j;
                }
            }
            frame[lru] = pages[i];
            time[lru] = ++t;
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
    printf("Total Page Faults (LRU): %d\n", faults);
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

    LRU(pages, n, frames);
    return 0;
}
