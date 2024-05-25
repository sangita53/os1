#include <stdio.h>

void worstFit(int m, int n, int blockSize[], int processSize[])
{
    int allocated[n];
    for (int i = 0; i < n; i++)
    {
        allocated[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int worstIndex = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (worstIndex == -1)
                {
                    worstIndex = j;
                }
                else if (blockSize[worstIndex] < blockSize[j])
                {
                    worstIndex = j;
                }
            }
        }

        if (worstIndex != -1)
        {
            allocated[i] = worstIndex;
            blockSize[worstIndex] -= processSize[i];
        }
    }

    printf("\nProcess No. \tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t", i + 1);
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
    worstFit(m, n, blockSize, processSize);
}



//Input :  5 4  &&  100 500 200 300 600  &&  212 417 112 426
