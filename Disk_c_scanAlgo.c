#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void CSCAN(int requests[], int n, int head, int disk_size) {
    int seek_count = 0;
    int distance, cur_track;
    int size = n + 3; // Including head, end of disk, and start of disk (0)
    int sorted_requests[size];

    // Copy the request array to the new array
    for (int i = 0; i < n; i++) {
        sorted_requests[i] = requests[i];
    }

    // Add the head, end, and start values based on CSCAN
    sorted_requests[n] = head;
    sorted_requests[n + 1] = disk_size - 1; // End of the disk
    sorted_requests[n + 2] = 0; // Start of the disk

    // Sort the array
    qsort(sorted_requests, size, sizeof(int), compare);

    // Find the position of the head in the sorted array
    int pos;
    for (int i = 0; i < size; i++) {
        if (sorted_requests[i] == head) {
            pos = i;
            break;
        }
    }

    printf("Seek Sequence is:\n");

    // Process the requests from head to end of the disk
    for (int i = pos; i < size; i++) {
        cur_track = sorted_requests[i];
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
        printf("%d ", cur_track);
    }

    // Jump to the start of the disk and move to the position before the initial head
    // Since it is circular, we simulate the jump
    head = 0;
    seek_count += disk_size - 1; // Moving from end to start of the disk

    for (int i = 0; i < pos; i++) {
        cur_track = sorted_requests[i];
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
        printf("%d ", cur_track);
    }

    printf("\nTotal number of seek operations = %d\n", seek_count);
}

int main() {
    int n, disk_size, head;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    int requests[n];
    printf("Enter the request sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }



    disk_size = 200;

    CSCAN(requests, n, head, disk_size);

    return 0;
}
// Request sequence = {176, 79, 34, 60, 92, 11, 41, 114}
// Initial head position = 50
// Direction = right(We are moving from left to right)
