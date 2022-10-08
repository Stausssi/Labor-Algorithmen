//
// Created by Simon on 12.05.2020.
//

#include "list.h"

int main(int argc, char *argv[]) {
    FILE *in = stdin;
    int inputCount = MAXITEMS;

    if (argc > 2) {
        fprintf(stderr, "Usage:_%s_[<file>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 2) {
        in = fopen(argv[1], "r");
        if (!in) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (in == stdin)
        fprintf(stdout, "Enter your elements. End with '\\n' or 'quit'!\n");
    else
        fprintf(stdout, "Reading from file '%s'!\n", argv[1]);

    listCell_p anchor = malloc(sizeof(listCell));
    anchor->next = NULL;

    listCell_p *anchAdr = &anchor;
    unsigned int listLen = 0;

    // Get the user input
    char *input = malloc(255 * sizeof(char));

    while (fgets(input, 255, in) && strcmp(input, "\n") != 0 && strcmp(input, "quit\n") != 0) {
        // Check for duplicates
        if (find(anchAdr, input) == NULL) {
            anchor = insertFirst(anchAdr, allocCell(input));
            fprintf(stdout, "Successfully added element!\n");
            listLen++;
        } else
            fprintf(stdout, "The String you entered already exists!\n");
    }

    if (in != stdin) {
        fclose(in);
    }

    // Print reverse
//    fprintf(stdout, "List in reverse order:\n");
//    listCell_p current;
//    while (current->next != NULL) {
//        fprintf(stdout, "%s", current->next->content);
//        current = current->next;
//    }

    // Print normal
    fprintf(stdout, "\n\nList in normal order:\n");
    printContent(anchAdr, listLen);

    fprintf(stdout, "\n");
    fprintf(stdout, "Content of the first Element is: %s\n", extractFirst(anchAdr)->content);
    fprintf(stdout, "Content of the last Element is: %s\n", extractLast(anchAdr)->content);

    fprintf(stdout, "\n");
    fprintf(stdout, "The reverted List is:\n");
    listCell_p oldAnchor = anchor;

    anchor = revert(anchAdr, listLen);
    anchAdr = &anchor;
    printContent(anchAdr, listLen);

    // Free Memory
    freeList(anchAdr);
    freeList(&oldAnchor);

    exit(EXIT_SUCCESS);
}

listCell_p allocCell(char *content) {
    listCell_p temp = malloc(sizeof(listCell));
    temp->content = strdup(content);
    temp->next = NULL;
    return temp;
}

listCell_p insertFirst(listCell_p *anchor, listCell_p newCell) {
    newCell->next = (*anchor)->next;
    (*anchor)->next = newCell;
    return *anchor;
}

listCell_p extractAt(listCell_p *anchor, unsigned int pos) {
    return allocCell(getAt(anchor, pos)->content);
}

listCell_p getAt(listCell_p *anchor, unsigned int pos) {
    listCell_p current = (*anchor)->next;
    for (int i = 0; i < pos; ++i) {
        if(current->next != NULL)
            current = current->next;
        else if (i < pos - 1)
            return NULL;
    }

    return current;
}

listCell_p extractFirst(listCell_p *anchor) {
    return extractAt(anchor, 0);
}

listCell_p getFirst(listCell_p *anchor) {
    return getAt(anchor, 0);
}

listCell_p extractLast(listCell_p *anchor) {
    return allocCell(getLast(anchor)->content);
}

listCell_p getLast(listCell_p *anchor) {
    listCell_p current = *anchor;
    while (current->next != NULL)
        current = current->next;

    return current;
}

listCell_p find(listCell_p *anchor, char *content) {
    listCell_p current = *anchor;
    while (current->next != NULL) {
        current = current->next;
        if (strcmp(content, current->content) == 0)
            return current;
    }

    return NULL;
}

listCell_p revert(listCell_p *anchor, unsigned int listLen) {
    listCell_p newAnchor = malloc(sizeof(listCell));
    unsigned int pos = 0;
    while (pos < listLen)
        // Grab the current element and add it to a new list
        newAnchor = insertFirst(&newAnchor, extractAt(anchor, pos++));

    return newAnchor;
}

void printContent(listCell_p *anchor, unsigned int listLen) {
    listCell_p current;

    for (int i = 0; i < listLen; i++) {
        current = *anchor;
        for (int j = 0; j < listLen - i; j++) {
            current = current->next;
        }
        fprintf(stdout, "%s\n", current->content);
    }
}

void freeCell(listCell_p cell) {
    free(cell->content);
    free(cell);
}

void freeList(listCell_p *anchor) {
    listCell_p tmp = *anchor;
    while (tmp->next != NULL) {
        freeCell(tmp);
        tmp = tmp->next;
    }
    freeCell(tmp);
    freeCell(*anchor);
}