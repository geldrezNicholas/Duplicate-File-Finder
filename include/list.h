#ifndef LIST_H
#define LIST_H

//One FileNode in memory list(linked list)
typedef struct FileNode {
    char *filepath;          //The name of the file
    unsigned long hash;      //The unique ID
    struct FileNode *next;   //Pointer to the next node in the chain
} FileNode;

//Check if a hash already exists in the list
//Returns the path of the ORIGINAL file if found, or NULL if it's new.
char *find_duplicate(struct FileNode *head, unsigned long hash);

//Add a new file to the list
//Returns the new head of the list.
struct FileNode *add_file(struct FileNode *head, char *path, unsigned long hash);

//Clean up list when done
void free_list(struct FileNode *head);

#endif