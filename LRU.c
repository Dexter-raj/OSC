#include <stdio.h>

void LRU(int pages[], int n, int frames) {
    int frame[frames];
    int recent[frames]; // Tracks the usage for each frame
    int faults = 0;

    for (int i = 0; i < frames; i++) {
        frame[i] = -1; // Initialize frames as empty
        recent[i] = -1; // Initialize recent usage tracker
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in frame
        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                found = 1;
                recent[j] = i; // Update recent usage to current time
                break;
            }
        }

        if (!found) { // Page fault
            int replace = -1, lru = n; // Assume LRU page is at the farthest time

            // Find the least recently used page
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) { // Empty frame available
                    replace = j;
                    break;
                } else if (recent[j] < lru) {
                    lru = recent[j];
                    replace = j;
                }
            }

            frame[replace] = page; // Replace the LRU page
            recent[replace] = i; // Update recent usage
            faults++; // Increment fault count
        }

        // Display current frame status
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
