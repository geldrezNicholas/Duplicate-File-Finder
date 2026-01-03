#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> //For opendir, readdir
#include <sys/stat.h> //For file stats(size, permissions)
#include "hash.h" //Include Hasher
#include "list.h"//Linked List

//Global head of linked list
FileNode *head = NULL;

void traverse_directory(const char *path)
{
    DIR *dir; //Pointer to directory stream
    struct dirent *entry; //Holds info about single file
    struct stat file_stat; //File details(size, type, etc..)
    char full_path[1024]; //Buffer storing full path string

    //Opens Directory
    dir = opendir(path);
    if (dir == NULL){
        perror("Could not open directory");
        return;
    }

    //Loop through every item in the directory
    while ((entry = readdir(dir)) != NULL){
        //Skip current folder and parent folder
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        //Build full path (path + '/' + file)
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        //Get file stats
        if (stat(full_path, &file_stat) == -1)
            continue;

        //Directory or File
        if (S_ISDIR(file_stat.st_mode)){
            //If Directory, print, and traverse new directory
            printf("[DIR]  %s\n", full_path);
            traverse_directory(full_path); // Recursion
            
        } else {
            //Calculate the hash
            unsigned long hash = hash_file(full_path);

            //Check memory for this hash
            char *original = find_duplicate(head, hash);

            //Duplicate found
            if (original != NULL) {
                printf("[DUPLICATE] %s\n", full_path);
                printf("   -> Copy of: %s\n", original);
                
                //Delete 
                printf("   Delete this duplicate? (y/n): ");
                
                char answer;
                //Listen for character(y or Y)
                scanf(" %c", &answer); 
                if (answer == 'y' || answer == 'Y') {
                    //Deletes file from hard drive
                    if (remove(full_path) == 0) {
                        printf("   DELETED successfully.\n");
                    } else {
                        perror("   Error deleting file");
                    }
                } else {
                    printf("   Kept file.\n");
                }
            } 
            // No duplicate found, so add it to memory
            else {
                head = add_file(head, full_path, hash);
                printf("[NEW] %s\n", full_path);
            }
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    //Check if the user forgot to type the folder name
    if (argc < 2) {
        printf("Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    printf("Scanning directory: %s\n", argv[1]);
    
    //Start the recursive traversal
    traverse_directory(argv[1]);

    //Clean up the memory list
    free_list(head);

    return 0;
}