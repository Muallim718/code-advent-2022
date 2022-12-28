#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ROW_MAX 8
#define COLUMN_SIZE 9
#define CRATE_SIZE 100
#define BUFFER_SIZE 100

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");
    char buffer[BUFFER_SIZE];
    int line = 0, column_position = 0, crate_position = 0, count = 0, row = 0;
    int length;
    int (*supply_crate)[COLUMN_SIZE];

    supply_crate = malloc(sizeof(*supply_crate) * ROW_MAX);

    if (!file) {
        printf("File failed to open.\n");
        return 1;
    }

    if (argc != 2) {
        printf("Usage: ./supply supply.txt");
        return 1;
    }

    while (feof(file) != true) {

        fgets(buffer, BUFFER_SIZE, file);
        length = strlen(buffer);
        buffer[length - 1] = '\0';

        if (row != ROW_MAX) {
            for (int i = 0; i < BUFFER_SIZE; i++) {
                line++;
                if (isalpha(buffer[i])) {
                    column_position = (line + 3) / 4 - 1;
                    
                    supply_crate[column_position][crate_position] = buffer[i];
                } 
                else if (buffer[i] == '\0') {
                    line = 0;
                    crate_position++;
                    break;
                }
            }
            row++;
        }

        if (*buffer == 'm') {
            break;
        }
    }
    for (int i = 0; i < COLUMN_SIZE; i++) {
        for (int j = 0; j < ROW_MAX; j++) {
            printf("%c", supply_crate[i][j]);
        }
        printf("\n");
    }
    
    free(supply_crate);
    fclose(file);
    return 0;
}