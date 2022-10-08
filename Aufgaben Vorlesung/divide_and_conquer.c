//
// Created by Simon on 02.06.2020.
//
#include <stdio.h>
#include <stdlib.h>

#define ITEMS 10

int divide_and_conquer(int findMe, int *array, int lower, int upper) {
    int index = upper < lower ? -1 : (upper + lower) / 2;

    if (index == -1 || array[index] == findMe)
        return index;
    else if (array[index] < findMe)
        return divide_and_conquer(findMe, array, index + 1, upper);
    else
        return divide_and_conquer(findMe, array, lower, index - 1);
}

int main(int argc, char *argv[]) {
    int array[] = {1, 4, 7, 10, 21, 50, 65, 80, 99, 101};
    int find = 50;
    fprintf(stdout, "The number %d can be found at index %d!", find, divide_and_conquer(find, array, 0, ITEMS - 1));
}
