#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //check that the argument count is 2
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    //open file for reading
    FILE *input_file = fopen(argv[1], "r");

    //check that the input file is valid
    if (input_file == NULL)
    {
        printf("Could not open file");
        return 2;
    }

    //store blocks of 512 bytes in an array
    unsigned char buffer[512];

    //track number of images generated
    int count_image = 0;

    //file pointer for recovered images
    FILE *output_file = NULL;

    //char filename[8]
    char *filename = malloc(8 * sizeof(char));

    //read the blocks of 512 bytes
    while (fread(buffer, sizeof(char), 512, input_file))
    {
        //check if bytes indicate start of JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (count_image > 0)
            {
                fclose(output_file);
            }
            //write JPEGfilenames
            sprintf(filename, "%03i.jpg", count_image);

            //open output_file for writing
            output_file = fopen(filename, "w");

            //count number of images found
            count_image++;
        }
        // check if output has been  used for valid input
        if (output_file != NULL)
        {
            fwrite(buffer, sizeof(char), 512, output_file);
        }
    }
    free(filename);
    fclose(output_file);
    fclose(input_file);

    return 0;
}
