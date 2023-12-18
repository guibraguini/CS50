#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Invalid Arguments \n");
        return 1;
    }

    //open the file with the name on the command line
    FILE *raw = fopen(argv[1], "r");


    //check if file is opened
    if (raw == NULL)
    {
        printf("Couldn't Open the File \n");
        return 1;
    }


    //initiate a pointer variable of the byte type
    BYTE *data;
    //allocate memory to the variable data
    data = malloc(sizeof(BYTE) * 512);



    //creates a variable to count the images
    int count = 0;
    //creates a variable to name the images
    char jpeg_name[8];
    //creates a variable to check if file is over
    int over = 0;
    FILE *img = NULL;

    int size = 0;
    //loop while file isn't over
    while (over == 0)
    {
        size = fread(data, sizeof(BYTE), 512, raw);
        //check if it's the end of the file
        if (size < 512)
        {
            //if it is then file is over and the condition changes
            over = 1;
        }
        if (data[0] == 0xff  && data[1] == 0xd8 && data[2] == 0xff && (data[3] & 0xf0) == 0xe0)
        {
            //check if isnt the first jpeg
            if (count >= 1)
            {
                //close the previous image and increment the number of the next one
                fclose(img);
            }

            if (count < 10)
            {
                //name the new file with double 0 if number equal or less than 9
                sprintf(jpeg_name, "00%d.jpg", count);
            }
            else
            {
                //name the new file with only one 0 if number equal or more than 10
                sprintf(jpeg_name, "0%d.jpg", count);
            }
            //open the new file
            img = fopen(jpeg_name, "w");
            count++;
        }
        if (img != NULL)
        {
            //write on the new fille
            fwrite(data, sizeof(BYTE), size, img);
        }

    }
    //closes the remaning opened filles
    if (img != NULL)
    {
        fclose(img);
    }
    if (raw != NULL)
    {
        fclose(raw);
    }
    //free the allocated memory
    free(data);
    return 0;
}
