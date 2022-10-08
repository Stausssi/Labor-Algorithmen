//
// Created by Simon on 12.05.2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXITEMS 5

typedef struct listCell {
    char *content;
    struct listCell *next;
} listCell, *listCell_p;

listCell_p insertFirst(listCell_p *anchor, listCell_p newCell);

listCell_p extractAt(listCell_p *anchor, unsigned int pos);
listCell_p getAt(listCell_p *anchor, unsigned int pos);

listCell_p extractFirst(listCell_p *anchor);
listCell_p getFirst(listCell_p *anchor);

listCell_p extractLast(listCell_p *anchor);
listCell_p getLast(listCell_p *anchor);

listCell_p allocCell(char *content);

listCell_p find(listCell_p *anchor, char *content);

listCell_p revert(listCell_p *anchor, unsigned int listLen);

void printContent(listCell_p *anchor, unsigned int listLen);

void freeCell(listCell_p cell);

void freeList(listCell_p *anchor);