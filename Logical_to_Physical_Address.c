// // using segmentation
// // input : 3 && 100 50 && 200 100 && 300 150 && 2 && 20
// // input : 3 && 100 150 && 250 300 && 350 400 && 2 && 20

// #include <stdio.h>

// struct segmentTable {
//     int base;
//     int limit;
// };

// int segmentationTranslation(struct segmentTable segTable[], int totalSegments, int seg, int offset) {
//     if (seg < 0 || seg >= totalSegments) {
//         printf("Invalid segment number.\n");
//         return -1;
//     }

//     if (offset < 0 || offset >= segTable[seg].limit) {
//         printf("Offset exceeds segment limit.\n");
//         return -1;
//     }

//     return segTable[seg].base + offset; // returning physical address
// }

// void main() {
//     int n;
//     printf("Enter number of segments : ");
//     scanf("%d", &n);
//     struct segmentTable segmentTable[n];
//     printf("\n");
//     for (int i = 0; i < n; i++) {
//         int b, l;
//         printf("Enter base of segment %d : ", i + 1);
//         scanf("%d", &b);
//         printf("Enter limit of segment %d : ", i + 1);
//         scanf("%d", &l);
//         segmentTable[i].base = b;
//         segmentTable[i].limit = l;
//     }

//     int seg, offset;
//     printf("\nEnter segment : ");
//     scanf("%d", &seg);
//     printf("Enter offset : ");
//     scanf("%d", &offset);

//     // Adjust for 1-based segment input to 0-based array index
//     seg -= 1;

//     int physicallAddress = segmentationTranslation(segmentTable, n, seg, offset);
//     if (physicallAddress != -1) {
//         printf("\nPhysical Address : %d", physicallAddress);
//     }
// }


// using paging
// input : 3 && 5 9 7 && 1 && 200
// input : 4 && 2 5 8 3 && 2 && 1024

#include <stdio.h>
struct pageTable
{
    int frame;
};

int pagingTranslation(struct pageTable pageTable[], int totalPages, int page, int offset)
{

    if (page < 0 || page >= totalPages)
    {
        printf("Invalid page number.\n");
        return -1;
    }

    if (offset < 0 || offset >= 4096) // each frame is 4KB (2^12 bytes) i.e 4096
    {
        printf("Offset exceeds page size.\n");
        return -1;
    }

    return ((pageTable[page].frame * 4096) + offset); // returning physical address
}

void main()
{
    int n;
    printf("Enter number of pages : ");
    scanf("%d", &n);
    struct pageTable pageTable[n];
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        int f;
        printf("Enter frame : ");
        scanf("%d", &f);
        pageTable[i].frame = f;
    }

    int page, offset;
    printf("\nEnter page : ");
    scanf("%d", &page);
    printf("Enter offset : ");
    scanf("%d", &offset);

    int physicallAddress = pagingTranslation(pageTable, n, page, offset);
    if (physicallAddress != -1)
    {
        printf("\nPhysical Address : %d", physicallAddress);
    }
}
