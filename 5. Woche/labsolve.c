//
// Created by Simon on 02.06.2020.
//

/*
Hier die Aufgabe!
1) Labyrinth einlesen
2) Checken
3) Ausgabe
Warum das in der Reihenfolge? Das hilft beim Debuggen!
Ohne Ausgabe ist Debuggen lästig, da muss man zu viel raten.
4) Lösen des Labyrints.
Einfachster Algorithmus: Suche mit Backtracken. Versuche von Startfeld alle Nachbarn, und von da rekursiv weiter.
Schon betretene Felder kann man markieren, um doppel-Betretungen zu verhindern (z.B. in dem man den "Brotkrümel" reinschreint).
Tote Wege kann man beim Backtracken markieren (z.B. mit !), dann kann man die Suche besser nachvervolgen.
...nachverfolgen... ;-)
Wer was anspruchsvolleres will: Google nach "Dijkstra shortest path" oder im Skript ans Ende gehen ;-)

 Wenn Sie wollen: Ich habe eine Datenstruktur zu verschenken:
"costs" brauchen Sie nur, wenn sie den kürzesten Weg finden wollen (statt nur irgendeinen - kürzester Weg mit Terrain ist dann Aufgabe 6 nächst Woche)
Was ist drin:
- Das Labyrinth als 2-D-Array von char
- Die Kosten (wie teuer war es, zu diesem Feld zu kommen), wenn gewünscht
- Wie viele Zeilen hat das konkrete Labyrinth (wenn man immer 256 ausgibt, scrollt das spannende vom Bildschirm)
- Wo ist der Start und wo ist das Ziel
Beispiellauf:
..anderer Fall:
..das Programm hat eine Verzögerung, damit man was sieht ;-)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

#define MAX_COLS  256
#define MAX_ROWS  256


/* Data type: Labyrinth - ASCII map, costs, direction */

typedef struct labyrinth {
    char lab[MAX_COLS + 2][MAX_ROWS];
    long costs[MAX_COLS][MAX_ROWS];
//    long bestX[MAX_COLS][MAX_ROWS];
//    long bestY[MAX_COLS][MAX_ROWS];
    int maxRow;
    int startX;
    int startY;
    int treasureX;
    int treasureY;
} LabCell, *LabCell_p;

LabCell_p labRead(FILE *in) {
    LabCell_p lab = malloc(sizeof(LabCell));
    lab->startX = lab->startY = lab->treasureX = lab->treasureY = 0;

    int row = 0;
    while (row < MAX_ROWS) {
        if (fgets(lab->lab[row], MAX_COLS, in)) {
            char *tmp = strchr(lab->lab[row], 'S');
            if (tmp && lab->startX == 0 && lab->startY == 0) {
                lab->startX = (int) (tmp - lab->lab[row]);
                lab->startY = row;
            }

            tmp = strchr(lab->lab[row], 'X');
            if (tmp && lab->treasureX == 0 && lab->treasureY == 0) {
                lab->treasureX = (int) (tmp - lab->lab[row]);
                lab->treasureY = row;
            }

            row++;
        } else
            break;
    }

    lab->maxRow = row;
    return lab;
}

LabCell_p labReadBest(FILE *in) {
    LabCell_p lab = malloc(sizeof(LabCell));
    lab->startX = lab->startY = lab->treasureX = lab->treasureY = 0;

    int row = 0;
    while (row < MAX_ROWS) {
        if (fgets(lab->lab[row], MAX_COLS, in)) {
            for (int i = 0; i < MAX_COLS; i++)
                lab->costs[row][i] = lab->lab[row][i] == '#' ? LONG_MAX : -1;

            char *tmp = strchr(lab->lab[row], 'S');
            if (tmp && lab->startX == 0 && lab->startY == 0) {
                lab->startX = (int) (tmp - lab->lab[row]);
                lab->startY = row;
            }

            tmp = strchr(lab->lab[row], 'X');
            if (tmp && lab->treasureX == 0 && lab->treasureY == 0) {
                lab->treasureX = (int) (tmp - lab->lab[row]);
                lab->treasureY = row;
            }

            row++;
        } else
            break;
    }

    lab->maxRow = row;
    return lab;
}

void printLab(LabCell_p lab) {
    system("clear");
    for (int row = 0; row < lab->maxRow; row++)
        fprintf(stdout, "%s", lab->lab[row]);
    fprintf(stdout, "\n");
}

bool isValid(char ch) {
    return ch == ' ' || ch == 'S' || ch == 'X';
}

void setFalse(LabCell_p lab, int x, int y) {
    lab->lab[y][x] = '!';
    printLab(lab);
    fprintf(stdout, "\nx:%d, y:%d\n", x, y);
    fprintf(stdout, "Costs: %ld\n", lab->costs[y][x]);
}

