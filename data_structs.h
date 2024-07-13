#include "linked_list.h"
#include <time.h>

#ifndef DATA_STRUCT
#define DATA_STRUCT

typedef struct Page
{
    long int id;
    LinkedList *addrs;
    int wasEdited;
    long int currentSize;
    long int lastAccess;

} Page;

typedef struct Frame
{
    Page page;
    int isEmpty;
} Frame;

#endif