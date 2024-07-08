#include "table.h"

Table createTable(unsigned int tablePageSize, unsigned int pageSizeInBytes) {
    Table table;
    table.pages = malloc(sizeof(Page*)*tablePageSize);
    table.size = tablePageSize;

    for(int i=0; i<tablePageSize; i++) {
        table.pages[i].currentSize = 1;
        table.pages[i].was_edited = 0;
        table.pages[i].last_access_time = 0;
        table.pages[i].id = -1;
        table.pages[i].base = i * pageSizeInBytes;
        table.pages[i].limit = ((i + 1) * pageSizeInBytes - 1);
        table.pages[i].maxSize = (pageSizeInBytes * 8)/32;
    }
    return table;
}

int writeIntoTable(Table *table, unsigned int addr, int opType, unsigned int page) {
    int pageFound = 0;

    for(int i=0; i<table->size; i++) {

        //página encontrada na tabela
        if(table->pages[i].base >= page && table->pages[i].limit <= page) {
            pageFound = 1;
            if(opType == WRITE) {
                //se o endereço não existe ainda na tabela
                if(findValue(table->pages[i].addrs, addr) == -1) {
                    //página vazia
                    if(table->pages[i].currentSize == 0) {
                        table->pages[i].addrs = createLinkedList();
                        insertAtBeginning(table->pages[i].addrs, addr);
                        table->pages[i].currentSize++;
                        return 1;
                    }
                    //página cheia
                    if(table->pages[i].currentSize == table->pages[i].maxSize) {
                        return 1;
                    }
                    //página já com endereços
                    insertAtEnd(table->pages[i].addrs, addr);
                    table->pages[i].currentSize++;
                    return 1;
                }
                //endereço já existe na tabela
                else {
                    return 1;
                }
            }
            //se encontrou
            return 1;
        }
    }

    if(!pageFound) {
        return 0;
    }
}