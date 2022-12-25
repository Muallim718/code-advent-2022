#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define SIZE 100

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");
    char buffer[SIZE];
    char first_half[SIZE];
    char second_half[SIZE];
    char copy;
    int copy_count = 0;
    int length = 0;
    int priority = 0;
    int priority_sum = 0;
    int upper_case_difference = 26;
    int lower_case_conversion = 96;
    int upper_case_conversion = 64;

    if (argc != 2) {
        printf("Usage: ./rucksack rucksack.txt\n");
        return 1;
    }

    if (file == NULL) {
        printf("File failed to open.\n");
        return 1;
    }

    while(fgets(buffer, SIZE, file) != NULL) {
        length = strlen(buffer);
        for (int i = 0; i < length / 2; i++) {
            first_half[i] = buffer[i];
            second_half[i] = buffer[i + length / 2];
        }
        for (int i = 0; i < length / 2; i++) {
            for (int j = 0; j < length / 2; j++) {
                if ((first_half[i] == second_half[j]) && copy_count == 0) {
                    copy = first_half[i];
                    copy_count++;
                }
            }
        }
        if (islower(copy)) priority = copy - lower_case_conversion;
        else if (isupper(copy)) priority = copy - upper_case_conversion + upper_case_difference;
        priority_sum += priority;
        copy_count = 0;
    }
    printf("The sum of the priorities of all items is %i!\n", priority_sum);

    fclose(file);
    return 0;
}