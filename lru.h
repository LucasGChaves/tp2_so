#include "table.h"

int findOldestPageIndex(Table *table);
void substitutePageWithLru(Table *table, Page page, long int addr);