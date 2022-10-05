#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

const int BLOCK_SIZE = 512;
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Verifies input
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    //Opens and checks file
    FILE *raw = fopen(argv[1], "r");
    if (raw == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    char filename[10];
    int count = 0;
    bool first = false;
    bool found = false;

    FILE *image;


    while (true)
    {
        int bytes = fread(buffer, sizeof(BYTE), BLOCK_SIZE, raw); //Reads file
        if (bytes == 0)
        {
            break;
        }


        //Checks if it is a new jpeg
        if (buffer[0] == 0xff
            && buffer[1] == 0xd8
            && buffer[2] == 0xff
            && (buffer[3] & 0xf0) == 0xe0)
        {
            found = true;

            //If it is the first jpeg
            if (!first)
            {
                first = true;
            }

            //If not, closes file
            else
            {
                fclose(image);
            }
            sprintf(filename, "%03i.jpg", count); //Formatting filename
            image = fopen(filename, "w");
            fwrite(buffer, sizeof(BYTE), bytes, image);
            count++;
        }

        else
        {
            //In case it is not a new file
            if (found)
            {
                fwrite(buffer, sizeof(BYTE), bytes, image);
            }
        }
    }

    //Closing every file
    fclose(raw);
    fclose(image);

    return 0;
}