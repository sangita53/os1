#include <stdio.h>

int main() {
    int i, j, k;
    int m = 3; // Number of resources
    int n = 5; // Number of processes
    int alloc[5][3], max[5][3], avail[3];
    int total_available[3] = {0, 0, 0};
    int total_alloc[3] = {0, 0, 0};

    // int alloc[5][3] = {{0, 1, 0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}}; 
    // int max[5][3] = {{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
    // int avail[3] = {3, 3, 2};


    printf("Enter allocation matrix (%d x %d):\n", n, m);
    for (i = 0; i < n; i++) {
        printf("Enter allocation for P%d: ", i);
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter Maximum Resources matrix (%d x %d):\n", n, m);
    for (i = 0; i < n; i++) {
        printf("Enter Maximum Resources for P%d: ", i);
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter available resources vector (%d):\n", m);
    for (i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Calculate total allocated resources
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            total_alloc[j] += alloc[i][j];
        }
    }

    // Calculate total available resources
    for (i = 0; i < m; i++) {
        total_available[i] = avail[i];
    }

    printf("Total Available Resources: ");
    for (i = 0; i < m; i++) {
        printf("%d ", total_available[i]);
    }
    printf("\n");

    printf("Total Allocated Resources: ");
    for (i = 0; i < m; i++) {
        printf("%d ", total_alloc[i]);
    }
    printf("\n");

    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++) {
        f[k] = 0;
    }

    int need[n][m];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("Initial Need Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    int y = 0;
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    ans[ind++] = i;
                    printf("Allocating resources for Process P%d\n", i);
                    printf("Updated Available Resources: ");
                    for (y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];
                        printf("%d ", avail[y]);
                    }
                    printf("\n");
                    f[i] = 1;
                }
            }
        }
    }

    int flag = 1;
    for (i = 0; i < n; i++) {
        if (f[i] == 0) {
            flag = 0;
            printf("\nThe system is not safe\n");
            break;
        }
    }

    if (flag == 1) {
        printf("\nFollowing is the SAFE Sequence\n");
        for (i = 0; i < n - 1; i++) {
            printf(" P%d ->", ans[i]);
        }
        printf(" P%d", ans[n - 1]);
    }

    return 0;
}