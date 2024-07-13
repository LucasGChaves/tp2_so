#include "lru.h"
#include <limits.h>

long int findOldestPageIndex(Table *table) {
    long int oldestTimeAccess = LONG_MAX;
    long int index = -1;

    for(int i=0; i<table->occupiedSlotsQuantity; i++) {
        //printf("%d - %ld\n", table->pages[i].lastAccess, oldestTimeAccess);
        if(table->pages[i].lastAccess < oldestTimeAccess) {
            //printf("entered\n");
            oldestTimeAccess = table->pages[i].lastAccess;
            index = i;
        }
    }

    return index;
}

void substitutePageWithLru(Table *table, Page newPage, long int addr) {
    long int oldestPageIndex = findOldestPageIndex(table);
    insertPageInTable(table, newPage, addr, oldestPageIndex);
}