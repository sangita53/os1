#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10

typedef struct {
    int page;
    int reference;
} Frame;

void printFrames(Frame frames[], int numFrames) {
    printf("Frames: ");
    for (int i = 0; i < numFrames; i++) {
        if (frames[i].page != -1) {
            printf("%d ", frames[i].page);
        } else {
            printf("- ");
        }
    }
    printf("\n");
}

int findPage(Frame frames[], int numFrames, int page) {
    for (int i = 0; i < numFrames; i++) {
        if (frames[i].page == page) {
            return i;
        }
    }
    return -1;
}

void secondChance(int pages[], int numPages, int numFrames) {
    Frame frames[MAX_FRAMES];
    for (int i = 0; i < numFrames; i++) {
        frames[i].page = -1;
        frames[i].reference = 0;
    }

    int pointer = 0;
    int pageFaults = 0;

    for (int i = 0; i < numPages; i++) {
        int page = pages[i];
        int pageIndex = findPage(frames, numFrames, page);

        if (pageIndex != -1) {
            // Page is already in the frames, give it a second chance
            frames[pageIndex].reference = 1;
        } else {
            // Page fault occurs
            while (frames[pointer].reference == 1) {
                frames[pointer].reference = 0;
                pointer = (pointer + 1) % numFrames;
            }

            frames[pointer].page = page;
            frames[pointer].reference = 1;
            pointer = (pointer + 1) % numFrames;
            pageFaults++;
        }

        printFrames(frames, numFrames);
    }

    printf("Total page faults: %d\n", pageFaults);
}

int main() {
    int pages[] = {1, 2, 3, 2, 1, 4, 5, 1, 2, 3, 4, 5};
    int numPages = sizeof(pages) / sizeof(pages[0]);
    int numFrames = 3;

    printf("Second Chance Page Replacement Algorithm\n");
    secondChance(pages, numPages, numFrames);

    return 0;
}
