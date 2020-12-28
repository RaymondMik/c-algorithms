#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define FAT_BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Ensure two words were entered at prompt
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open memory card
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Unable to open file\n");
        return 1;
    }

    typedef uint8_t BYTE;
    BYTE buffer[FAT_BLOCK_SIZE];
    FILE *jpeg_pointer = NULL;
    int counter = 0;
    bool jpeg_exists_already = false;

    // Read a FAT block from the raw image
    while (fread(&buffer, FAT_BLOCK_SIZE, 1, file) == 1)
    {
        // let's use bitwise operator &
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //JPEG has already been found
            if (jpeg_exists_already)
            {
                fclose(jpeg_pointer);
            }
            else
            {
                char file_name[8];
                // Create new JPEG file
                sprintf(file_name, "%03i.jpg", counter);
                // open new file for JPEG
                jpeg_pointer = fopen(file_name, "w");
                counter++;
            }
        }

        if (jpeg_pointer != NULL)
        {
            // write in that file
            fwrite(buffer, FAT_BLOCK_SIZE, 1, jpeg_pointer);
        }
    }

    // Close all files
    if (jpeg_pointer == NULL)
    {
        fclose(jpeg_pointer);
    }

    if (file == NULL)
    {
        fclose(file);
    }

    return 0;
}
