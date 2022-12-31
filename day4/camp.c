#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 100

struct section {
    int min;
    int max;
};

bool pair(struct section first_elf, struct section second_elf);
bool overlap(struct section first_elf, struct section second_elf);

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");
    char buffer[SIZE];
    char *token;
    int length, token_number;
    int iteration = 1, pair_count = 0, overlap_count = 0;

    if (!file) {
        printf("File failed to open.\n");
        return 1;
    }

    if (argc != 2) {
        printf("Usage: ./camp camp.csv");
        return 1;
    }

    struct section first_elf;
    struct section second_elf;

    while(fgets(buffer, SIZE, file) != NULL) {
        length = strlen(buffer);
        buffer[length - 1] = '\0';

        for (int i = 0; i < length; i++) {
            if (buffer[i] == '-') {
                buffer[i] = ',';
            }
        }
        token = strtok(buffer, ",");

        while (token != NULL) {
            token_number = atoi(token);
            if (iteration == 1) first_elf.min = token_number;
            else if (iteration == 2) first_elf.max = token_number;
            else if (iteration == 3) second_elf.min = token_number;
            else if (iteration == 4) second_elf.max = token_number, iteration = 0;
            token = strtok(NULL, ",");
            iteration++;
        }
        
        if (pair(first_elf, second_elf)) pair_count++;
        if (overlap(first_elf, second_elf)) overlap_count++;
    }
    printf("There are %i pairs!\n", pair_count);
    printf("There are %i overlapping pairs!\n.", overlap_count);

    fclose(file);
    return 0;
}

bool pair(struct section first_elf, struct section second_elf) {

    if ((first_elf.min >= second_elf.min) && (first_elf.max <= second_elf.max)) return true;
    else if ((first_elf.min <= second_elf.min) && (first_elf.max >= second_elf.max)) return true;
    return false;
}

bool overlap(struct section first_elf, struct section second_elf) {

    int first_elf_numbers[SIZE], second_elf_numbers[SIZE];
    int first_elf_amount = first_elf.max - first_elf.min;
    int second_elf_amount = second_elf.max - second_elf.min;

    for (int i = 0; i <= first_elf_amount; i++) {
        first_elf_numbers[i] = i + first_elf.min;
    }

    for (int i = 0; i <= second_elf_amount; i++) {
        second_elf_numbers[i] = i + second_elf.min;
    }

    for (int i = 0; i <= first_elf_amount; i++) {
        for (int j = 0; j <= second_elf_amount; j++) {
            if (first_elf_numbers[i] == second_elf_numbers[j]) return true;
        }
    }
    return false;
}