#include <stdio.h>

void optimal(int numOfFrames, int numOfPages, int pages[])
{
    int position;
    int frame[numOfFrames];
    for (int i = 0; i < numOfFrames; i++)
    {
        frame[i] = -1;
    }

    int hit = 0, miss = 0;

    // Print the header of the table
    printf("Page ");
    for (int i = 0; i < numOfFrames; i++)
    {
        printf("Frame%d ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < numOfPages; i++)
    {
        int flag1 = 0, flag2 = 0;
        for (int j = 0; j < numOfFrames; j++)
        {
            if (frame[j] == pages[i])
            {
                flag1 = flag2 = 1;
                hit++;
                break;
            }
        }
        if (flag1 == 0)
        {
            for (int j = 0; j < numOfFrames; j++)
            {
                if (frame[j] == -1)
                {
                    miss++;
                    frame[j] = pages[i];
                    flag2 = 1;
                    break;
                }
            }
        }
        if (flag2 == 0)
        {
            int flag3 = 0;
            int temp[numOfFrames];
            for (int j = 0; j < numOfFrames; j++)
            {
                temp[j] = -1;
                for (int k = i + 1; k < numOfPages; k++)
                {
                    if (frame[j] == pages[k])
                    {
                        temp[j] = k;
                        break;
                    }
                }
            }
            for (int j = 0; j < numOfFrames; j++)
            {
                if (temp[j] == -1)
                {
                    position = j;
                    flag3 = 1;
                    break;
                }
            }

            if (flag3 == 0)
            {
                int max = temp[0];
                position = 0;
                for (int j = 1; j < numOfFrames; j++)
                {
                    if (temp[j] > max)
                    {
                        max = temp[j];
                        position = j;
                    }
                }
            }
            frame[position] = pages[i];
            miss++;
        }
        printf("%6d ", pages[i]);
        for (int j = 0; j < numOfFrames; j++)
        {
            if (frame[j] == -1)
                printf("%6s ", "-");
            else
                printf("%6d ", frame[j]);
        }
        printf("\n");
    }
    printf("\nPage hits: %d", hit);
    printf("\nPage misses: %d", miss);
}

int main()
{
    int p, f;
    printf("\nEnter number of frames: ");
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
    optimal(f, p, pages);
    return 0;
}


//input : 4 13  &&  7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2