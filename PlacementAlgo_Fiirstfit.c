#include <stdio.h>
void firstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocated[n];

    for (int i = 0; i < n; i++)
    {
        allocated[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                allocated[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
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
    printf("\nEnter number of blocks : ");
    scanf("%d", &m);
    printf("Enter number of processes : \n");
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

    firstFit(blockSize, m, processSize, n);
    
}




//Input : 5 4  &&  100 500 200 300 600  &&  212 417 112 426