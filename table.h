#ifndef TABLEHEADER_H
#define TABLEHEADER_H

#include "data_structs.h"
#include "linked_list.h"
#include "macros.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef struct Table
{
    Page *pages;
    int size;
    int maxSlotsQuantity;
    int occupiedSlotsQuantity;
    int maxAddrsQuantityInPage;
    int readCount;
    int writeCount;
    int pageFaultCount;
    int substitutionCount;
} Table;

void initializeTable(Table *table, long int tablePageSize, long int pageSizeInBytes);
int writeIntoTable(Table *table, long int addr, Page page/*unsigned int pageId*/);
int readFromTable(Table *table, long int addr, Page page/*unsigned int pageId*/);
int pageIndexOnTable(Table *table, unsigned int pageId);
void insertPageInTable(Table *table, Page page, long int addr, unsigned int pos);

int findPageIndex(Table *table, Page *page);

#endif