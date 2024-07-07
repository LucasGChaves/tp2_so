#include <stdio.h>

unsigned int convertToByte(unsigned int numberInKB) {
    return numberInKB * 1024;
}

unsigned int getAddrOffset(unsigned int pageSizeInBits) {
    unsigned int tmp = pageSizeInBits;
    unsigned int offset = 0;
    while(tmp > 1) {
        tmp = tmp>>1;
        offset++;
    }
    return offset;
}

unsigned int getAddrPage(unsigned int addr, unsigned int offset) {
    return addr >> offset;
}

unsigned int convertStrAddrToInt(char* addr) {
    unsigned int intAddr;
    sscanf(addr, "%x", &intAddr);
    return intAddr;
}


int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Uso: %s <algorithm> <file> <page_size> <memory_size>\n", argv[0]);
        return 1;
    }

    unsigned int pageSizeInKB = argv[3][0] - '0';

    unsigned int pageSizeInByte = convertToByte(pageSizeInKB);

    unsigned int offset = getAddrOffset(pageSizeInByte);

    //for test purposes
    char addrStr[100] = "004a3098";
    unsigned int addrInt = convertStrAddrToInt(addrStr);

    unsigned int page = getAddrPage(addrInt, offset);

    printf("Page size in KB: %d\n", pageSizeInKB);
    printf("Page size in bytes: %d\n", pageSizeInByte);
    printf("Offset: %d\n", offset);
    printf("Address in HEX(int=%d): %x\n", addrInt, addrInt);
    printf("Page in HEX(int=%d): %x\n", page, page);

}