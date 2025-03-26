#include <stdio.h>

int lru(int recent[], int fsize) {
    int min = recent[0], pos = 0;
    for (int i = 1; i < fsize; i++) {
        if (recent[i] < min) {
            min = recent[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int n, fsize, reference[50], frame[10], recent[10], fault = 0, time = 0;

    printf("Enter number of references: ");
    scanf("%d", &n);
    printf("Enter reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &reference[i]);
    printf("Enter frame size: ");
    scanf("%d", &fsize);

    for (int i = 0; i < fsize; i++)
        frame[i] = -1; // Initialize frames as empty

    for (int i = 0; i < n; i++) {
        int found = 0;
        
        // Check if page is already in frame
        for (int j = 0; j < fsize; j++) {
            if (frame[j] == reference[i]) {
                found = 1;
                recent[j] = time++; // Update recent usage time
                break;
            }
        }

        // If not found, replace LRU page
        if (!found) {
            int pos = lru(recent, fsize);
            frame[pos] = reference[i];
            recent[pos] = time++;
            fault++;
        }
    }

    printf("\nTotal Page Faults: %d\n", fault);
    return 0;
}
