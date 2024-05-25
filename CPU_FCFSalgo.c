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
