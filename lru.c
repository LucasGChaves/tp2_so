#include "lru.h"

int findOldestPageIndex(Table *table) {
    time_t oldestTimeAccess = time(NULL);
    int index = -1;

    for(int i=0; i<table->occupiedSlotsQuantity; i++) {
        if(difftime(oldestTimeAccess, table->pages[i].lastAccessTime) <= 0) {
            oldestTimeAccess = table->pages[i].lastAccessTime;
            index = i;
        }
    }

    return index;
}

void substitutePageWithLru(Table *table, Page newPage, long int addr) {
    int oldestPageIndex = findOldestPageIndex(table);
    insertPageInTable(table, newPage, addr, oldestPageIndex);
}