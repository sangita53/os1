#include <stdio.h>

void fifo(int numOfFrames, int numOfPages, int pages[])
{
    int frame[numOfFrames];
    for (int i = 0; i < numOfFrames; i++)
    {
        frame[i] = -1;
    }

    int hit = 0, miss = 0, index = -1;
    
    // Print the header of the table
    printf("Page ");
    for (int i = 0; i < numOfFrames; i++)
    {
        printf("Frame%d ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < numOfPages; i++)
    {
        int flag = 0;
        for (int j = 0; j < numOfFrames; j++)
        {
            if (frame[j] == pages[i])
            {
                flag = 1;
                break;
            }
        }

        if (flag)
        {
            printf("%6d ", pages[i]);
            for (int k = 0; k < numOfFrames; k++)
            {
                if (frame[k] == -1)
                    printf("%6s ", "-");
                else
                    printf("%6d ", frame[k]);
            }
            hit++;
        } 
        else
        {
            index = (index + 1) % numOfFrames;
            frame[index] = pages[i];
            miss++;
            printf("%6d ", pages[i]);
            for (int k = 0; k < numOfFrames; k++)
            {
                if (frame[k] == -1)
                    printf("%6s ", "-");
                else
                    printf("%6d ", frame[k]);
            }
        }
        printf("\n");
    }
    printf("\nPage hits: %d", hit);
    printf("\nPage misses: %d", miss);
}

int main()
{
    int p, f;
    printf("Enter number of frames: \n");
    scanf("%d", &f);
    printf("Enter number of pages: ");
    scanf("%d", &p);

    int pages[p];
    for (int i = 0; i < p; i++)
    {
        printf("Enter page: ");
        scanf("%d", &pages[i]);
    }
    printf("\n");
    fifo(f, p, pages);
}



//input : 3 5  &&  4 1 2 4 5  