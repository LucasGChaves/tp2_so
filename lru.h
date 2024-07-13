#include "table.h"

long int findOldestPageIndex(Table *table);
void substitutePageWithLru(Table *table, Page page, long int addr);