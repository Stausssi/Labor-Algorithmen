//
// Created by Simon on 26.05.2020.
//

#include "mystat.h"

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

//    if (in == stdin)
//        fprintf(stdout, "Enter your elements. End with '\\n' or 'quit'!\n");
//    else
//        fprintf(stdout, "Reading from file '%s'!\n", argv[1]);

    listCell_p anchor = malloc(sizeof(listCell));
    anchor->next = NULL;

    listCell_p *anchAdr = &anchor;
    unsigned int listLen = 0;

    // Get the user input
    char *input = malloc(255 * sizeof(char));

    while (fgets(input, 255, in) != NULL && strcmp(input, "\n") != 0 && strcmp(input, "quit\n") != 0) {
        // Check for duplicates
        listCell_p duplicate = find(anchAdr, input);
        if (duplicate == NULL) {
            anchor = insertFirst(anchAdr, allocCell(input));
//            fprintf(stdout, "Successfully added element!\n");
            listLen++;
        } else {
//            fprintf(stdout, "The String you entered already exists!\n");
            duplicate->duplicates++;
        }
    }

    // Close the input stream if it's not stdin
    if (in != stdin) {
        fclose(in);
    }

    if (anchor->next != NULL) {
        // Print
        fprintf(stdout, "\nOutput:\n");
        printContent(anchAdr);
    }

    // Free Memory
    freeList(anchAdr);

    exit(EXIT_SUCCESS);
}

listCell_p allocCell(char *content) {
    listCell_p temp = malloc(sizeof(listCell));
    temp->content = strdup(content);
    temp->duplicates = 1;
    temp->next = NULL;
    return temp;
}

listCell_p insertFirst(listCell_p *anchor, listCell_p newCell) {
    newCell->next = (*anchor)->next;
    (*anchor)->next = newCell;
    return *anchor;
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

void printContent(listCell_p *anchor) {
    listCell_p current = *anchor;

    while (current->next != NULL) {
        current = current->next;
        fprintf(stdout, "%d mal: %s", current->duplicates, current->content);
    }
}

void freeList(listCell_p *anchor) {
    free(*anchor);
}
