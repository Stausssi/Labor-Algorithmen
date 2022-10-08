//
// Created by Simon on 16.06.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITEMS 100000

long long getUSecClock() {
    clock_t cpuTime = clock();
    return (long long) cpuTime * 1000000 / CLOCKS_PER_SEC;
}

void selectionSort(int *toSort, int length) {
    for (int i = 0; i < length - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < length; ++j) {
            if (toSort[j] < toSort[minIndex])
                minIndex = j;
        }

        int tmp = toSort[minIndex];
        toSort[minIndex] = toSort[i];
        toSort[i] = tmp;
    }
}

void printArray(int *array, int start, int end) {
    fprintf(stdout, "[");
    for (int i = start; i < end; ++i) {
        fprintf(stdout, "%d", array[i]);
        if (end - i > 1)
            fprintf(stdout, ", ");
    }
    fprintf(stdout, "]");
}

int *mergeSort(int *toSort, int start, int end) {
    int lenA1, lenA2, length;
    length = end - start;

    if (length <= 1)
        return toSort;

    // Split the array into two portions of (almost) the same size
    lenA1 = length / 2;
    lenA2 = length / 2;

    if (length % 2 != 0)
        lenA1++;

    // Fill these arrays
    int *arr1 = malloc(lenA1 * sizeof(int));
    for (int i = 0; i < lenA1; i++)
        arr1[i] = toSort[i];

    int *arr2 = malloc(lenA2 * sizeof(int));
    for (int i = 0; i < lenA2; i++)
        arr2[i] = toSort[lenA1 + i];

    // Split the array until there is a single entry left
    arr1 = mergeSort(arr1, start, start + lenA1);
    arr2 = mergeSort(arr2, start + lenA1, start + lenA1 + lenA2);

    // Merge the arrays
    int e1 = 0, e2 = 0;
    for (int i = 0; i < length; i++) {
        if (e1 >= lenA1)
            toSort[i] = arr2[e2++];
        else if (e2 >= lenA2)
            toSort[i] = arr1[e1++];
        else if (arr1[e1] <= arr2[e2])
            toSort[i] = arr1[e1++];
        else
            toSort[i] = arr2[e2++];
    }

    return toSort;
}

void merge(int *toSort, int *temp, int from, int partSize, int length) {
    int mid = from + partSize - 1;

    // Upper border could also be length if the length isn't dividable by 2,
    // therefore the last array is smaller than expected
    int to = from + 2 * partSize - 1 < length ? from + 2 * partSize - 1 : length;

    int k = from, i = from, j = mid + 1;

    // loop till there are elements in the left and right runs
    while (i <= mid && j <= to) {
        if (toSort[i] < toSort[j])
            temp[k++] = toSort[i++];
        else
            temp[k++] = toSort[j++];
    }

    // Copy remaining elements
    while (i < length && i <= mid)
        temp[k++] = toSort[i++];

    // Don't need to copy second half

    // copy back to the original array to reflect sorted order
    for (i = from; i <= to; i++)
        toSort[i] = temp[i];
}

void bottomUpMergeSort(int *toSort, int length) {
    int* temp = malloc(MAX_ITEMS * sizeof(int));
    memcpy(temp, toSort, MAX_ITEMS * sizeof(int));

    for (int partSize = 1; partSize < length; partSize *= 2) {
        for (int i = 0; i < length; i += 2 * partSize)
            // Merge arrays with the size of partSize
            merge(toSort, temp, i, partSize, length);
    }
}

int q_part(int *toSort, int start, int end) {
    int pivotI = (start + end) / 2;
    int pivotV = toSort[pivotI];
    int temp;

    temp = toSort[end];
    toSort[end] = pivotV;
    toSort[pivotI] = temp;

    int sp = start;
    for (int i = start; i < end; ++i) {
        if (toSort[i] < pivotV) {
            temp = toSort[sp];
            toSort[sp] = toSort[i];
            toSort[i] = temp;

            sp++;
        }
    }

    temp = toSort[sp];
    toSort[sp] = toSort[end];
    toSort[end] = temp;
    return sp;
}

int *quickSort(int *toSort, int start, int end) {
    if (start < end) {
        int pivot = q_part(toSort, start, end);
        toSort = quickSort(toSort, start, pivot - 1);
        toSort = quickSort(toSort, pivot + 1, end);
    }

    return toSort;
}

void bubbleDown(int *heap, int node, int end) {
    int I_leftChild = 2 * node + 1;

    if (I_leftChild < end) {
        int I_greatestChild = I_leftChild;
        int I_rightChild = I_leftChild + 1;

        if (I_rightChild < end) {
            if (heap[I_rightChild] > heap[I_leftChild])
                I_greatestChild = I_rightChild;
        }

        if (heap[I_greatestChild] > heap[node]) {
            int temp = heap[node];
            heap[node] = heap[I_greatestChild];
            heap[I_greatestChild] = temp;

            bubbleDown(heap, I_greatestChild, end);
        }
    }
}

void heapify(int *heap, int end) {
    int last = (end - 1) / 2;

    for (int i = last; i > -1; --i) {
        bubbleDown(heap, i, end);
    }
}

void heapSort(int *toSort, int length) {
    int last = length - 1;
    heapify(toSort, length);

    for (int i = last; i > 0; --i) {
        int temp = toSort[0];
        toSort[0] = toSort[i];
        toSort[i] = temp;
        bubbleDown(toSort, 0, i);
    }
}

int main(int argc, char *argv[]) {
    FILE *in = stdin;
    char output = 'c';
    char alg = 's';

    if (argc > 4) {
        fprintf(stderr, "Usage:_%s_[<file>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc >= 2) {
        in = fopen(argv[1], "r");
        if (!in) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }

        if (argc >= 3)
            alg = argv[2][0];

        if (argc == 4)
            output = argv[3][0];

    }

    int *toSort = malloc(MAX_ITEMS * sizeof(int));
    int i = 0;
    char input[255];

    while (fgets(input, 255, in) && i < MAX_ITEMS)
        toSort[i++] = atoi(input);

    char *algName = malloc(10 * sizeof(char));
    switch (alg) {
        case 's':
            strcpy(algName, "Selection");
            break;
        case 'm':
            strcpy(algName, "Merge");
            break;
        case 'b':
            strcpy(algName, "BottomUpMerge");
            break;
        case 'q':
            strcpy(algName, "Quick");
            break;
        case 'h':
            strcpy(algName, "Heap");
            break;
        default:
            break;
    }

    // Change output to complete ('c') if there are less than 11 items in the array
    if (i <= 10 && output == 'b')
        output = 'c';

    long long t1, t2;
    t1 = getUSecClock();

    if (alg == 's')
        selectionSort(toSort, i);
    else if (alg == 'm')
        toSort = mergeSort(toSort, 0, i);
    else if (alg == 'b')
        bottomUpMergeSort(toSort, i - 1);
    else if (alg == 'q')
        toSort = quickSort(toSort, 0, i - 1);
    else if (alg == 'h')
        heapSort(toSort, i);
    else
        return EXIT_FAILURE;

    t2 = getUSecClock();

    if (output == 'c')
        //Print entire list
        printArray(toSort, 0, i);
    else if (output == 'b') {
        // Print border items
        printArray(toSort, 0, 5);

        fprintf(stdout, " ... ");

        printArray(toSort, i - 5, i);
    }

    fprintf(stdout, "\nSorting %d elements with %sSort took %lld usec!\n", i, algName, t2 - t1);

    while (!getchar());

    if (in != stdin) {
        fclose(in);
    }

    exit(EXIT_SUCCESS);
}