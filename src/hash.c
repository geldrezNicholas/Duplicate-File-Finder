#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

//Creates Unique ID(hash) for files - DJB2 Algorithm
unsigned long hash_string(unsigned long hash, unsigned char *buffer, size_t size) {
    for (size_t i = 0; i < size; i++) {
        hash = ((hash << 5) + hash) + buffer[i];
    }
    return hash;
}

//Opens file and reads buffer
unsigned long hash_file(const char *filepath) {
    //Read Binary(essential for non-text files)
    FILE *f = fopen(filepath, "rb");
    //If the file cannot be open
    if (f == NULL){ 
        return 0;
    }

    unsigned long hash = 5381; //Stable Start
    unsigned char buffer[4096]; //Buffer Allows 4KB
    size_t bytes_read;

    //While file is not empty
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), f)) > 0) {
        //Update content hash
        hash = hash_string(hash, buffer, bytes_read);
    }
    fclose(f);
    return hash;
}