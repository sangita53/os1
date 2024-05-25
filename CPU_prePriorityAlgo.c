#include <stdio.h>

typedef struct Process {
    int pid;
    int burst_time;
    int arrival_time;
    int priority;
    int remaining_time;
    int turnaround_time;
    int waiting_time;
} Process;

void preemptive_priority(Process processes[], int n, float *avg_turnaround_time, float *avg_waiting_time) {
    int time = 0;
    int completed = 0;
    float total_turnaround_time = 0, total_waiting_time = 0;

    while (completed != n) {
        int highest_priority = -1;
        int next_process = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0) {
                if (highest_priority == -1 || processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    next_process = i;
                }
            }
        }

        if (next_process == -1) {
            time++;
            continue;
        }

        processes[next_process].remaining_time--;

        if (processes[next_process].remaining_time == 0) {
            completed++;
            processes[next_process].turnaround_time = time + 1 - processes[next_process].arrival_time;
            processes[next_process].waiting_time = processes[next_process].turnaround_time - processes[next_process].burst_time;
            total_turnaround_time += processes[next_process].turnaround_time;
            total_waiting_time += processes[next_process].waiting_time;
        }

        time++;
    }

    *avg_turnaround_time = total_turnaround_time / n;
    *avg_waiting_time = total_waiting_time / n;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for process P%d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
    }

    float avg_turnaround_time, avg_waiting_time;
    preemptive_priority(processes, n, &avg_turnaround_time, &avg_waiting_time);

    printf("\nPreemptive Priority Algorithm - \n\n");
    printf("PID\tAT\tBT\tPriority\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].priority, processes[i].turnaround_time, processes[i].waiting_time);
    }

    printf("Average Turnaround Time: %.2f\nAverage Waiting Time: %.2f\n", avg_turnaround_time, avg_waiting_time);

    return 0;
}



//input 5 && 0 3 3 && 1 4 2 && 2 6 4 && 3 4 6 && 5 2 10