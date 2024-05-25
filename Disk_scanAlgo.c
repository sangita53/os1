#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void SCAN(int requests[], int n, int head, int direction, int disk_size) {
    int seek_count = 0;
    int distance, cur_track;
    int size = n + 2;
    int sorted_requests[size];

    // Copy the request array to the new array
    for (int i = 0; i < n; i++) {
        sorted_requests[i] = requests[i];
    }

    // Add the head and end values based on direction
    sorted_requests[n] = head;
    sorted_requests[n + 1] = (direction == 1) ? disk_size - 1 : 0;

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

    // Process the requests based on the direction
    if (direction == 1) {
        // Move towards the end of the disk
        for (int i = pos; i < size; i++) {
            cur_track = sorted_requests[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            printf("%d ", cur_track);
        }
        // Move towards the start of the disk
        for (int i = pos - 1; i >= 0; i--) {
            cur_track = sorted_requests[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            printf("%d ", cur_track);
        }
    } else {
        // Move towards the start of the disk
        for (int i = pos; i >= 0; i--) {
            cur_track = sorted_requests[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            printf("%d ", cur_track);
        }
        // Move towards the end of the disk
        for (int i = pos + 1; i < size; i++) {
            cur_track = sorted_requests[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            printf("%d ", cur_track);
        }
    }

    printf("\nTotal number of seek operations = %d\n", seek_count);
}

int main() {
    int n, head, direction, disk_size;

    // Get the number of requests
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requests[n];

    // Get the requests
    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    // Get the initial head position
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    // Get the direction
    printf("Enter the direction (1 for high, 0 for low): ");
    scanf("%d", &direction);

    disk_size = 200;

    // Call the SCAN function
    SCAN(requests, n, head, direction, disk_size);

    return 0;
}
//8
// Request sequence = {176, 79, 34, 60, 92, 11, 41, 114}
// Initial head position = 50
// Direction = left (We are moving from right to left)