#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, done = 0, headPosition;
    float tso = 0;
    printf("Enter number of requests : ");
    scanf("%d", &n);
    printf("Enter head position : ");
    scanf("%d", &headPosition);
    int requests[n];
    printf("\nEnter request sequence \n");
    for (int i = 0; i < n; i++) {
        printf("Enter request %d : ", i);
        scanf("%d", &requests[i]);
    }
    
    printf("\nSeek sequence : ");
    int initialHeadPosition = headPosition;
    for (int i = 0; i < n; i++) {
        tso = tso + abs(headPosition - requests[i]);
        headPosition = requests[i];
        done++;

        if (done == n) {
            printf("%d\n", requests[i]);
        } else {
            printf("%d -> ", requests[i]);
        }
    }
    
    printf("\nTotal Seek operations/count : %.2f\n", tso);
    printf("Average Seek Length : %.2f\n", tso / n);

    // // Print the sequence of head movements
    // printf("Sequence of head movements:\n");
    // headPosition = initialHeadPosition; // reset the initial head position
    // for (int i = 0; i < n; i++) {
    //     printf("Move from %d to %d\n", headPosition, requests[i]);
    //     headPosition = requests[i];
    // }

    return 0;
}


// Input : 8  &&  50  &&  176, 79, 34, 60, 92, 11, 41, 114