#ifndef DATA_STRUCT
#define DATA_STRUCT

typedef struct Page
{
    char id;
    long int last_access_time;
    int was_edited;
} Page;

typedef struct Frame
{
    Page page;
    int isEmpty;
} Frame;

#endif