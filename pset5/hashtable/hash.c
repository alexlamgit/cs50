#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

int main(int argc, char *argv[])
{
    FILE *dict = fopen(argv[1], "r");

    fseek(dict, 0, SEEK_END);
    long size = ftell(dict);
    rewind(dict);

    /*
    char *buffer = malloc(sizeof(dict));
    do
    {
        fscanf(dict, "%s", buffer);
    }
    while ((fscanf(dict, "%s", buffer)) != EOF);
    */

    char *name = "A\0";
    int hashed = hash(name) % 9999;
    printf("%u, %ld\n", hashed, size);
    //fclose(dict);
    //free(buffer);
    return 0;
}
