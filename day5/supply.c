#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");

    if (!file) {
        printf("File failed to open.\n");
        return 1;
    }

    if (argc != 2) {
        printf("Usage: ./supply supply.txt");
        return 1;
    }

    return 0;
}