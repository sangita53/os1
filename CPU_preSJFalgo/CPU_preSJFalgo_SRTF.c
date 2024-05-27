//preamptive sjf is known as srtf

#include <stdio.h>
#include <stdlib.h>
#define MAX 20

struct gantt {
    int process_id;
    int start_time;
    int end_time;
};

int main() {
    int a[MAX][7], i, CPU_Total_Time = 0, CPU_Current_Time, small, n, temp[MAX];
    float awt, atat;
    struct gantt g[100]; // Array to store Gantt chart events
    int gantt_index = 0; // Gantt chart index

    printf("Enter number of processes : ");
    scanf("%d", &n);

    printf("\nBurst time\n");
    for (i = 0; i < n; i++) {
        a[i][0] = i;
        printf("Enter burst time of process P%d : ", i);
        scanf("%d", &a[i][2]);
        CPU_Total_Time += a[i][2];
        a[i][6] = -1;
    }

    printf("\nArrival time\n");
    for (i = 0; i < n; i++) {
        a[i][0] = i;
        printf("Enter arrival time of process P%d : ", i);
        scanf("%d", &a[i][1]);
        a[i][6] = -1;
    }

    small = a[0][1];
    for (i = 0; i < n; i++) {
        if (small > a[i][1])
            small = a[i][1];

        temp[i] = a[i][2];
    }

    CPU_Current_Time = small;
    CPU_Total_Time = CPU_Total_Time + small;

    while (CPU_Current_Time < CPU_Total_Time) {
        // checking AT
        for (i = 0; i < n; i++) {
            if (a[i][6] == -1 && a[i][1] <= CPU_Current_Time) {
                small = i;
                break;
            }
        }

        // checking smallest BT for AT
        for (i = 0; i < n; i++) {
            if (a[i][6] == -1 && a[i][1] <= CPU_Current_Time) {
                if (a[small][2] > a[i][2])
                    small = i;
            }
        }

        // Record Gantt chart event
        if (gantt_index == 0 || g[gantt_index - 1].process_id != small + 1) {
            g[gantt_index].process_id = small + 1;
            g[gantt_index].start_time = CPU_Current_Time;
            gantt_index++;
        }
        
        CPU_Current_Time++;
        a[small][2]--;

        if (a[small][2] == 0) { // processed
            a[small][6] = 0;                // status
            a[small][3] = CPU_Current_Time; // completion time
            g[gantt_index - 1].end_time = CPU_Current_Time;
        }
    }

    atat = 0.0;
    awt = 0.0;
    printf("\nProcess\tAT\tBT\tFT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               a[i][0], a[i][1], temp[i], a[i][3], 
               (a[i][3] - a[i][1]), 
               (a[i][3] - a[i][1] - temp[i]));
        
        a[i][4] = a[i][3] - a[i][1]; // TAT
        a[i][5] = a[i][4] - temp[i]; // WT
        awt += a[i][5];
        atat += a[i][4];
    }
    atat /= n;
    awt /= n;
    printf("\nAverage TAT : %.2f", atat);
    printf("Average WT : %.2f\n", awt);

    // Print Gantt chart
    printf("\nGantt Chart:\n");
    for (i = 0; i < gantt_index; i++) {
        printf("| P%d ", g[i].process_id);
    }
    printf("|\n");
    for (i = 0; i < gantt_index; i++) {
        printf("%d\t", g[i].start_time);
    }
    printf("%d\n", g[gantt_index - 1].end_time);

    return 0;
}

// Input : 5  &&  6 2 8 3 4   &&   2 5 1 0 4
