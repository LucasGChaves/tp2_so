#include "linked_list.h"
#include <time.h>

#ifndef DATA_STRUCT
#define DATA_STRUCT

typedef struct Page
{
    int id;
    LinkedList *addrs;
    time_t lastAccessTime;
    int wasEdited;
    int currentSize;

} Page;

typedef struct Frame
{
    Page page;
    int isEmpty;
} Frame;

#endif