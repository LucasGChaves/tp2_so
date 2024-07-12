#include "linked_list.h"
#include <time.h>

#ifndef DATA_STRUCT
#define DATA_STRUCT

typedef struct Page
{
    int id;
    LinkedList *addrs;
    time_t lastAccessTime; // user difftime(time1, time0) para comparar. Se positivo, time1 é mais tarde que time2
    int wasEdited;
    int currentSize;

} Page;

typedef struct Frame
{
    Page page;
    int isEmpty;
} Frame;

#endif