#include <stdio.h>
#include <string.h>
#include <assert.h>

char* stringToHex(char* input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = strlen(input);

    char output[100];
    int count = 0;

    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output[count] = lut[c >> 4];
        count++;
        output[count] = lut[c & 15];
        count++;
    }
    return output;
}

int main()
{
    char string[100];
    char result[100];

    printf("input : ");
    gets(string);

    printf("result : %2s\nLength input -> %d\nLength convertion ->%d\n", stringToHex(string), strlen(string), strlen(stringToHex(string)));
    return 0;
}