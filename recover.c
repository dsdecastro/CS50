#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        printf("Usage ./recover image\n");
        return 1;
    }

    FILE *imageFile = fopen(argv[1], "r");

    // Check to see if the file can be opened
    if (imageFile == NULL)
    {
        printf("Image could not be opened.\n");
        return 1;
    }

    // Read from the given file in blocks of size 512
    FILE *writeFile = fopen(".tmp", "w");
    char *writeFileName = malloc(8 * sizeof(char));
    uint8_t *buffer = malloc(512 * sizeof(uint8_t));
    int counter = 0;
    while (fread(buffer, sizeof(uint8_t), 512, imageFile) == 512)
    {
        // Check for the JPEG signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef)
        {
            // Open a new JPEG file if signature is detected
            fclose(writeFile);
            sprintf(writeFileName, "%03i.jpg", counter);
            writeFile = fopen(writeFileName, "w");
            counter++;
        }

        // Write to the current file
        fwrite(buffer, sizeof(uint8_t), 512, writeFile);
    }

    // Free up space used by malloc
    free(buffer);
    free(writeFileName);

    // Close the imageFile and writeFile
    fclose(imageFile);
    fclose(writeFile);

    // Remove temporary file
    remove(".tmp");

    return 0;
}