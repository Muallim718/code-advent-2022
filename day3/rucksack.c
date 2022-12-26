#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 100

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");
    char buffer[BUFFER_SIZE], **first_elf, **second_elf, **third_elf, copy;
    int iteration = 1, length = 0, copy_count = 0, first_elf_size = 0, second_elf_size = 0, third_elf_size = 0;
    int priority = 0, priority_sum = 0;
    int upper_case_difference = 26, lower_case_conversion = 96, upper_case_conversion = 64;

    first_elf = malloc(BUFFER_SIZE * sizeof(char *));
    second_elf = malloc(BUFFER_SIZE * sizeof(char *));
    third_elf = malloc(BUFFER_SIZE * sizeof(char *));

    if (!file) {
        printf("File failed to open.\n");
        return 1;
    }

    if (argc != 2) {
        printf("Usage: ./test2 rucksack.txt\n");
        return 1;
    }

    while(fgets(buffer, BUFFER_SIZE, file) != NULL) {
        length = strlen(buffer);
        buffer[length] = '\0';
        if (iteration == 1) {
            first_elf_size = strlen(buffer);
            for (int i = 0; i < length; i++) {
                first_elf[i] = malloc(length * sizeof(char));
                *first_elf[i] = buffer[i];
            }
        }
        else if (iteration == 2) {
            second_elf_size = strlen(buffer);
            for (int i = 0; i < length; i++) {
                second_elf[i] = malloc(length * sizeof(char));
                *second_elf[i] = buffer[i];
            }
        }
        else if (iteration == 3) {
            third_elf_size = strlen(buffer);
            for (int i = 0; i < length; i++) {
                third_elf[i] = malloc(length * sizeof(char));
                *third_elf[i] = buffer[i];
            }
            iteration = 0;
        }

        if (iteration == 0) {
            for (int i = 0; i < first_elf_size; i++) {
                for (int j = 0; j < second_elf_size; j++) {
                    for (int k = 0; k < third_elf_size; k++) {
                        if ((*first_elf[i] == *second_elf[j]) && (*first_elf[i] == *third_elf[k]) && copy_count == 0) {
                            copy = *first_elf[i];
                            copy_count++;
                        }
                    }
                }
            }

            if (islower(copy)) priority = copy - lower_case_conversion;
            else if (isupper(copy)) priority = copy - upper_case_conversion + upper_case_difference;
            priority_sum += priority;
            copy_count = 0;
        }

        length = 0;
        iteration++;
    }
    printf("The sum of the priorities of all items is %i!\n", priority_sum);

    free(first_elf);
    free(second_elf);
    free(third_elf);
}