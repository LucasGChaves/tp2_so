#include "table.h"

void initializeTable(Table *table, long int tablePageSizeInBytes, long int pageSizeInBytes)
{
    table->maxSlotsQuantity = tablePageSizeInBytes / pageSizeInBytes;

    table->pages = (Page *)malloc(sizeof(Page) * table->maxSlotsQuantity);
    table->size = tablePageSizeInBytes;
    table->occupiedSlotsQuantity = 0;
    table->maxAddrsQuantityInPage = (pageSizeInBytes * 8) / 32;
    table->readCount = 0;
    table->writeCount = 0;
    table->pageFaultCount = 0;
    table->substitutionCount = 0;
    table->totalAccesses = 0;

    int i = 0;

    for (i = 0; i < table->maxSlotsQuantity; i++)
    {
        table->pages[i].currentSize = 0;
        table->pages[i].wasEdited = 0;
        table->pages[i].id = -1;
        table->pages[i].addrs = createLinkedList();
        table->pages[i].lastAccess = 0;
    }
}

int writeIntoTable(Table *table, long int addr, Page page, Queue *fifoQueue, SecondChanceQueue *secondChanceQueue /*unsigned int pageId*/)
{
    long int pageIndex = pageIndexOnTable(table, page.id);
    time_t now = time(NULL);

    // printf("\n\n\n***************** %d %d %d *****************\n\n\n", pageIndex, table->occupiedSlotsQuantity, table->maxSlotsQuantity);
    if (pageIndex == -1)
    {
        if (table->occupiedSlotsQuantity == table->maxSlotsQuantity)
        {
            // printf("\nPAGE_FAUT_AND_SUBSTITUTION\n");
            return PAGE_FAUT_AND_SUBSTITUTION;
        }

        insertPageInTable(table, page, addr, -1);
        enqueue(fifoQueue, page);
        enqueueSecondChanceQueue(secondChanceQueue, page);
        return PAGE_FAULT;
    }

    // Página cheia -> não escreve
    if (table->pages[pageIndex].currentSize == table->maxAddrsQuantityInPage)
    {
        table->totalAccesses++;
        table->pages[pageIndex].lastAccess = table->totalAccesses;
        return OPERATION_CONCLUDED;
    }

    if (findValue(table->pages[pageIndex].addrs, addr) == -1)
    {
        if (table->pages[pageIndex].currentSize == 0)
        {
            insertAtBeginning(table->pages[pageIndex].addrs, addr);
        }
        else
        {
            insertAtEnd(table->pages[pageIndex].addrs, addr);
        }
        table->pages[pageIndex].currentSize++;
        table->totalAccesses++;
        table->pages[pageIndex].lastAccess = table->totalAccesses;
    }
    return OPERATION_CONCLUDED;
}

int readFromTable(Table *table, long int addr, Page page, Queue *fifoQueue, SecondChanceQueue *secondChanceQueue /*unsigned int pageId*/)
{
    long int pageIndex = pageIndexOnTable(table, page.id);
    // printf("\nADDR: %ld\n", addr);
    if (pageIndex == -1)
    {
        if (table->occupiedSlotsQuantity == table->maxSlotsQuantity)
        {
            return PAGE_FAUT_AND_SUBSTITUTION;
        }
        insertPageInTable(table, page, addr, -1);
        enqueue(fifoQueue, page);
        enqueueSecondChanceQueue(secondChanceQueue, page);
        return PAGE_FAULT;
    }

    table->totalAccesses++;
    table->pages[pageIndex].lastAccess = table->totalAccesses;
    return OPERATION_CONCLUDED;
}

long int pageIndexOnTable(Table *table, long int pageId)
{
    long int index = -1;
    for (long int i = 0; i < table->maxSlotsQuantity; i++)
    {
        if (table->pages[i].id == pageId)
        {
            index = i;
            break;
        }
    }
    return index;
}

void insertPageInTable(Table *table, Page page, long int addr, long int pos)
{
    table->totalAccesses++;

    if (pos == -1)
    {
        if (table->occupiedSlotsQuantity < table->maxSlotsQuantity)
        {
            freeLinkedList(table->pages[table->occupiedSlotsQuantity].addrs);
            table->pages[table->occupiedSlotsQuantity] = page;
            table->pages[table->occupiedSlotsQuantity].lastAccess = table->totalAccesses;
            table->pages[table->occupiedSlotsQuantity].addrs = createLinkedList();
            insertAtBeginning(table->pages[table->occupiedSlotsQuantity].addrs, addr);
            table->occupiedSlotsQuantity++;
            return;
        }
    }

    freeLinkedList(table->pages[pos].addrs);
    table->pages[pos] = page;
    table->pages[pos].lastAccess = table->totalAccesses;
    table->pages[pos].addrs = createLinkedList();
    insertAtBeginning(table->pages[pos].addrs, addr);
    return;
}

long int findPageIndex(Table *table, Page page)
{
    long int index = -1;

    for (long int i = 0; i < table->occupiedSlotsQuantity; i++)
    {
        if (table->pages[i].id == page.id)
        {
            index = i;
        }
    }

    return index;
}

void freeTablePages(Table *table)
{
    for (long int i = 0; i < table->maxSlotsQuantity; i++)
    {
        if (table->pages[i].id > -1)
        {
            freeLinkedList(table->pages[i].addrs);
        }
    }
    free(table->pages);
}