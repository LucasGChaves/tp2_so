#include "table.h"
#include <time.h>

Table createTable(unsigned int tablePageSize, unsigned int pageSizeInBytes)
{
    Table table;
    table.pages = malloc(sizeof(Page *) * tablePageSize);
    table.size = tablePageSize;
    table.lastSlotOccupied = -1;
    table.pagesMaxSize = (pageSizeInBytes * 8) / 32;

    for (int i = 0; i < tablePageSize; i++)
    {
        table.pages[i].currentSize = 0;
        table.pages[i].wasEdited = 0;
        table.pages[i].lastAccessTime = 0;
        table.pages[i].id = -1;
    }

    return table;
}

int writeIntoTable(Table *table, unsigned int addr, unsigned int pageId)
{
    int pageIndex = pageIndexOnTable(table, pageId);

    if (pageIndex != -1)
    {
        return 0;
    }

    if (table->pages[pageIndex].currentSize == table->pagesMaxSize)
    {
        return 1;
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
        time_t now = time(NULL);
        table->pages[pageIndex].lastAccessTime = now;
    }
    return 1;
}

int readFromTable(Table *table, unsigned int addr, unsigned int pageId)
{
    int pageIndex = pageIndexOnTable(table, pageId);

    if (pageIndex == -1)
    {
        return 0;
    }

    time_t now = time(NULL);
    table->pages[pageIndex].lastAccessTime = now;
    return 1;
}

int pageIndexOnTable(Table *table, unsigned int pageId)
{
    int index = -1;
    for (int i = 0; i < table->size; i++)
    {
        if (table->pages[i].id == pageId)
        {
            index = i;
            break;
        }
    }
    return index;
}