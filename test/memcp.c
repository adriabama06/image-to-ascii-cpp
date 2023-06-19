#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

int main()
{
    unsigned char data[5] = {35, 123, 55, 89, 10};
    unsigned char* result = malloc(sizeof(unsigned char));

    memcpy(result, data + 2, sizeof(unsigned char) * 1);

    printf("%u\n", *result);

    free(result);

    return 0;
}