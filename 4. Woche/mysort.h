//
// Created by Simon on 26.05.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listCell {
    char *content;
    struct listCell *next;
} listCell, *listCell_p;

listCell_p insertFirst(listCell_p *anchor, listCell_p newCell);

listCell_p getAt(listCell_p *anchor, unsigned int pos);

listCell_p allocCell(char *content);

listCell_p find(listCell_p *anchor, char *content);

void sort(listCell_p *anchor, unsigned int listLen);

void printContent(listCell_p *anchor);

void freeList(listCell_p *anchor);