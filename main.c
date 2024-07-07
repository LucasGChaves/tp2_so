#include "linked_list.h"
#include "stack.h"
#include <stdio.h>
#include <string.h>

#define READ 0
#define WRITE 1

unsigned int convertToByte(unsigned int numberInKB)
{
    return numberInKB * 1024;
}

unsigned int getAddrOffset(unsigned int pageSizeInBits)
{
    unsigned int tmp = pageSizeInBits;
    unsigned int offset = 0;
    while (tmp > 1)
    {
        tmp = tmp >> 1;
        offset++;
    }
    return offset;
}

unsigned int getAddrPage(unsigned int addr, unsigned int offset)
{
    return addr >> offset;
}

unsigned int convertStrAddrToInt(char *addr)
{
    unsigned int intAddr;
    sscanf(addr, "%x", &intAddr);
    return intAddr;
}

<<<<<<< HEAD
int isReadOrWrite(char* line) {
    char* addr = strtok(line, " ");
    char* opType = strtok(NULL, " ");

    if(opType[0] == 'R') {
        return READ;
    }
    
    return WRITE;
}

char* getAddrFromLine(char* line) {
    return strtok(line, " ");
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
=======
int main(int argc, char *argv[])
{
    if (argc != 5)
    {
>>>>>>> c6f01ccc7e45790682eec110aabb38981a701f88
        printf("Uso: %s <algorithm> <file> <page_size> <memory_size>\n", argv[0]);
        return 1;
    }

    unsigned int pageSizeInKB = argv[3][0] - '0';

    unsigned int pageSizeInByte = convertToByte(pageSizeInKB);

    unsigned int offset = getAddrOffset(pageSizeInByte);

<<<<<<< HEAD
    //for test purposes
    char line[100] = "004a3098 R";
    char lineCopy[100];
    char addr[100];
    strcpy(lineCopy, line);
    strcpy(addr, getAddrFromLine(line));
=======
    // for test purposes
    char addrStr[100] = "004a3098";
    unsigned int addrInt = convertStrAddrToInt(addrStr);
>>>>>>> c6f01ccc7e45790682eec110aabb38981a701f88

    int type = isReadOrWrite(lineCopy);
    printf("Original address: %s\n", addr);
    printf("Type: %d\n", type);

    unsigned int addrInt = convertStrAddrToInt(addr);

    unsigned int page = getAddrPage(addrInt, offset);
    printf("\n-------------------\n");
    printf("Page size in KB: %d\n", pageSizeInKB);
    printf("Page size in bytes: %d\n", pageSizeInByte);
    printf("Offset: %d\n", offset);
    printf("Address in HEX(int=%d): %x\n", addrInt, addrInt);
    printf("Page in HEX(int=%d): %x\n", page, page);
}