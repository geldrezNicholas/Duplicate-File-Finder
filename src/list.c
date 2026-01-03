#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

//Search the linked list for a specific hash
//Returns: The filepath of the duplicate if found, or NULL if not found.
char *find_duplicate(struct FileNode *head, unsigned long hash) {
    struct FileNode *current = head;

    while (current != NULL){
        if(current->hash == hash){
            return current->filepath;
        }else{
            current = current->next;
        }
    }

    return NULL;
}

//Add a new file to the front of the list
//Returns: The new head of the list.
struct FileNode *add_file(struct FileNode *head, char *path, unsigned long hash) {

    //Allocate and Initialize node 
    FileNode *node = malloc(sizeof(struct FileNode));
    node->filepath = strdup(path);
    node->hash = hash;
    node->next = head;

    return node;
}

//Free all memory used by the list
void free_list(struct FileNode *head) {
    struct FileNode *tmp;

    //Free filepath before tmp to not lose filepath access
    while (head != NULL){
        tmp = head;
        head = head->next;
        free(tmp->filepath);
        free(tmp);
    }
    
}