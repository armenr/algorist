/*see README for original credits */

#include"random.h"
#include"sort.h"
#include<stdio.h>

static void randomizeArray(int s[]) {
    int i;
    for (i = 0; i < NELEM; i++)
        s[i] = NELEM - i;
    random_permutation(s, NELEM);
}

static void printArray(int s[]) {
    int i;
    for (i = 0; i < NELEM; i++)
        printf("%d ", s[i]);
}

int main(void) {
    int s[NELEM + 2], i;

    printf("Randomized array from 1 to %d: \n", NELEM);
    randomizeArray(s);
    printArray(s);
    insertion_sort(s, NELEM);
    printf("\n\nInsertion sort: \n");
    printArray(s);

    printf("\n\nRandomized array from 1 to %d: \n", NELEM);
    randomizeArray(s);
    printArray(s);
    selection_sort(s, NELEM);
    printf("\n\nSelection sort: \n");
    printArray(s);

    printf("\n\nRandomized array from 1 to %d: \n", NELEM);
    randomizeArray(s);
    printArray(s);
    quick_sort(s, 0, NELEM - 1);
    printf("\n\nQuick sort: \n");
    printArray(s);

    printf("\n\nRandomized array from 1 to %d: \n", NELEM);
    randomizeArray(s);
    printArray(s);
    heap_sort(s, NELEM);
    printf("\n\nHeap sort: \n");
    printArray(s);

    printf("\n\nRandomized array from 1 to %d: \n", NELEM);
    randomizeArray(s);
    printArray(s);
    merge_sort(s, 0, NELEM - 1);
    printf("\n\nMerge sort: \n");
    printArray(s);

    printf("\n\n");

    for (i = 0; i < NELEM; i++)
        s[i] = 2 * (NELEM - i);
    random_permutation(s, NELEM);

    heap_sort(s, NELEM);

    for (i = 0; i < 2 * NELEM + 1; i++)
        printf("%d found in %d\n", i, binary_search(s, i, 0, NELEM - 1));

    printf("\n");
    return 0;
}

/*
osman@osman-dev:~/src/ds$ ./sort-demo 
Randomized array from 1 to 8: 
6 2 3 7 8 5 4 1 

Insertion sort: 
1 2 3 4 5 6 7 8 

Randomized array from 1 to 8: 
8 3 1 5 6 2 7 4 

Selection sort: 
1 2 3 4 5 6 7 8 

Randomized array from 1 to 8: 
1 6 4 3 7 2 8 5 

Quick sort: 
1 2 3 4 5 6 7 8 

Randomized array from 1 to 8: 
1 7 2 4 6 5 3 8 

Heap sort: 
1 2 3 4 5 6 7 8 

Randomized array from 1 to 8: 
1 7 8 4 6 2 3 5 

Merge sort: 
1 2 3 4 5 6 7 8 

0 found in -1
1 found in -1
2 found in 0
3 found in -1
4 found in 1
5 found in -1
6 found in 2
7 found in -1
8 found in 3
9 found in -1
10 found in 4
11 found in -1
12 found in 5
13 found in -1
14 found in 6
15 found in -1
16 found in 7
 */
