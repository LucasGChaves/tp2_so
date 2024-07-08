#include "linked_list.h"
#ifndef DATA_STRUCT
#define DATA_STRUCT
#define READ 0
#define WRITE 1
typedef struct Page
{
    int id;
    LinkedList *addrs;
    long int lastAccessTime;
    int wasEdited;
    int currentSize;

} Page;

typedef struct Frame
{
    Page page;
    int isEmpty;
} Frame;

#endif