#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

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
    int is_directory;
    int num_file;
    int capacity;
} tree_node;

tree_node *create_node(char *file_name, tree_node *directory, int is_directory, int file_size);
void add_file(tree_node *directory, tree_node *file);
void free_tree(tree_node *node); 
void print_tree(tree_node *node);
bool check_command(char *command);

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");
    
    char buffer[BUFFER_SIZE];
    char directory_name[BUFFER_SIZE];
    char file_name[BUFFER_SIZE];

    int buffer_length = 0, items_parsed = 0, file_size = 0;

    tree_node *root;
    tree_node *directory;
    tree_node *file_info;
    tree_node *current_directory;

    root = create_node(ROOT_DIRECTORY, NULL, IS_DIRECTORY, DIRECTORY_SIZE);
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


        if (strcmp(buffer, DIRECTORY_CHANGE) == 0) {
            current_directory = current_directory -> directory;
        }

        if (check_command(buffer) == 0) {
            items_parsed = sscanf(buffer, "$ cd %s", directory_name);
            if (items_parsed != 1) {
                printf("Failed to obtain directory information.\n");
                return 1;
            }
            
            current_directory = create_node(directory_name, root, IS_DIRECTORY, DIRECTORY_SIZE);
        }

        if (*buffer == DIRECTORY_HEADER) {
            items_parsed = sscanf(buffer, "dir %s", directory_name);
            if (items_parsed != 1) {
                printf("Failed to obtain directory information.\n");
                return 1;
            }

            directory = create_node(directory_name, current_directory, IS_DIRECTORY, DIRECTORY_SIZE);
            add_file(current_directory, directory);
            current_directory = directory;
        }

        else if (isdigit(*buffer)) {
            items_parsed = sscanf(buffer, "%i %s", &file_size, file_name);
            if (items_parsed != 2) {
                printf("Failed to obtain file information.\n");
                return 1;
            }

            file_info = create_node(file_name, current_directory, IS_FILE, file_size);
            add_file(current_directory, file_info);
        }
    }

    print_tree(root);
    free_tree(root);
    free_tree(directory);
    free_tree(file_info);
    fclose(file);
    return 0;
}

bool check_command(char *command) {
    if (*command == COMMAND_START) {
        if (strcmp(command, DIRECTORY_CHANGE) == 0 || strcmp(command, LIST_ITEMS) == 0 || strcmp(command, ROOT_DIRECTORY_DES) == 0) {
            return true;
        }
    }

    else if (*command == DIRECTORY_HEADER || isdigit(*command)) {
        return true;
    }

    return false;
}

tree_node *create_node(char *file_name, tree_node *directory, int is_directory, int file_size) {
    tree_node *node = malloc(sizeof(tree_node));

    node -> file_name = malloc(strlen(file_name) + 1);
    node -> directory = directory;
    node -> is_directory = is_directory;
    node -> file_size = file_size;
    node -> file =  malloc(0);
    node -> capacity = 0;
    node -> num_file = 0;

    strcpy(node -> file_name, file_name);

    return node;
}

void add_file(tree_node *directory, tree_node *file) {
    if (directory -> capacity == directory -> num_file) {
        directory -> capacity = directory -> capacity * 2; 
        directory -> file = realloc(directory -> file, directory -> capacity * sizeof(tree_node*));
    }

    directory -> file[directory -> num_file] = file;
    directory -> num_file++;
}

void free_tree(tree_node *node) {
    if (node == NULL) {
        return; 
    }

    for (int i = 0; i < node -> num_file; i++) {
        free_tree(node -> file[i]);
    }

    free(node -> file_name);
    free(node -> file);
    free(node);  
}

void print_tree(tree_node *node) {
    printf("%s\n", node -> file_name);

    for (int i = 0; i < node -> num_file; i++) {
        print_tree(node -> file[i]);
    }
}