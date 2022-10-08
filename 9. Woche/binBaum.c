/*-----------------------------------------------------------------------

  File  : bst.c

Author: Stephan Schulz (schulz@eprover.org)

Contents

  Program that builds and tests binary search trees.

  Copyright 2015-2018 by the author.

  This code is released under the GNU General Public Licence, version
  2, or, at your choice, any later version. See the file COPYING.

Changes

<1> Mon Jun 22 20:43:15 CEST 2015
    New

-----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>

#define MAXLINE  256

/* Binary tree cell */

typedef struct bintreecell {
    long key;
    char *payload;
    struct bintreecell *lchild;
    struct bintreecell *rchild;
} BinTree, *BinTree_p;


/*-----------------------------------------------------------------------
//
// Function: xmalloc()
//
//   Thin wrapper around malloc() - fail noisily (with error message)
//   if no memory is available.
//
// Global Variables: -
//
// Side Effects    : Only via malloc() or in case of error
//
/----------------------------------------------------------------------*/

void *xmalloc(size_t size) {
    void *mem = malloc(size);
    if (!mem) {
        fprintf(stderr, "lin_list: Out of memory\n");
        exit(EXIT_FAILURE);
    }
    return mem;
}

/*-----------------------------------------------------------------------
//
// Function: xstrdup()
//
//   Thin wrapper around strdup() - fail noisily (with error message)
//   if no memory is available.
//
// Global Variables: -
//
// Side Effects    : Only via malloc() or in case of error
//
/----------------------------------------------------------------------*/

char *xstrdup(char *str) {
    void *newstr = strdup(str);
    if (!newstr) {
        fprintf(stderr, "lin_list: Out of memory\n");
        exit(EXIT_FAILURE);
    }
    return newstr;
}

BinTree_p initTree(long key, char *value) {
    BinTree_p tree = xmalloc(sizeof(BinTree));

    tree->key = key;
    tree->payload = xstrdup(value);
    tree->rchild = NULL;
    tree->lchild = NULL;

    return tree;
}

BinTree_p insert(BinTree_p tree, long key, char *value) {
    if (tree) {
        if (key > tree->key)
            tree->rchild = insert(tree->rchild, key, value);
        else if (key < tree->key)
            tree->lchild = insert(tree->lchild, key, value);
        else
            return NULL;
        return tree;
    } else
        return initTree(key, value);
}

BinTree_p find(BinTree_p tree, long key) {
    if (tree) {
        if (key > tree->key)
            return find(tree->rchild, key);
        if (key < tree->key)
            return find(tree->lchild, key);

        return tree;
    } else
        return NULL;
}

void print_tree(BinTree_p tree) {
    if(tree->lchild)
        print_tree(tree->lchild);

    printf("(%ld, %s)\n", tree->key, tree->payload);

    if (tree->rchild)
        print_tree(tree->rchild);
}

/*-----------------------------------------------------------------------
//
// Function: main()
//
//    Read a file of insert/delete/find/print_tree instructions for a
//    binary search tree, and "execute" them (well, execute the
//    comments that tell you where to put your code).
//
// Global Variables: -
//
// Side Effects    : Reads input, prints output
//
/----------------------------------------------------------------------*/

int main(int argc, char *argv[]) {
    FILE *in = stdin;
    char line[MAXLINE];
    char *inp;
    int key;
    char *valPtr;
    BinTree_p tree;

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [<file>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (argc == 2) {
        in = fopen(argv[1], "r");
        if (!in) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    tree = NULL;

    while ((inp = fgets(line, MAXLINE, in))) {
        if (strncmp(line, "I:", 2) == 0) {
            key = atoi(&line[2]);
            valPtr = strchr(line, '\n');
            if (valPtr) {
                *valPtr = '\0';
            }
            valPtr = strchr(line, ',');
            if (valPtr) {
                valPtr++;
                printf("Inserting (%d, %s) into the tree\n", key, valPtr);

                tree = insert(tree, key, valPtr);
//                if (tree == NULL) {
//                    tree = initTree(key, valPtr);
//                } else {
//                    BinTree_p current = tree;
//                    while (1) {
//                        if (key > current->key) {
//                            if (current->rchild == NULL) {
//                                current->rchild = initTree(key, valPtr);
//                                break;
//                            } else
//                                current = current->rchild;
//                        } else if (key < current->key) {
//                            if (current->lchild == NULL) {
//                                current->lchild = initTree(key, valPtr);
//                                break;
//                            } else
//                                current = current->lchild;
//                        }
//                    }
//                }
//                if (tree)
//                    printf("Inserted!\n");
//                else
//                    printf("Error!\n");
            }
        } else if (strncmp(line, "F:", 2) == 0) {
            key = atoi(&line[2]);
            printf("Searching key %d in the tree\n", key);
            BinTree_p result = find(tree, key);
            if (result)
                printf("Found (%ld, %s)\n", result->key, result->payload);
            else
                printf("Not found!\n");
        } else if (strncmp(line, "D:", 2) == 0) {
            key = atoi(&line[2]);
            printf("Remove record with key %d from the tree\n", key);
            /* Put delete code here ! */
        } else if (strncmp(line, "P:", 2) == 0) {
            printf("Print the full tree\n");
            /* Put Print code here ! */
            if (tree) {
                print_tree(tree);
            }
        }
    }

    if (in != stdin) {
        fclose(in);
    }

    exit(EXIT_SUCCESS);
}

/*---------------------------------------------------------------------*/
/*                        End of File                                  */
/*---------------------------------------------------------------------*/