#include "helpers.h"
#include<math.h>


//declare a function to cap the value
float cap(float value);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // go through all the image height
    for (int i = 0; i < height; i++)
    {
        // go all through the image width for every height pixel
        for (int j = 0; j < width; j++)
        {
            //creates a temporaly float variable to save the float value of the sum of all the rgb colors of the pixel
            float temp_result = (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen);
            //round the float value divided by 3
            temp_result = round(temp_result / 3);
            // the color blue recives the value of the temp variable
            image[i][j].rgbtBlue = temp_result;
            // the color Green recives the value of the temp variable
            image[i][j].rgbtGreen = temp_result;
            // the color red recives the value of the temp variable
            image[i][j].rgbtRed = temp_result;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // go through all the image height
    for (int i = 0; i < height; i++)
    {
        // go all through the image width for every height pixel
        for (int j = 0; j < width; j++)
        {
            //creates a temporaly float variable to save the new pixel red value
            float new_red = (image[i][j].rgbtRed * 0.393) + (image[i][j].rgbtGreen * 0.769)  + (image[i][j].rgbtBlue * 0.189);
            //round and cap the result value
            new_red = cap(round(new_red));
            //creates a temporaly float variable to save the new pixel green value
            float new_green = (image[i][j].rgbtRed * 0.349) + (image[i][j].rgbtGreen * 0.686)  + (image[i][j].rgbtBlue * 0.168);
            //round and cap the result value
            new_green = cap(round(new_green));
            //creates a temporaly float variable to save the new pixel blue value
            float new_blue = (image[i][j].rgbtRed * 0.272) + (image[i][j].rgbtGreen * 0.534)  + (image[i][j].rgbtBlue * 0.131);
            //round and cap the result value
            new_blue = cap(round(new_blue));
            // the color red recives the value of the temp variable
            image[i][j].rgbtRed = new_red;
            // the color Green recives the value of the temp variable
            image[i][j].rgbtGreen = new_green;
            // the color blue recives the value of the temp variable
            image[i][j].rgbtBlue = new_blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // creates a variable to store the last width pixel of the image tha was not modified yet
    int negative_j;
    // go through all the image height
    for (int i = 0; i < height; i++)
    {
        //negative_j reset to the last width pixel of the image
        negative_j = width - 1;
        // go all through the image width for every height pixel
        for (int j = 0; j < width / 2; j++)
        {
            // creates a variable to temporaly store the pixel rgb value
            RGBTRIPLE pixel = image[i][j];
            // insert the rgb value of the last pixel on the first one
            image[i][j] = image[i][negative_j];
            // insert the rgb value of the temporary pixel on the last one
            image[i][negative_j] = pixel;

            // negative_j moves 1 pixel closer to the center of the image
            negative_j--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //creates a new image to recive the blur
    RGBTRIPLE new_image[height][width];
    // go through all the image height
    for (int i = 0; i < height; i++)
    {
        // go all through the image width for every height pixel
        for (int j = 0; j < width; j++)
        {
            //creates a variable to temporarily recive the blue value
            int temp_blue = 0;
            //creates a variable to temporarily recive the red value
            int temp_red = 0;
            //creates a variable to temporarily recive the green value
            int temp_green = 0;
            //creates a variable that gets all the height neighbors initialized with -1 so it can catch previous neighbors
            int blur_i = -1;
            //creates a variable that gets all the widht neighbors initialized with -1 so it can catch previous neighbors
            int blur_j = -1;
            //creates a variable that counts how many height neighbors it was catched
            int count_i = 0;
            //creates a variable that counts how many width neighbors it was catched
            int count_j = 0;
            //loops through all the height neighbors
            while (i + blur_i <= i + 1)
            {
                //check if there's a neighbor on top
                if (i + blur_i < 0)
                {
                    blur_i = 0;
                }
                //check if there's a neighbor under
                else if (i + blur_i >= height)
                {
                    break;
                }
                blur_j = -1;
                count_j = 0;
                //loops through all the height neighbors
                while (j + blur_j <= j + 1)
                {

                    //check if there's a neighbor on the left
                    if (j + blur_j < 0)
                    {
                        blur_j = 0;
                    }
                    //check if there's a neighbor on the right
                    else if (j + blur_j >= width)
                    {
                        break;
                    }
                    //add the blue value of the current neighbor to the temp_blue var
                    temp_blue += image[i + blur_i][j + blur_j].rgbtBlue;
                    //add the red value of the current neighbor to the temp_red var
                    temp_red += image[i + blur_i][j + blur_j].rgbtRed;
                    //add the green value of the current neighbor to the temp_green var
                    temp_green += image[i + blur_i][j + blur_j].rgbtGreen;
                    blur_j++;
                    count_j++;
                }
                blur_i++;
                count_i++;
            }

            // creates a temporaly variable to recive the float value of count_i * count_j
            float temp_count = count_i * count_j;
            // creates a temporaly variable to recive the float values and round them to int
            float temp_result = temp_blue;
            temp_result = round(temp_result / temp_count);
            // the color blue of the pixel recive a sum of all the neighboring blue values divided by the number of neighbors
            new_image[i][j].rgbtBlue = temp_result;
            temp_result = temp_green;
            temp_result = round(temp_result / temp_count);
            // the color Green of the pixel recive a sum of all the neighboring green values divided by the number of neighbors
            new_image[i][j].rgbtGreen = temp_result;
            temp_result = temp_red;
            temp_result = round(temp_result / temp_count);
            // the color red of the pixel recive a sum of all the neighboring red values divided by the number of neighbors
            new_image[i][j].rgbtRed = temp_result;
        }
    }

    // go through all the image height
    for (int i = 0; i < height; i++)
    {
        // go all through the image width for every height pixel
        for (int j = 0; j < width; j++)
        {
            // the output image recive the new image value
            image[i][j] = new_image[i][j];
        }
    }
    return;
}

//cap the value between 0 and 255
float cap(float value)
{
    //check if value is greater then 255
    if (value > 255)
    {
        //if it is then cap it to 255
        value = 255;
    }
    //check if value is less then 0
    if (value < 0)
    {
        //if it is then cap it to 0
        value = 0;
    }
    return value;
}
