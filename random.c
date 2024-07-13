#include "random.h"
#include <stdlib.h>

int getRandomNumber(int n)
{
    srand(456);
    return rand() % n;
}