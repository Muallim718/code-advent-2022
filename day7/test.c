#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define CAPACITY 100
#define BUFFER_SIZE 100
#define IS_DIRECTORY 1
#define IS_FILE 0
#define DIRECTORY_SIZE 0
#define ROOT_DIRECTORY_DES "$ cd /"
#define DIRECTORY_CHANGE "$ cd .."
#define LIST_ITEMS "$ ls"
#define ROOT_DIRECTORY "/"
#define COMMAND_START '$'
#define DIRECTORY_HEADER 'd'

typedef struct tree_node {
    struct tree_node *directory;
    struct tree_node **file;
    char *file_name;
    int file_size;
    int file_type;
    int num_file;
    int capacity;
} tree_node;

tree_node *create_node(char *file_name, tree_node *directory, int file_type, int file_size);
void add_file(tree_node *directory, tree_node *file);
void free_tree(tree_node *node); 
void print_tree(tree_node *node);
bool cd_directory(char *command);

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");
    
    char buffer[BUFFER_SIZE];
    char new_directory_name[BUFFER_SIZE];
    char directory_name[BUFFER_SIZE];
    char file_name[BUFFER_SIZE];
    int buffer_length = 0, items_parsed = 0, file_size = 0;

    tree_node *root;
    tree_node *directory;
    tree_node *file_info;
    tree_node *current_directory;
    tree_node *new_directory;

    // Initialize the root directory node
    root = create_node(ROOT_DIRECTORY, NULL, IS_DIRECTORY, DIRECTORY_SIZE);
    // Set it as the base node
    current_directory = root;

    if (!file) {
        printf("File failed to open.\n");
        return 1;
    }

    if (argc != 2) {
        printf("Usage: ./device device.txt\n");
        return 1;
    }

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        buffer_length = strlen(buffer);
        buffer[buffer_length - 1] = '\0';

        // If a directory is encountered
        if (*buffer == DIRECTORY_HEADER) {
            // Obtain the directory's name
            items_parsed = sscanf(buffer, "dir %s", directory_name);
            if (items_parsed != 1) {
                printf("Failed to obtain directory information.\n");
                return 1;
            }

            // Create a node for the directory
            directory = create_node(directory_name, current_directory, IS_DIRECTORY, DIRECTORY_SIZE);
            // Make it a children of the current parent directory
            add_file(current_directory, directory);
        }

        // If a file is encountered
        else if (isdigit(*buffer)) {
            // Obtain the file's name and size
            items_parsed = sscanf(buffer, "%i %s", &file_size, file_name);
            if (items_parsed != 2) {
                printf("Failed to obtain file information.\n");
                return 1;
            }

            // Create a node for the file
            file_info = create_node(file_name, current_directory, IS_FILE, file_size);
            // Make it a children of the current parent directory
            add_file(current_directory, file_info);
        }

        // If cd-ing into a new directory
        else if (cd_directory(buffer) == 0) {
            
            // Obtain the name of the directory being entered
            items_parsed = sscanf(buffer, "$ cd %s", directory_name);
            if (items_parsed != 1) {
                printf("Failed to obtain directory information.\n");
                return 1;
            }
            
            // Update the current directory
            for (int i = 0; i < current_directory -> num_file; i++) {
                if (strcmp(current_directory -> file[i] -> file_name, directory_name) == 0) {
                    current_directory = current_directory -> file[i];
                }
            }
        }

        // If there is a directory change, up one level, cd ..
        else if (strcmp(buffer, DIRECTORY_CHANGE) == 0) {
            // Go up one level
            // Update the current directory such that the parent directory is the new directory
            current_directory = current_directory -> directory;
        }
    }

    print_tree(root);
    free_tree(root);
    fclose(file);
    return 0;
}

bool cd_directory(char *command) {
    if (*command == COMMAND_START) {
        if (strcmp(command, DIRECTORY_CHANGE) == 0 || strcmp(command, LIST_ITEMS) == 0 || strcmp(command, ROOT_DIRECTORY_DES) == 0) {
            return true;
        }
    }

    return false;
}

tree_node *create_node(char *file_name, tree_node *directory, int file_type, int file_size) {
    int null_character = 1;
    int file_length = strlen(file_name) + null_character;

    tree_node *node = malloc(sizeof(tree_node));
    node -> file_name = malloc(file_length);
    node -> capacity = CAPACITY;
    node -> file =  malloc(sizeof(tree_node) * node -> capacity);
    node -> file_size = file_size;
    node -> directory = directory;
    node -> file_type = file_type;
    node -> num_file = 0;

    strcpy(node -> file_name, file_name);

    return node;
}

void add_file(tree_node *directory, tree_node *file) {
    int growth_factor = 2;

    if (directory -> capacity == directory -> num_file) {
        directory -> capacity = directory -> capacity * growth_factor; 
        directory -> file = realloc(directory -> file, directory -> capacity * sizeof(tree_node*));
    }

    directory -> file[directory -> num_file] = file;
    directory -> num_file++;
}

void free_tree(tree_node *node) {
    if (node != NULL) {
        for (int i = 0; i < node -> num_file; i++) {
            free_tree(node -> file[i]);
        }

        free(node -> file_name);
        free(node -> file);
        free(node);  
    }
}

void print_tree(tree_node *node) {
    printf("%s\n", node -> file_name);

    for (int i = 0; i < node -> num_file; i++) {
        print_tree(node -> file[i]);
    }
}