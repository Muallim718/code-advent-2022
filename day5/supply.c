#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define ROW_MAX 8
#define COLUMN_MAX 9
#define CRATE_SIZE 1000
#define BUFFER_SIZE 100
#define INSTRUCTIONS_START 'm'

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");
    char buffer[BUFFER_SIZE];
    int crate_lengths[COLUMN_MAX];
    int supply_crate[CRATE_SIZE][COLUMN_MAX];
    int line = 0, column_position = 0, crate_position = 0, row = 0, buffer_length = 0, instructions_start = 0;

    for (int i = 0; i < COLUMN_MAX; i++) {
        crate_lengths[i] = 0;
    }

    for (int i = 0; i < CRATE_SIZE; i++) {
        for (int j = 0; j < COLUMN_MAX; j++) {
            supply_crate[i][j] = ' ';
        }
    }

    if (!file) {
        printf("File failed to open.\n");
        return 1;
    }

    if (argc != 2) {
        printf("Usage: ./supply supply.txt");
        return 1;
    }

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        buffer_length = strlen(buffer);
        buffer[buffer_length - 1] = '\0';

        if (row != ROW_MAX) {
            for (int i = 0; i < BUFFER_SIZE; i++) {
                line++;
                if (isalpha(buffer[i])) {
                    column_position = (line + 3) / 4 - 1;
                    supply_crate[crate_position][column_position] = buffer[i];
                } 
                else if (buffer[i] == '\0') {
                    line = 0;
                    crate_position++;
                    break;
                }
            }
            row++;
        }

        if (*buffer == INSTRUCTIONS_START && instructions_start == 0) {
            for (int i = 0; i < COLUMN_MAX; i++) {
                for (int j = 0; j < ROW_MAX / 2; j++) {
                    int temp = supply_crate[j][i];
                    supply_crate[j][i] = supply_crate[ROW_MAX - j - 1][i];
                    supply_crate[ROW_MAX - j - 1][i] = temp;
                }
            }
            for (int i = 0; i < COLUMN_MAX; i++) {
                crate_lengths[i] = 0;
                for (int j = 0; j < ROW_MAX; j++) {
                    if (isalpha(supply_crate[j][i])) crate_lengths[i]++;
                }
            }
            instructions_start = 1;
        }

        if (*buffer == INSTRUCTIONS_START) {
            int crate_amount = 0, source_crate = 0, destination_crate = 0;
            int items_parsed = sscanf(buffer, "move %d from %d to %d", &crate_amount, &source_crate, &destination_crate);
            if (items_parsed != 3) {
                printf("Failed to parse items.\n");
                return 1;
            }
            for (int i = 0; i < crate_amount; i++) {
                int source_top = crate_lengths[source_crate - 1] - crate_amount + i;
                int destination_top = crate_lengths[destination_crate - 1] + i;
                int original_crate = supply_crate[source_top][source_crate - 1];
                
                supply_crate[destination_top][destination_crate - 1] = original_crate;
                supply_crate[source_top][source_crate - 1] = ' ';
            }
            for (int i = 0; i < COLUMN_MAX; i++) {
                crate_lengths[i] = 0;
                for (int j = 0; j < CRATE_SIZE; j++) {
                    if (isalpha(supply_crate[j][i])) crate_lengths[i]++;
                }
            }
        }
    }
    printf("The message is ");
    for (int i = 0; i < COLUMN_MAX; i++) {
        printf("%c", supply_crate[crate_lengths[i] - 1][i]);
    }
    printf("!\n");
    

    fclose(file);
    return 0;
}