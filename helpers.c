#include "helpers.h"
#include <math.h>
#include <stdio.h>

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



// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //creates a new image to recive the sobel filtet
    RGBTRIPLE new_image[height][width];
    // go through all the image height
    for (int i = 0; i < height; i++)
    {
        // go all through the image width for every height pixel
        for (int j = 0; j < width; j++)
        {
            //creates a variable to temporarily recive the blue gx value
            int temp_blue_gx = 0;
            //creates a variable to temporarily recive the red gx value
            int temp_red_gx = 0;
            //creates a variable to temporarily recive the green gx value
            int temp_green_gx = 0;
            //creates a variable to temporarily recive the blue gy value
            int temp_blue_gy = 0;
            //creates a variable to temporarily recive the red gy value
            int temp_red_gy = 0;
            //creates a variable to temporarily recive the green gy value
            int temp_green_gy = 0;
            //creates a variable that gets all the height neighbors initialized with -1 so it can catch previous neighbors
            int neighbors_i = -1;
            //creates a variable that gets all the widht neighbors initialized with -1 so it can catch previous neighbors
            int neighbors_j = -1;

            //loops through all the height neighbors
            while (i + neighbors_i <= i + 1)
            {
                //check if there's a neighbor on top
                if (i + neighbors_i < 0)
                {
                    neighbors_i = 0;
                }
                //check if there's a neighbor under
                else if (i + neighbors_i >= height)
                {
                    break;
                }


                //loops through all the height neighbors
                while (j + neighbors_j <= j + 1)
                {
                    //check if there's a neighbor on the left
                    if (j + neighbors_j < 0)
                    {
                        neighbors_j = 0;
                    }
                    //check if there's a neighbor on the right
                    else if (j + neighbors_j >= width)
                    {
                        break;
                    }
                    //creates a variable to store neighbors_i and change it accordly
                    int neighbors_gx = neighbors_i;
                    //creates a variable to store neighbors_j and change it accordly
                    int neighbors_gy = neighbors_j;
                    //adjust the middle values
                    if (neighbors_gx == 0 || neighbors_gy == 0)
                    {
                        neighbors_gx *= 2;
                        neighbors_gy *= 2;
                    }

                    //stores the past sum with the new blue value acording to gx
                    temp_blue_gx += image[i][j].rgbtBlue * neighbors_gx;
                    //stores the past sum with the new red value acording to gx
                    temp_red_gx += image[i][j].rgbtRed * neighbors_gx;
                    //stores the past sum with the new green value acording to gx
                    temp_green_gx += image[i][j].rgbtGreen * neighbors_gx;
                    //stores the past sum with the new blue value acording to gy
                    temp_blue_gy += image[i][j].rgbtBlue * neighbors_gy;
                    //stores the past sum with the new red value acording to gy
                    temp_red_gy += image[i][j].rgbtRed * neighbors_gy;
                    //stores the past sum with the new green value acording to gy
                    temp_green_gy += image[i][j].rgbtGreen * neighbors_gy;
                    neighbors_j++;
                }
                neighbors_i++;
            }

            //creates a new variable to store the new blue value acording to sobel
            float sobel_blue = (temp_blue_gx * temp_blue_gx) + (temp_blue_gy * temp_blue_gy);
            sobel_blue = round(sqrt(sobel_blue));
            //creates a new variable to store the new red value acording to sobel
            float sobel_red = (temp_red_gx * temp_red_gx) + (temp_red_gy * temp_red_gy);
            sobel_red = round(sqrt(sobel_red));
            //creates a new variable to store the new green value acording to sobel
            float sobel_green = (temp_green_gx * temp_green_gx) + (temp_green_gy * temp_green_gy);
            sobel_green = round(sqrt(sobel_green));
            //normalize the sobel blue value if more than 255
            if (sobel_blue > 255)
            {
                sobel_blue = 255;
            }
            //normalize the sobel blue value if less than 0
            if (sobel_blue < 0)
            {
                sobel_blue = 0;
            }
            //normalize the sobel red value if more than 255
            if (sobel_red > 255)
            {
                sobel_red = 255;
            }
            //normalize the sobel red value if less than 0
            if (sobel_red < 0)
            {
                sobel_red = 0;
            }
            //normalize the sobel green value if more than 255
            if (sobel_green > 255)
            {
                sobel_green = 255;
            }
            //normalize the sobel green value if less than 0
            if (sobel_green < 0)
            {
                sobel_green = 0;
            }


                    new_image[i][j].rgbtBlue = sobel_blue;
                    new_image[i][j].rgbtRed = sobel_red;
                    new_image[i][j].rgbtGreen = sobel_green;
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
