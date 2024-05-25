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
    while (completed != n) {
        index = q[++front];

        // to find start time of process
        if (BT[index] == p[index].burstTime) {
            p[index].startTime = current_time > p[index].arrivalTime ? current_time
                                                                     : p[index].arrivalTime;
            current_time = p[index].startTime;
        }

        // check if process if finished nor not
        if (BT[index] > tq) {
            BT[index] -= tq;
            current_time += tq;
        } else {
            current_time += BT[index];

            p[index].finishTime = current_time;
            p[index].turnTime = p[index].finishTime - p[index].arrivalTime;
            p[index].waitingTime = p[index].turnTime - p[index].burstTime;
            total_WT += p[index].waitingTime;
            total_TAT += p[index].turnTime;
            completed++;

            BT[index] = 0;
        }

        // add new processes to queue of at <= CT
        for (int i = 1; i < n; i++) {
            if (BT[i] > 0 && p[i].arrivalTime <= current_time && !mark[i]) {
                mark[i] = 1;
                q[++rear] = i;
            }
        }

        // enter current process again in queue if it not finished
        if (BT[index] > 0) {
            q[++rear] = index;
        }
    }

    avgWT = (float)total_WT / n;
    avgTAT = (float)total_TAT / n;
    printf("\n");
    printf("Process\tAT\tBT\tFT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1,
               p[i].arrivalTime,
               p[i].burstTime,
               p[i].finishTime,
               p[i].turnTime,
               p[i].waitingTime);
    }
    printf("\n");
    printf("Average Waiting Time = %.2f\n", avgWT);
    printf("Average Turnaround Time = %.2f\n", avgTAT);
    return 0;
}
 //input 4 && arrival : 0 1 2 4 && brust : 5 4 2 1 && TQ = 2