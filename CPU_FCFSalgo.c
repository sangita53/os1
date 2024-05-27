#include <stdio.h>

typedef struct Process {
    int pid;
    int burst_time;
    int arrival_time;
    int turnaround_time;
    int waiting_time;
} Process;

void fcfs(Process processes[], int n, float *avg_turnaround_time, float *avg_waiting_time, int gantt_chart[]) {
    int time = 0;
    float total_turnaround_time = 0, total_waiting_time = 0;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time > time) {
            time = processes[i].arrival_time;
        }
        processes[i].waiting_time = time - processes[i].arrival_time;
        time += processes[i].burst_time;
        processes[i].turnaround_time = time - processes[i].arrival_time;
        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;
        gantt_chart[i] = processes[i].pid; // Store the PID for Gantt chart
    }

    *avg_turnaround_time = total_turnaround_time / n;
    *avg_waiting_time = total_waiting_time / n;
}

int main() {
    // Example usage
    Process processes[] = {
        {1, 5, 0, 0, 0},
        {2, 3, 2, 0, 0},
        {3, 8, 4, 0, 0},
        {4, 6, 6, 0, 0}
    };
    int n = sizeof(processes) / sizeof(processes[0]);
    float avg_turnaround_time, avg_waiting_time;
    int gantt_chart[n];

    fcfs(processes, n, &avg_turnaround_time, &avg_waiting_time, gantt_chart);

    printf("PID\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].turnaround_time, processes[i].waiting_time);
    }

    printf("First Come First Serve (FCFS) Algorithm - Average Turnaround Time: %.2f, Average Waiting Time: %.2f\n", avg_turnaround_time, avg_waiting_time);

    // Print Gantt Chart
    printf("Gantt Chart:\n|");
    for (int i = 0; i < n; i++) {
        printf(" P%d |", gantt_chart[i]);
    }
    printf("\n");

    return 0;
}

