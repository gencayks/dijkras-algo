#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("--- SYSTEM STATUS ---\n");
    printf("Compute Node: DETECTED (Arch Linux Container)\n");
    
    // Correct Syntax:
    // 1. "int *ptr" declares a pointer variable named ptr.
    // 2. "10 * sizeof(int)" calculates the total bytes needed.
    int *ptr = (int*) malloc(10 * sizeof(int));
    
    if (ptr == NULL) {
        printf("Memory Error!\n");
        return 1;
    } 
    
    printf("Memory Allocation: SUCCESS (Heap Active)\n");
    printf("Ready for C Programming.\n");
    
    free(ptr);
    return 0;
}