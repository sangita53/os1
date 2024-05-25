#include <stdio.h>
#include <stdlib.h>
#define MAX 20

int main()
{
    int a[MAX][7], i, CPU_Total_Time = 0, CPU_Current_Time, small, n, temp[MAX];
    float awt, atat;
    printf("Enter number of processes : ");
    scanf("%d", &n);

    printf("\nBurst time\n");
    for (i = 0; i < n; i++)
    {

        a[i][0] = i;
        printf("Enter burst time of process P%d : ", i);
        scanf("%d",&a[i][2]);
        CPU_Total_Time += a[i][2];
        a[i][6] = -1;
    }

    printf("\nArrival time\n");
    for (i = 0; i < n; i++)
    {

        a[i][0] = i;
        printf("Enter arrival time of process P%d : ", i);
        scanf("%d", &a[i][1]);
        //CPU_Total_Time += a[i][2];
        a[i][6] = -1;
    }

    small = a[0][1];
    for (i = 0; i < n; i++)
    {
        if (small > a[i][1])
            small = a[i][1];

        temp[i] = a[i][2];
    }

    // printf("Starting CPU_Current_Time at %d",small);
    CPU_Current_Time = small;
    CPU_Total_Time = CPU_Total_Time + small;

    while (CPU_Current_Time < CPU_Total_Time)
    {
        // checking AT
        for (i = 0; i < n; i++)
        {
            if (a[i][6] == -1 && a[i][1] <= CPU_Current_Time)
            {
                small = i;
                break;
            }
        }

        // checking smallest BT for AT
        for (i = 0; i < n; i++)
        {

            if (a[i][6] == -1 && a[i][1] <= CPU_Current_Time)
            {
                if (a[small][2] > a[i][2])
                    small = i;
            }
        }

        CPU_Current_Time++;
        a[small][2]--;
        if (a[small][2] == 0) // processed
        {
            a[small][6] = 0;                // status
            a[small][3] = CPU_Current_Time; // completion time
        }
    }

    atat = 0.0;
    awt = 0.0;
    printf("\nProcess\tAT\tBT\tFT\tTAT\tWT\t");
    for (i = 0; i < n; i++)
    {
        printf("\n %d", a[i][0]);
        printf("\t %d", a[i][1]);
        printf("\t %d", temp[i]);
        printf("\t %d", a[i][3]);
        a[i][4] = a[i][3] - a[i][1];
        printf("\t %d", a[i][4]);
        a[i][5] = a[i][4] - temp[i];
        printf("\t %d", a[i][5]);
        awt = awt + a[i][5];
        atat = atat + a[i][4];
    }
    atat = atat / n;
    awt = awt / n;
    printf("\n\nAverage TAT : %.2f", atat);
    printf("\nAverage WT : %.2f", awt);

    return 0;
}


//Input : 5  &&  6 2 8 3 4   &&   2 5 1 0 4