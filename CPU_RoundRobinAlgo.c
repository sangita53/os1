
#include <stdio.h>
#include <stdlib.h>

struct process {
    int arrivalTime;
    int burstTime;
    int finishTime;
    int turnTime;
    int waitingTime;
    int startTime;
};

struct ganttChart {
    int processID;
    int startTime;
    int endTime;
};

int main() {
    int n, tq, total_TAT = 0, BT[50], total_WT = 0, index;
    struct process p[50];
    float avgTAT, avgWT;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter time quantum of CPU: ");
    scanf("%d", &tq);

    // Separate input for arrival times
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time of process %d: ", i + 1);
        scanf("%d", &p[i].arrivalTime);
    }

    // Separate input for burst times
    for (int i = 0; i < n; i++) {
        printf("Enter burst time of process %d: ", i + 1);
        scanf("%d", &p[i].burstTime);
        BT[i] = p[i].burstTime;
    }

    int q[100], front = -1, rear = -1;
    q[++rear] = 0;

    int current_time = 0;
    int completed = 0;
    int mark[100] = {0};

    struct ganttChart gantt[100];
    int ganttIndex = 0;

    while (completed != n) {
        index = q[++front];

        // to find start time of process
        if (BT[index] == p[index].burstTime) {
            p[index].startTime = current_time > p[index].arrivalTime ? current_time : p[index].arrivalTime;
            current_time = p[index].startTime;
        }

        int executionTime = (BT[index] > tq) ? tq : BT[index];
        BT[index] -= executionTime;
        current_time += executionTime;

        gantt[ganttIndex].processID = index + 1;
        gantt[ganttIndex].startTime = current_time - executionTime;
        gantt[ganttIndex].endTime = current_time;
        ganttIndex++;

        // check if process is finished or not
        if (BT[index] == 0) {
            p[index].finishTime = current_time;
            p[index].turnTime = p[index].finishTime - p[index].arrivalTime;
            p[index].waitingTime = p[index].turnTime - p[index].burstTime;
            total_WT += p[index].waitingTime;
            total_TAT += p[index].turnTime;
            completed++;
        }

        // add new processes to queue if arrival time <= current time
        for (int i = 1; i < n; i++) {
            if (BT[i] > 0 && p[i].arrivalTime <= current_time && !mark[i]) {
                mark[i] = 1;
                q[++rear] = i;
            }
        }

        // re-enter current process into queue if it is not finished
        if (BT[index] > 0) {
            q[++rear] = index;
        }
    }

    avgWT = (float)total_WT / n;
    avgTAT = (float)total_TAT / n;

    printf("\nProcess\tAT\tBT\tFT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, p[i].arrivalTime, p[i].burstTime, p[i].finishTime, p[i].turnTime, p[i].waitingTime);
    }

    printf("\nAverage Waiting Time = %.2f\n", avgWT);
    printf("Average Turnaround Time = %.2f\n", avgTAT);

    // Print Gantt Chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < ganttIndex; i++) {
        printf("| P%d (%d - %d) ", gantt[i].processID, gantt[i].startTime, gantt[i].endTime);
    }
    printf("|\n");

    return 0;
}
//  //input 4 && arrival : 0 1 2 4 && brust : 5 4 2 1 && TQ = 2
