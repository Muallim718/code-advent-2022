#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");

    if (argc != 2) {
        printf("Usage: ./rucksack rucksack.txt\n");
        return 1;
    }

    if (file == NULL) {
        printf("File failed to open.\n");
        return 1;
    }
    
    return 0;
}