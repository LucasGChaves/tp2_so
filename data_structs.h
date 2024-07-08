#include "linked_list.h"
#ifndef DATA_STRUCT
#define DATA_STRUCT
#define READ 0
#define WRITE 1
typedef struct Page
{
    int id;
    LinkedList *addrs;
    long int last_access_time;
    int was_edited;
    int maxSize;
    int currentSize;
    int base;
    int limit;

} Page;

typedef struct Frame
{
    Page page;
    int isEmpty;
} Frame;

#endif