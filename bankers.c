#include <stdio.h>

int main() {
    int n = 5, m = 3;
    int alloc[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    int max[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    int avail[3] = {3, 3, 2};

    int need[5][3], finish[5] = {0}, safeSeq[5], work[3], i, j, k;

    // Calculate Need matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Copy available to work
    for (i = 0; i < m; i++)
        work[i] = avail[i];

    // Banker's algorithm to find safe sequence
    int count = 0;
    while (count < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j])
                        break;

                if (j == m) {
                    for (k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) break;
    }

    // Display results
    if (count == n) {
        printf("System is safe.\nSafe Sequence: ");
        for (i = 0; i < n; i++)
            printf("P%d%s", safeSeq[i], i == n - 1 ? "\n\n" : "->");

        // Print table header
        printf("PROCESS\tALLOCATED\tMAX\t\tNEED\t\tAVAILABLE\n");

        int tempAvail[3] = {3, 3, 2}; // original available

        for (i = 0; i < n; i++) {
            int p = safeSeq[i];

            printf("P%d\t", p);
            for (j = 0; j < m; j++)
                printf("%d ", alloc[p][j]);
            printf("\t\t");

            for (j = 0; j < m; j++)
                printf("%d ", max[p][j]);
            printf("\t");

            for (j = 0; j < m; j++)
                printf("%d ", need[p][j]);
            printf("\t");

            for (j = 0; j < m; j++) {
                printf("%d ", tempAvail[j]);
                tempAvail[j] += alloc[p][j]; // update available
            }
            printf("\n");
        }
    } else {
        printf("System is not safe.\n");
    }

    return 0;
}
