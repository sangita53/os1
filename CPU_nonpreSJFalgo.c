#include <stdio.h>

int main() {
    int total_BT = 0, smallest, n;
    int tat = 0, wt = 0;

    printf("\nEnter the number of processes: \n");
    scanf("%d", &n);

    int burst_time[n], remaining_bt[n], at[n], completion_time[n], turnaround_time[n], waiting_time[n];

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

        time += remaining_bt[smallest];
        completion_time[smallest] = time;
        turnaround_time[smallest] = completion_time[smallest] - at[smallest];
        waiting_time[smallest] = turnaround_time[smallest] - burst_time[smallest];

        tat += turnaround_time[smallest];
        wt += waiting_time[smallest];
        remaining_bt[smallest] = 0;
        completed++;
    }

    // Display results
    printf("\nProcess\t\tBT\t\tAT\t\tCT\t\tTAT\t\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\n", i, burst_time[i], at[i], completion_time[i], turnaround_time[i], waiting_time[i]);
    }

    // Display average times
    printf("\n\nAverage waiting time = %.2f", wt * 1.0 / n);
    printf("\nAverage turnaround time = %.2f", tat * 1.0 / n);

    return 0;
}

//Input : 5  &&  6 2 8 3 4   &&   2 5 1 0 4