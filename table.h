#ifndef TABLEHEADER_H
#define TABLEHEADER_H

#include "data_structs.h"
#include "linked_list.h"
#include "macros.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Table
{
    Page *pages;
    long int size;
    long int maxSlotsQuantity;
    long int occupiedSlotsQuantity;
    long int maxAddrsQuantityInPage;
    long int readCount;
    long int writeCount;
    long int pageFaultCount;
    long int substitutionCount;
    long int totalAccesses;
} Table;

void initializeTable(Table *table, long int tablePageSize, long int pageSizeInBytes);
int writeIntoTable(Table *table, long int addr, Page page/*unsigned int pageId*/);
int readFromTable(Table *table, long int addr, Page page/*unsigned int pageId*/);
long int pageIndexOnTable(Table *table, long int pageId);
void insertPageInTable(Table *table, Page page, long int addr, long int pos);
long int findPageIndex(Table *table, Page *page);
void freeTablePages(Table *table);

#endif