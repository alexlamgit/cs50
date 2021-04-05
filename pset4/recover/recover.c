#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Opens the file, checking for invalid input
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Invalid file. \n");
        return 1;
    }

    // Gets the size of the file
    fseek(card, 0, SEEK_END);
    long size = ftell(card);
    rewind(card);

    // Leaving this as variable since not all cards are formatted the same way
    int blocksize = 512;

    // Find how many blocks fit in the card
    int length = size / blocksize;

    // Buffer for fread
    BYTE buffer[blocksize];

    // Number of jpegs encountered
    int no_jpegs = -1;

    int passes = 0;
    char *filename = malloc(7);
    if (filename == NULL)
    {
        printf("Not enough memory. ");
        return 1;
    }

    FILE *img = NULL;

    while (passes < length)
    {
        passes++;
        fread(buffer, 1, 512, card);

        if (buffer[0] == 0xff && buffer [1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            no_jpegs++;
            /*
                Check if this is the first JPEG encountered,
                in which case no file has to be closed first.
            */
            if (no_jpegs == 0)
            {
                sprintf(filename, "%03i.jpg", no_jpegs);

                // Create file with filename
                img = fopen(filename, "w");

                // Write data from buffer to the img file
                fwrite(buffer, 1, 512, img);
            }

            else if (no_jpegs > 0)
            {
                fclose(img);

                sprintf(filename, "%03i.jpg", no_jpegs);

                // Create file with filename
                img = fopen(filename, "w");

                // Write data from buffer to the img file
                fwrite(buffer, 1, 512, img);
            }
        }
        else if (no_jpegs  != -1)
        {
            fopen(filename, "a");
            fwrite(buffer, 1, 512, img);
        }
    }
    free(filename);
}
