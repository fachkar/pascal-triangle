#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>

// two-dimension array as a dynamic commutation/lookup table
typedef unsigned long pascal_var;
pascal_var **pscltrng = NULL;

void printPascalTriangle(pascal_var **tmp2darray, pascal_var row, pascal_var position)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int spaceadder = 1;
    for (k = 0; k < (row - spaceadder); ++k) {
        printf(" ");
    }

    ++spaceadder;
    printf("1\n");
    for (k = 0; k < (row - spaceadder); ++k) {
        printf(" ");
    }
    ++spaceadder;

    printf("1 1\n");
    for (i = 0; i < row - 2; ++i) {
        for (k = 0; k < (row - spaceadder); ++k) {
            printf(" ");
        }
        ++spaceadder;
        for (j = 0; j < position ; ++j) {
            if (pscltrng[i][j] == 0)
                continue;
            printf("%lu ", pscltrng[i][j]);
        }
        printf("\n");
    }
}

pascal_var get_pascal_trg(pascal_var row, pascal_var position)
{
    pascal_var rslt = 0;
    int i = 0;
    int j = 0;

    if (row < 3) {
        rslt = 1;
    } else {
        pscltrng = (pascal_var **)malloc((row - 2)  * sizeof(pascal_var *));
        if (pscltrng != NULL) {
            for (i = 0; i < (row - 2); ++i) {
                pscltrng[i] = (pascal_var *)malloc(position * sizeof(pascal_var));
            }

            //populate pscltrng
            pscltrng[0][0] = 1;
            pscltrng[0][1] = 2;
            pscltrng[0][2] = 1;
            for (i = 1; i < row - 2; ++i) {
                for (j = 0; j < position ; ++j) {
                    if (j == 0) {
                        pscltrng[i][j] = 1;
                        continue;
                    }

                    pscltrng[i][j] = pscltrng[i - 1][j - 1] + pscltrng[i - 1][j];
                }
            }

            //printing pascal's tringle just for displaying contents after population
            //printPascalTriangle(pscltrng,row,position);

            rslt = pscltrng[row - 3][position - 1];

            //free-ing mem
            for (i = 0; i < (row - 2); ++i) {
                if (pscltrng[i] != NULL)
                    free(pscltrng[i]);
            }

            free(pscltrng);
        }
    }

    return rslt;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        printf("pasctrg <row number> <position>\n");
        return -1;
    }

    pascal_var row = strtoul(argv[1], NULL, 10);
    pascal_var  position = strtoul(argv[2], NULL, 10);
    if (position > row) {
        printf("Parameter Error! position must be less or equal to the number of rows\n");
        return -1;
    }

    printf(" computing for row:%lu, poistion:%lu\n", row, position);

    printf(" Pascal-Triangle object is: %lu\n", get_pascal_trg(row, position));

    return 0;
}




