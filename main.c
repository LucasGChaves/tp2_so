#include "linked_list.h"
#include "stack.h"
#include "data_structs.h"
#include "table.h"
#include "lru.h"
#include "macros.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char* concat(const char *s1, const char *s2) {
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
    //sscanf(addr, "%x", &intAddr);
    return intAddr;
}

int isReadOrWrite(char* line) {
    char* addr = strtok(line, " ");
    char* opType = strtok(NULL, " ");

    if(opType[0] == 'R') {
        return READ;
    }
    
    return WRITE;
}

char* getAddrFromLine(char* line) {
    char lineCopy[100];
    strcpy(lineCopy, line);
    return strtok(lineCopy, " ");
}

void printRelatory(Table *table, char* algorithm, long int pageSize, long int memorySize, char* fileName) {
    printf("Executando o arquivo %s...\n", fileName);
    printf("Tamanho da memoria: %d\n", memorySize);
    printf("Tamanho das paginas: %d\n", pageSize);
    printf("Tecnica de reposicaoo: %s\n", algorithm);
    printf("Paginas lidas: %d\n", table->readCount);
    printf("Pagnas escritas: %d\n", table->writeCount);
    printf("Page faults: %d\n", table->pageFaultCount);
    printf("Substituicoes de pagina: %d\n", table->substitutionCount);
}

void processSubstitution(Table *table, Page newPage, long int addr, char* algorithm) {
    if(strcmp(algorithm, "lru") == 0) {
        substitutePageWithLru(table, newPage, addr);
    }
}

void processFileLine(Table *table, char* line, long int offset, char* algorithm) {
    char addr[256];
    strcpy(addr, getAddrFromLine(line));
    long int opType = isReadOrWrite(line);
    long int addrInt = convertStrAddrToInt(addr);
    long int pageId = getAddrPage(addrInt, offset);

    time_t seconds = time(NULL);
    //Page* page = (Page*) malloc(sizeof(Page));
    Page page;
    //page->addrs = createLinkedList();

    page.currentSize = 1;
    page.wasEdited = 1;
    page.lastAccessTime = seconds;
    page.id = pageId;

    //insertAtBeginning(page->addrs, addrInt);

    // printf("------TESTING------\n");
    // printf("Line: %s\n", line);
    // printf("Addr: %s\n", addr);
    // printf("opType: %d\n", opType);
    // printf("addrInt: %d / %s\n", addrInt, addr);
    // printf("page: %d / %s\n", pageId, addr);
    // printf("------------------");

    int opResult = -1;

    if(opType == READ) {
        opResult = readFromTable(table, addrInt, page);
    }
    else {
        opResult = writeIntoTable(table, addrInt, page);
    }

    if(opResult == 0) {
        //call substitution algorithm
        processSubstitution(table, page, addrInt, algorithm);
        table->substitutionCount++;
        if(opType == READ) {
            int result = readFromTable(table, addrInt, page);
            if(result == 2) {
                table->readCount++;
            }
        }
        else {
            int result = writeIntoTable(table, addrInt, page);
            //printf("\nresult: %d\n", result);
            if(result == 2) {
                table->writeCount++;
            }
        }
        return;
    }
    if(opResult == 1) {
        table->pageFaultCount++;
        if(opType == READ) {
            table->readCount++;
        }
        else {
            table->writeCount++;
        }
        return;
    }
    if(opResult == 2 && opType == READ) {
        table->readCount++;
        return;
    }
    table->writeCount++;
    return;
}

void processFile(Table *table, char* fileName, long int offset, char* algorithm) {
    char* filePath = concat("files/", fileName);
    
    FILE* file = fopen(filePath, "r");

    char line[256];

    if(file != NULL) {
        while(fgets(line, sizeof(line), file)) {
            processFileLine(table, line, offset, algorithm);
        }
        fclose(file);
    }
}

void printFullTable(Table *table) {
    printf("-----TABLE-----\n");
    printf("size: %d\n", table->size);
    printf("maxSlotsQuantity: %d\n", table->maxSlotsQuantity);
    printf("occupiedSlotsQuantity: %d\n", table->occupiedSlotsQuantity);
    printf("maxAddrsQuantityInPage: %d\n", table->maxAddrsQuantityInPage);
    printf("readCount: %d\n", table->readCount);
    printf("writeCount: %d\n", table->writeCount);
    printf("pageFaultCount: %d\n", table->pageFaultCount);
    printf("substitutionCount: %d\n", table->substitutionCount);
    printf("---------------\n");
    printf("-----PAGES-----\n");
    for(int i=0; i < table->occupiedSlotsQuantity; i++) {
        freeLinkedList(table->pages[i].addrs);
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

    char* algorithm = argv[1];
    char* fileName = argv[2];
    unsigned int pageSizeInKB = atoi(argv[3]);
    long int pageSizeInByte = convertToByte(pageSizeInKB);
    unsigned int tableSizeInKB = atoi(argv[4]);
    long int tableSizeInByte = convertToByte(tableSizeInKB);
    long int offset = getAddrOffset(pageSizeInByte);

    Table table;
    initializeTable(&table, tableSizeInByte, pageSizeInByte);
    processFile(&table, fileName, offset, algorithm);
    printRelatory(&table, algorithm, pageSizeInKB, tableSizeInKB, fileName);
    printFullTable(&table);

}