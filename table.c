#include "table.h"

void initializeTable(Table *table, long int tablePageSizeInBytes, long int pageSizeInBytes) {
    table->maxSlotsQuantity = tablePageSizeInBytes/pageSizeInBytes;
    
    table->pages = (Page*) malloc(sizeof(Page) * table->maxSlotsQuantity);
    table->size = tablePageSizeInBytes;
    table->occupiedSlotsQuantity = 0;
    table->maxAddrsQuantityInPage = (pageSizeInBytes * 8) / 32;
    table->readCount = 0;
    table->writeCount = 0;
    table->pageFaultCount = 0;
    table->substitutionCount = 0;

    int i = 0;

    for (i = 0; i < table->maxSlotsQuantity; i++) {
        table->pages[i].currentSize = 0;
        table->pages[i].wasEdited = 0;
        table->pages[i].lastAccessTime = 0;
        table->pages[i].id = -1;
        table->pages[i].addrs;
    }
}

int writeIntoTable(Table *table, long int addr, Page page/*unsigned int pageId*/) {
    int pageIndex = pageIndexOnTable(table, page.id);
    time_t now = time(NULL);

    //printf("\n\n\n***************** %d %d %d *****************\n\n\n", pageIndex, table->occupiedSlotsQuantity, table->maxSlotsQuantity);
    if (pageIndex == -1) {
        if(table->occupiedSlotsQuantity == table->maxSlotsQuantity) {
            return PAGE_FAUT_AND_SUBSTITUTION;
        }

        
        insertPageInTable(table, page, addr, -1);
        table->pages[pageIndex].lastAccessTime = now;
        return PAGE_FAULT;
    }

    //Página cheia -> não escreve
    if (table->pages[pageIndex].currentSize == table->maxAddrsQuantityInPage) {
        table->pages[pageIndex].lastAccessTime = now;
        return OPERATION_CONCLUDED;
    }

    if (findValue(table->pages[pageIndex].addrs, addr) == -1) {
        if (table->pages[pageIndex].currentSize == 0) {
            insertAtBeginning(table->pages[pageIndex].addrs, addr);
        }
        else {
            insertAtEnd(table->pages[pageIndex].addrs, addr);
        }
        table->pages[pageIndex].currentSize++;
        table->pages[pageIndex].lastAccessTime = now;
    }
    return OPERATION_CONCLUDED;
}

int readFromTable(Table *table, long int addr, Page page/*unsigned int pageId*/)
{
    int pageIndex = pageIndexOnTable(table, page.id);
    time_t now = time(NULL);

    if (pageIndex == -1) {
        if(table->occupiedSlotsQuantity == table->maxSlotsQuantity) {
            return PAGE_FAUT_AND_SUBSTITUTION;
        }
        insertPageInTable(table, page, addr, -1);
        table->pages[pageIndex].lastAccessTime = now;
        return PAGE_FAULT;
    }

    table->pages[pageIndex].lastAccessTime = now;
    return OPERATION_CONCLUDED;
}

int pageIndexOnTable(Table *table, unsigned int pageId) {
    int index = -1;
    for (int i = 0; i < table->maxSlotsQuantity; i++) {
        if (table->pages[i].id == pageId) {
            index = i;
            break;
        }
    }
    return index;
}

void insertPageInTable(Table *table, Page page, long int addr, unsigned int pos) {
    time_t now = time(NULL);

    if(pos == -1) {
        if(table->occupiedSlotsQuantity < table->maxSlotsQuantity) {
            table->pages[table->occupiedSlotsQuantity] = page;
            table->pages[table->occupiedSlotsQuantity].lastAccessTime = now;
            table->pages[table->occupiedSlotsQuantity].addrs = createLinkedList();
            insertAtBeginning(table->pages[table->occupiedSlotsQuantity].addrs, addr);
            table->occupiedSlotsQuantity++;
            return;
        }
    }

    table->pages[pos] = page;
    table->pages[pos].lastAccessTime = now;
    table->pages[pos].addrs = createLinkedList();
    insertAtBeginning(table->pages[pos].addrs, addr);
    return;
}