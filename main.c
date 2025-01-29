#include <stdio.h>
#include <stdlib.h>

#define MAX_ROD_LENGTH 100

typedef struct {
    int length;
    int value;
} Piece;

int compare_pieces(const void *a, const void *b) {
    return ((Piece *)b)->value - ((Piece *)a)->value;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <supplied rod length>\n", argv[0]);
        return 1;
    }

    int rodLength = atoi(argv[1]);
    if (rodLength <= 0) {
        fprintf(stderr, "Invalid rod length.\n");
        return 1;
    }

    Piece pieces[MAX_ROD_LENGTH];
    int numPieces = 0;
    
    printf("Enter the list of piece lengths and prices in the format <length>, <value> (Ctrl+D to end input):\n");
    while (scanf("%d, %d", &pieces[numPieces].length, &pieces[numPieces].value) == 2) {
        if (pieces[numPieces].length > rodLength) {
            printf("Ignoring piece of length %d since it is longer than the rod.\n", pieces[numPieces].length);
        } else {
            numPieces++;
        }
    }

    if (numPieces == 0) {
        printf("No valid pieces entered.\n");
        return 1;
    }

    qsort(pieces, numPieces, sizeof(Piece), compare_pieces);

    int totalValue = 0;
    int remainingLength = rodLength;

    for (int i = 0; i < numPieces && remainingLength > 0; i++) {
        if (pieces[i].length <= remainingLength) {
            int numCuts = remainingLength / pieces[i].length;
            int cutValue = numCuts * pieces[i].value;
            printf("%d @ %d = %d\n", numCuts, pieces[i].length, cutValue);
            totalValue += cutValue;
            remainingLength -= numCuts * pieces[i].length;
        }
    }

    printf("\nRemainder: %d\n", remainingLength);
    printf("Value: %d\n", totalValue);

    return 0;
}
