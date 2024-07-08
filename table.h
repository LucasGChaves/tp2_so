#include "data_structs.h"
#include "linked_list.h"

typedef struct Table
{
    Page* pages;
    int size;
    int occupiedSlots;
} Table;