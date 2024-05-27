#include <stdio.h>

struct gantt {
    int process_id;
    int start_time;
    int end_time;
};

int main() {
    int total_BT = 0, smallest, n;
    int tat = 0, wt = 0;

    printf("\nEnter the number of processes: \n");
    scanf("%d", &n);

    int burst_time[n], remaining_bt[n], at[n], completion_time[n], turnaround_time[n], waiting_time[n];
    struct gantt g[100]; // Array to store Gantt chart events
    int gantt_index = 0; // Gantt chart index

    // Input burst times
    printf("\nBurst time\n");
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process P%d: ", i);
        scanf("%d", &burst_time[i]);
        remaining_bt[i] = burst_time[i]; // Initialize remaining burst times
        total_BT += burst_time[i];
    }

    // Input arrival times
    printf("\nArrival time\n");
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process P%d: ", i);
        scanf("%d", &at[i]);
    }

    remaining_bt[n] = 9999; // Sentinel value for comparison

    int time = 0, completed = 0;
    while (completed < n) {
        smallest = n;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && remaining_bt[i] > 0 && remaining_bt[i] < remaining_bt[smallest])
                smallest = i;
        }

        if (smallest == n) {
            time++;
            continue;
        }

        // Record Gantt chart event
        g[gantt_index].process_id = smallest;
        g[gantt_index].start_time = time;

        time += remaining_bt[smallest];
        completion_time[smallest] = time;
        turnaround_time[smallest] = completion_time[smallest] - at[smallest];
        waiting_time[smallest] = turnaround_time[smallest] - burst_time[smallest];

        tat += turnaround_time[smallest];
        wt += waiting_time[smallest];
        remaining_bt[smallest] = 0;
        completed++;

        // Update end time in Gantt chart event
        g[gantt_index].end_time = time;
        gantt_index++;
    }

    // Display results
    printf("\nProcess\t\tBT\t\tAT\t\tCT\t\tTAT\t\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\n", i, burst_time[i], at[i], completion_time[i], turnaround_time[i], waiting_time[i]);
    }

    // Display average times
    printf("\n\nAverage waiting time = %.2f", wt * 1.0 / n);
    printf("\nAverage turnaround time = %.2f", tat * 1.0 / n);

    // Print Gantt chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < gantt_index; i++) {
        printf("| P%d ", g[i].process_id);
    }
    printf("|\n");
    for (int i = 0; i < gantt_index; i++) {
        printf("%d\t", g[i].start_time);
    }
    printf("%d\n", g[gantt_index - 1].end_time);

    return 0;
}

// Input : 5  &&  6 2 8 3 4   &&   2 5 1 0 4
