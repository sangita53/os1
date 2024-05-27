#include <stdio.h>

void findWT(int n, int bt[], int wt[])
{

    wt[0] = 0;

    for (int i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1];
}

void findTAT(int n, int bt[], int wt[], int tat[])
{

    for (int i = 0; i < n; i++)
    {

        tat[i] = bt[i] + wt[i];
    }
}

void findavgTime(int processes[], int n, int bt[])
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    findWT(n, bt, wt);
    findTAT(n, bt, wt, tat);

    printf("Processes | Burst time | Waiting time | Turn around time\n");

    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf(" %d ", (i + 1));
        printf("           %d ", bt[i]);
        printf("              %d", wt[i]);
        printf("                 %d\n", tat[i]);
    }
    float s = (float)total_wt / (float)n;
    float t = (float)total_tat / (float)n;
    printf("Average waiting time = %f", s);
    printf("\n");
    printf("Average turn around time = %f ", t);
}

int main()
{
    int n;
    printf("Enter number of process: ");
    scanf("%d", &n);
    int processes[n], bt[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter BT of process %d : ", i);
        scanf("%d", &bt[i]);
        processes[i] = i;
    }

    findavgTime(processes, n, bt);
    return 0;
}



//input for 3 process : 10 5 8   && for 5 process :  10 3 5 2 8 

// #include <stdio.h>

// typedef struct Process {
//     int pid;
//     int burst_time;
//     int arrival_time;
//     int turnaround_time;
//     int waiting_time;
// } Process;

// void fcfs(Process processes[], int n, float *avg_turnaround_time, float *avg_waiting_time) {
//     int time = 0;
//     float total_turnaround_time = 0, total_waiting_time = 0;

//     for (int i = 0; i < n; i++) {
//         if (processes[i].arrival_time > time) {
//             time = processes[i].arrival_time;
//         }
//         processes[i].waiting_time = time - processes[i].arrival_time;
//         time += processes[i].burst_time;
//         processes[i].turnaround_time = time - processes[i].arrival_time;
//         total_turnaround_time += processes[i].turnaround_time;
//         total_waiting_time += processes[i].waiting_time;
//     }

//     *avg_turnaround_time = total_turnaround_time / n;
//     *avg_waiting_time = total_waiting_time / n;
// }

// int main() {
//     // Example usage
//     Process processes[] = {
//         {1, 5, 0, 0, 0},
//         {2, 3, 2, 0, 0},
//         {3, 8, 4, 0, 0},
//         {4, 6, 6, 0, 0}
//     };
//     int n = sizeof(processes) / sizeof(processes[0]);
//     float avg_turnaround_time, avg_waiting_time;

//     fcfs(processes, n, &avg_turnaround_time, &avg_waiting_time);

//     printf("PID\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n");
//     for (int i = 0; i < n; i++) {
//         printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].turnaround_time, processes[i].waiting_time);
//     }

//     printf("First Come First Serve (FCFS) Algorithm - Average Turnaround Time: %.2f, Average Waiting Time: %.2f\n", avg_turnaround_time, avg_waiting_time);

//     return 0;
// }
