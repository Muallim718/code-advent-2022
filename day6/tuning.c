#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 5000
#define ARRAY_SIZE 4

char *packet(char *array, char *buffer);
int location_marker = 0;

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");
    char buffer[BUFFER_SIZE];
    char buffer_copy[BUFFER_SIZE];
    char array[ARRAY_SIZE];
    char packet_begin[ARRAY_SIZE];
    int character_match = 0, character_count = 0, offset = 0;

    if (!file) {
        printf("File failed to open.\n");
        return 1;
    }

    if (argc != 2) {
        printf("Usage: ./tuning tuning.txt");
        return 1;
    }
    
    
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        strncpy(buffer_copy, buffer, BUFFER_SIZE);
        strncpy(array, buffer, ARRAY_SIZE);
        array[ARRAY_SIZE] = '\0';
        buffer_copy[BUFFER_SIZE] = '\0';
        strncpy(packet_begin, packet(array, buffer_copy), ARRAY_SIZE);
        packet_begin[ARRAY_SIZE] = '\0';       
    }
    
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (character_match != ARRAY_SIZE) {
            character_match = 0;
            character_count++;
            for (int j = 0; j < ARRAY_SIZE; j++) {
                if (packet_begin[j % 4] == buffer_copy[i + j]) {
                    offset = j;
                    character_match++;
                }
            }
        }
    }

    printf("The number of processed characters before the first start-of-packet marker is %i!\n", character_count + offset);

    fclose(file);
    return 0;
}

char *packet(char *array, char *buffer) {
    int match = 0;
    int repeat_location = 0;

    for (int i = 0; i < ARRAY_SIZE; i++) {
        for (int j = 0; j < ARRAY_SIZE; j++) {
            if (array[i] == array[j] && i != j && match == 0) {
                repeat_location = i + 1;
                match = 1;
            }
        }
    }

    location_marker += repeat_location;

    if (match == 0) return array;

    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (repeat_location + i < BUFFER_SIZE) {
            array[i] = buffer[location_marker + i];
        }
    }

    return packet(array, buffer);
}