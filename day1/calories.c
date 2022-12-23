#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100
#define ELF_MAX 1000

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");
    char buffer[SIZE];
    int calories[ELF_MAX];
    int empty_line = 0;
    int value = 0;
    int number = 0;

    if (argc != 2) {
        printf("Usage: ./calories list.txt\n");
        return 1;
    }
    
    if (file == NULL) {
        printf("File failed to open.\n");
        return 1;
    }
    
    while (fgets(buffer, SIZE, file) != NULL) {
        number = atoi(buffer);
        value += number; 
        if (buffer[0] == '\n') {
            calories[empty_line] = value;
            empty_line++;
            value = 0;
        }
    }

    int elf_number = empty_line;
    int max = calories[0];
    for (int i = 0; i < elf_number; i++) {
        if (calories[i] > max) {
            max = calories[i];
        }
    }

    printf("The maximum amount of calories is %i.\n", max);

    fclose(file);
    return 0;
}