bool labSolve(LabCell_p lab, int x, int y, long costs) {

    costs++;
    lab->costs[y][x] = lab->costs[y][x] < costs && lab->costs[y][x] != 0 ? lab->costs[y][x] : costs;
    lab->lab[y][x] = isValid(lab->lab[y][x]) ? '.' : lab->lab[y][x];

    if (abs(x - lab->treasureX) == 0 && abs(y - lab->treasureY) == 1 ||
        abs(x - lab->treasureX) == 1 && abs(y - lab->treasureY) == 0) {
        return true;
    } else {
        if (isValid(lab->lab[y][x + 1])) {
            if (!labSolve(lab, x + 1, y, costs))
                setFalse(lab, x + 1, y);
            else
                return true;
        }

        if (isValid(lab->lab[y][x - 1])) {
            if (!labSolve(lab, x - 1, y, costs))
                setFalse(lab, x - 1, y);
            else
                return true;
        }

        if (isValid(lab->lab[y + 1][x])) {
            if (!labSolve(lab, x, y + 1, costs))
                setFalse(lab, x, y + 1);
            else
                return true;
        }

        if (isValid(lab->lab[y - 1][x])) {
            if (!labSolve(lab, x, y - 1, costs))
                setFalse(lab, x, y - 1);
            else
                return true;
        }

        return false;
    }


}


bool labSolveBest(LabCell_p lab, int x, int y, long costs) {
    if (costs < lab->costs[y][x] || lab->costs[y][x] == -1)
        lab->costs[y][x] = costs;

    char prev = lab->lab[y][x];
    lab->lab[y][x] = 'X';

//    printLab(lab);

    if (abs(x - lab->treasureX) == 0 && abs(y - lab->treasureY) == 1 ||
        abs(x - lab->treasureX) == 1 && abs(y - lab->treasureY) == 0) {
        lab->lab[y][x] = prev;
        return true;
    } else {
        long currentCost = lab->costs[y][x] + 1;

        // Check if its possible to go right
        x++;
        if (isValid(lab->lab[y][x])) {
            // Check whether this field has been reached cheaper before
            if (currentCost < lab->costs[y][x] || lab->costs[y][x] == -1) {
                labSolveBest(lab, x, y, currentCost);
            }
        }

        x--;

        // Check if its possible to go left
        x--;
        if (isValid(lab->lab[y][x])) {
            // Check whether this field has been reached cheaper before
            if (currentCost < lab->costs[y][x] || lab->costs[y][x] == -1) {
                labSolveBest(lab, x, y, currentCost);
            }
        }
        x++;

        // Check if its possible to go down
        y++;
        if (isValid(lab->lab[y][x])) {
            // Check whether this field has been reached cheaper before
            if (currentCost < lab->costs[y][x] || lab->costs[y][x] == -1) {
                labSolveBest(lab, x, y, currentCost);
            }
        }
        y--;

        // Check if its possible to go up
        y--;
        if (isValid(lab->lab[y][x])) {
            // Check whether this field has been reached cheaper before
            if (currentCost < lab->costs[y][x] || lab->costs[y][x] == -1) {
                labSolveBest(lab, x, y, currentCost);
            }
        }
        y++;

        lab->lab[y][x] = prev;
    }

}

long getBestPath(LabCell_p lab) {
    int x = lab->treasureX;
    int y = lab->treasureY;
    lab->costs[y][x] = LONG_MAX;

    long costs = 0;
    bool hasMoved = true;

    while ((abs(x - lab->startX) > 1 || abs(y - lab->startY) > 1)) {
        hasMoved = false;
        long cheapest = lab->costs[y][x];
        long currentCost;

        currentCost = lab->costs[y][x + 1];
        if (currentCost != -1) {
            if (currentCost < cheapest) {
                cheapest = currentCost;
                x += 1;
                hasMoved = true;
            }
        }

        currentCost = lab->costs[y][x - 1];
        if (currentCost != -1) {
            if (currentCost < cheapest) {
                cheapest = currentCost;
                x -= 1;
                hasMoved = true;
            }
        }

        currentCost = lab->costs[y + 1][x];
        if (currentCost != -1) {
            if (currentCost < cheapest) {
                cheapest = currentCost;
                y += 1;
                hasMoved = true;
            }
        }


        currentCost = lab->costs[y - 1][x];
        if (currentCost != -1) {
            if (currentCost < cheapest) {
                cheapest = currentCost;
                y -= 1;
                hasMoved = true;
            }
        }

        if (!hasMoved) break;

        costs++;
        lab->lab[y][x] = '.';
        printLab(lab);
    }

    return costs;
}

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
    LabCell_p maze = labReadBest(in);

    bool result = labSolveBest(maze, maze->startX, maze->startY, 0);

    printLab(maze);

    if (result) {
        printLab(maze);
        long costs = getBestPath(maze);

        if (costs != 0)
            fprintf(stdout, "\nSolved! Costs: %ld", costs);
        else
            fprintf(stdout, "\nCan't be solved!");
    } else
        fprintf(stdout, "\nCan't be solved!");

    while (getchar() != '\n');

    if (in != stdin) {
        fclose(in);
    }

    exit(EXIT_SUCCESS);
}

