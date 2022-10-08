//
// Created by Simon on 26.05.2020.
//

#include "mysort.h"

int main(int argc, char *argv[]) {
    FILE *in = stdin;

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

    // Close the input stream if it's not stdin
    if (in != stdin) {
        fclose(in);
    }

    // Sort the list
    sort(anchAdr, listLen);

    // Print
    fprintf(stdout, "\nSorted List:\n");
    printContent(anchAdr);

    // Free Memory
    freeList(anchAdr);

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

listCell_p getAt(listCell_p *anchor, unsigned int pos) {
    listCell_p current = (*anchor)->next;
    for (int i = 0; i < pos; ++i) {
        if (current->next != NULL)
            current = current->next;
        else if (i < pos - 1)
            return NULL;
    }

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

void sort(listCell_p *anchor, unsigned int listLen) {
    for (int i = 0; i < listLen; ++i) {
        for (int j = i + 1; j < listLen; ++j) {
            listCell_p el1, el2;
            el1 = getAt(anchor, i);
            el2 = getAt(anchor, j);

            if (strcmp(el1->content, el2->content) > 0) {
                char *tempContent = malloc(sizeof(char) * 255);
                strcpy(tempContent, el1->content);
                strcpy(el1->content, el2->content);
                strcpy(el2->content, tempContent);

                free(tempContent);
            }
        }
    }
}

void printContent(listCell_p *anchor) {
    listCell_p current = *anchor;

    while(current->next != NULL) {
        current = current->next;
        fprintf(stdout, "%s", current->content);
    }
}

void freeList(listCell_p *anchor) {
    free(*anchor);
}