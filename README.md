# Duplicate File Finder

A command-line tool built in C that helps you find and clean up duplicate files in any directory.

Unlike basic tools that only check filenames, this program reads the actual binary content of files to ensure they are true duplicates, even if they have different names.

## Features

* **Recursive Scanning:** It doesn't just check one folder; it dives into every subfolder automatically.
* **Content-Based Detection:** Uses the **DJB2** hashing algorithm to ID files based on their data, not their names.
* **Memory Efficient:** Implements a custom **Linked List** to track files without wasting memory.
* **Safe Deletion:** It finds duplicates but **asks for your permission** before deleting anything.

## Project Structure

```text
├── include/
│   ├── hash.h   
│   └── list.h    
├── src/
│   ├── main.c        # Handles directory recursion and user interaction
│   ├── hash.c        # Implements the djb2 hashing algorithm to ID files
│   └── list.c        # Manages the linked list (add nodes, find duplicates, free memory)
└── Makefile          # Instructions to compile the project automatically
```
## How to Run
From the project directory:
```text
# 1. Build the project
make

# 2. Run the tool, "directory" is the directory you wish to scan
./dedup directory

# 3. Clean Up
make clean
```
