#include "linked_list.h"
#include "data_structs.h"
#include "table.h"
#include "lru.h"
#include "random.h"
#include "second_chance.h"
#include "fifo.h"
#include "macros.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char *concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

long int convertToByte(unsigned int numberInKB)
{
    return numberInKB * 1024;
}

long int getAddrOffset(long int pageSizeInBits)
{
    long int tmp = pageSizeInBits;
    long int offset = 0;
    while (tmp > 1)
    {
        tmp = tmp >> 1;
        offset++;
    }
    return offset;
}

long int getAddrPage(long int addr, long int offset)
{
    return addr >> offset;
}

long int convertStrAddrToInt(char *addr)
{
    long int intAddr;

    intAddr = strtol(addr, NULL, 16);
    // sscanf(addr, "%x", &intAddr);
    return intAddr;
}

int isReadOrWrite(char *line)
{
    char *addr = strtok(line, " ");
    char *opType = strtok(NULL, " ");

    if (opType[0] == 'R')
    {
        return READ;
    }

    return WRITE;
}

void getAddrFromLine(char *line, char *addr)
{
    // char lineCopy[100];
    // strcpy(lineCopy, line);
    // return strtok(lineCopy, " ");
    sscanf(line, "%s", addr);
}

void printRelatory(Table *table, char *algorithm, long int pageSize, long int memorySize, char *fileName)
{
    printf("Executando o arquivo %s...\n", fileName);
    printf("Tamanho da memoria: %ld\n", memorySize);
    printf("Tamanho das paginas: %ld\n", pageSize);
    printf("Tecnica de reposicaoo: %s\n", algorithm);
    printf("Paginas lidas: %ld\n", table->readCount);
    printf("Pagnas escritas: %ld\n", table->writeCount);
    printf("Page faults: %ld\n", table->pageFaultCount);
    printf("Substituicoes de pagina: %ld\n", table->substitutionCount);
}

void processSubstitution(Table *table, Page newPage, long int addr, char *algorithm, Queue *fifoQueue, SecondChanceQueue *secondChanceQueue)
{
    if (strcmp(algorithm, "lru") == 0)
    {
        substitutePageWithLru(table, newPage, addr);
    }
    else if (strcmp(algorithm, "2a") == 0)
    {
        Page page = dequeueSecondChanceQueue(secondChanceQueue);
        findPageIndex(table, page);
    }
    else if (strcmp(algorithm, "fifo") == 0)
    {
        Page page = dequeue(fifoQueue);
        findPageIndex(table, page);
    }
    else if (strcmp(algorithm, "random") == 0)
    {
        int pageIndex = getRandomNumber(table->maxSlotsQuantity - 1);
        insertPageInTable(table, newPage, addr, pageIndex);
    }
}

void processFileLine(Table *table, char *line, long int offset, char *algorithm, Queue *fifoQueue, SecondChanceQueue *secondChanceQueue)
{
    char addr[256];
    getAddrFromLine(line, addr);
    int opType = isReadOrWrite(line);
    long int addrInt = convertStrAddrToInt(addr);
    long int pageId = getAddrPage(addrInt, offset);

    // Page* page = (Page*) malloc(sizeof(Page));
    Page page;
    // page->addrs = createLinkedList();

    page.currentSize = 1;
    page.wasEdited = 1;
    page.id = pageId;

    // insertAtBeginning(page->addrs, addrInt);

    // printf("------TESTING------\n");
    // printf("Line: %s\n", line);
    // printf("Addr: %s\n", addr);
    // printf("opType: %d\n", opType);
    // printf("addrInt: %d / %s\n", addrInt, addr);
    // printf("page: %d / %s\n", pageId, addr);
    // printf("------------------");

    int opResult = -1;

    if (opType == READ)
    {
        opResult = readFromTable(table, addrInt, page, fifoQueue, secondChanceQueue);
    }
    else
    {
        opResult = writeIntoTable(table, addrInt, page, fifoQueue, secondChanceQueue);
    }

    if (opResult == 0)
    {
        // call substitution algorithm
        processSubstitution(table, page, addrInt, algorithm, fifoQueue, secondChanceQueue);
        table->substitutionCount++;
        if (opType == READ)
        {
            int result = readFromTable(table, addrInt, page, fifoQueue, secondChanceQueue);
            if (result == 2)
            {
                table->readCount++;
            }
        }
        else
        {
            int result = writeIntoTable(table, addrInt, page, fifoQueue, secondChanceQueue);
            // printf("\nresult: %d\n", result);
            if (result == 2)
            {
                table->writeCount++;
            }
        }
        return;
    }
    if (opResult == PAGE_FAULT)
    {
        table->pageFaultCount++;
        if (opType == READ)
        {
            table->readCount++;
        }
        else
        {
            table->writeCount++;
        }
        return;
    }
    if (opResult == 2 && opType == READ)
    {
        table->readCount++;
        return;
    }
    table->writeCount++;
    return;
}

void processFile(Table *table, char *fileName, long int offset, char *algorithm)
{
    char *filePath = concat("files/", fileName);

    FILE *file = fopen(filePath, "r");

    Queue *fifoQueue = createQueue();
    SecondChanceQueue *secondChanceQueue = createSecondChanceQueue();

    char line[256];

    if (file != NULL)
    {
        while (fgets(line, sizeof(line), file))
        {
            processFileLine(table, line, offset, algorithm, fifoQueue, secondChanceQueue);
        }
        fclose(file);
    }
    free(filePath);
}

void printFullTable(Table *table)
{
    printf("-----TABLE-----\n");
    printf("size: %ld\n", table->size);
    printf("maxSlotsQuantity: %ld\n", table->maxSlotsQuantity);
    printf("occupiedSlotsQuantity: %ld\n", table->occupiedSlotsQuantity);
    printf("maxAddrsQuantityInPage: %ld\n", table->maxAddrsQuantityInPage);
    printf("readCount: %ld\n", table->readCount);
    printf("writeCount: %ld\n", table->writeCount);
    printf("pageFaultCount: %ld\n", table->pageFaultCount);
    printf("substitutionCount: %ld\n", table->substitutionCount);
    printf("---------------\n");
    printf("-----PAGES-----\n");
    for (long int i = 0; i < table->occupiedSlotsQuantity; i++)
    {
        // printf("Page %d -> ", table->pages[i].id);
        // printList(table->pages[i].addrs);
    }
    printf("---------------\n");
}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("Usage: %s <algorithm> <file> <page_size> <memory_size>\n", argv[0]);
        return 1;
    }

    char *algorithm = argv[1];
    char *fileName = argv[2];
    unsigned int pageSizeInKB = atoi(argv[3]);
    long int pageSizeInByte = convertToByte(pageSizeInKB);
    unsigned int tableSizeInKB = atoi(argv[4]);
    long int tableSizeInByte = convertToByte(tableSizeInKB);
    long int offset = getAddrOffset(pageSizeInByte);

    Table table;
    initializeTable(&table, tableSizeInByte, pageSizeInByte);
    processFile(&table, fileName, offset, algorithm);
    printRelatory(&table, algorithm, pageSizeInKB, tableSizeInKB, fileName);
    // printFullTable(&table);
    freeTablePages(&table);
}