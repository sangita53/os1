#include <stdio.h>

void nextFit(int m, int n, int blockSize[], int processSize[])
{
    int allocated[n];
    for (int i = 0; i < n; i++)
    {
        allocated[i] = -1;
    }
    int j = 0;

    for (int i = 0; i < n; i++)
    {
        int count = 0;
        while (count < m)
        {
            if (blockSize[j] >= processSize[i])
            {
                allocated[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
            j = (j + 1) % m;
            count++;
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++)
    {
        printf(" %d\t\t", i + 1);
        printf("%d\t\t", processSize[i]);
        if (allocated[i] != -1)
        {
            printf("%d", allocated[i] + 1);
        }
        else
        {
            printf("Not Allocated");
        }
        printf("\n");
    }
}

int main()
{
    int m, n;
    printf("Enter number of blocks : ");
    scanf("%d", &m);
    printf("Enter number of processes : ");
    scanf("%d", &n);
    int blockSize[m], processSize[n];

    for (int i = 0; i < m; i++)
    {
        printf("Enter size of block %d : ", i + 1);
        scanf("%d", &blockSize[i]);
    }
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("Enter size of process %d : ", i + 1);
        scanf("%d", &processSize[i]);
    }
    nextFit(m, n, blockSize, processSize);
}



//Input : 5 4  &&  100 500 200 300 600  &&  212 417 112 426
//Input : 3 3  &&  5 10 20  &&  10 20 30
