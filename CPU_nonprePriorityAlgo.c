#include <stdio.h>

void main() {
    int n = 0; // Processes Number
    int CPU_CT = 0; // CPU_CT Current time
    printf("Enter number of Processes: ");
    scanf("%d", &n);

    int AT[n]; // Arrival Time
    int BT[n]; // Burst Time
    int PP[n]; // Process Priority
    int originalPP[n]; // To keep original Process Priority
    int turnaroundTime[n];
    int waittingTime[n];
    int completed[n]; // To mark processes as completed

    printf("\nEnter Arrival Times:\n");
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &AT[i]);
    }

    printf("\nEnter Burst Times:\n");
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &BT[i]);
    }

    printf("\nEnter Priorities:\n");
    for (int i = 0; i < n; i++) {
        printf("Enter priority for process P%d: ", i + 1);
        scanf("%d", &PP[i]);
        originalPP[i] = PP[i]; // Store original priority
    }

    // Initialize the completed array to 0
    for (int i = 0; i < n; i++) {
        completed[i] = 0;
    }

    int NoP = n; // Number of Processes

    while (NoP > 0 && CPU_CT <= 1000) {
        int minPriority = n + 1; // Initialize with a value higher than the maximum possible priority
        int chosenProcess = -1; // To store the index of the chosen process

        // Find the process with the highest priority (lowest value) that has arrived and not completed
        for (int i = 0; i < n; i++) {
            if (AT[i] <= CPU_CT && PP[i] < minPriority && !completed[i]) {
                minPriority = PP[i];
                chosenProcess = i;
            }
        }

        if (chosenProcess == -1) {
            CPU_CT++;
            continue;
        }

        // Process the chosen process
        waittingTime[chosenProcess] = CPU_CT - AT[chosenProcess];
        CPU_CT += BT[chosenProcess];
        turnaroundTime[chosenProcess] = CPU_CT - AT[chosenProcess];
        
        // Mark the process as completed
        completed[chosenProcess] = 1;
        NoP--;
    }

    printf("\n\n\tAT\tBT\tPP\tTAT\tWT\n\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, AT[i], BT[i], originalPP[i], turnaroundTime[i], waittingTime[i]);
    }

    float AvgWT = 0;
    float AVGTaT = 0;
    for (int i = 0; i < n; i++) {
        AvgWT += waittingTime[i];
        AVGTaT += turnaroundTime[i];
    }

    printf("Avg. Turnaround Time = %.2f\nAvg. Waiting Time = %.2f\n", AVGTaT / n, AvgWT / n);
}

//input 5 && arrviavl : 0 1 2 3 5  && brust : 3 4 6 4 2  && priority : 3 2 4 6 10 