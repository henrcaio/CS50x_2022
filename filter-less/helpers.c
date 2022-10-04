#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double aux = 0;
    //Goes throught lines
    for (int i = 0; i < height; i++)
    {
        //Goes throught columns
        for (int j = 0; j < width; j++)
        {
            aux = (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0; //Sets average value
            image[i][j].rgbtBlue = image[i][j].rgbtRed = image[i][j].rgbtGreen = round(aux); //Assigns average value
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //Goes throught lines
    for (int i = 0; i < height; i++)
    {
        //Goes throught columns
        for (int j = 0; j < width; j++)
        {

            //Turns RGB values into sepia
            int sepiaBlue = round((image[i][j].rgbtBlue * 0.131) + (image[i][j].rgbtRed * 0.272) + (image[i][j].rgbtGreen * 0.534));
            int sepiaRed = round((image[i][j].rgbtBlue * 0.189) + (image[i][j].rgbtRed * 0.393) + (image[i][j].rgbtGreen * 0.769));
            int sepiaGreen = round((image[i][j].rgbtBlue * 0.168) + (image[i][j].rgbtRed * 0.349) + (image[i][j].rgbtGreen * 0.686));

            //Ensures values will not exceed max value
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            //Assigns sepia value
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Goes throught lines
    for (int i = 0; i < height; i++)
    {
        int k = (width - 1);

        //Goes throught columns left-to-right
        for (int j = 0; j <= (width - 1) / 2 ; j++, k--)
        {

            //Storing RGB values in auxiliar variables
            int blue = image[i][j].rgbtBlue;
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;

            //Moving pixels right-to-left
            image[i][j].rgbtBlue = image[i][k].rgbtBlue;
            image[i][j].rgbtRed = image[i][k].rgbtRed;
            image[i][j].rgbtGreen = image[i][k].rgbtGreen;

            //Moving pixels left-to-right
            image[i][k].rgbtBlue = blue;
            image[i][k].rgbtRed = red;
            image[i][k].rgbtGreen = green;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Making a copied image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }

    //Blurring image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double blurRed = 0.0;
            double blurGreen = 0.0;
            double blurBlue = 0.0;

            //Top left corner
            if (i == 0 && j == 0)
            {
                blurRed += copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed;
                blurRed += copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed;
                blurRed = blurRed / 4.0;

                blurGreen += copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen;
                blurGreen += copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen;
                blurGreen = blurGreen / 4.0;

                blurBlue += copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue;
                blurBlue += copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue;
                blurBlue = blurBlue / 4.0;

                image[i][j].rgbtRed = round(blurRed);
                image[i][j].rgbtGreen = round(blurGreen);
                image[i][j].rgbtBlue = round(blurBlue);
            }

            //Top right corner
            else if (i == 0 && j == (width - 1))
            {
                blurRed += copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed;
                blurRed += copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed;
                blurRed = blurRed / 4.0;

                blurGreen += copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen;
                blurGreen += copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen;
                blurGreen = blurGreen / 4.0;

                blurBlue += copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue;
                blurBlue += copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue;
                blurBlue = blurBlue / 4.0;

                image[i][j].rgbtRed = round(blurRed);
                image[i][j].rgbtGreen = round(blurGreen);
                image[i][j].rgbtBlue = round(blurBlue);
            }

            //Bottom left corner
            else if (i == (height - 1) && j == 0)
            {
                blurRed += copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed;
                blurRed += copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed;
                blurRed = blurRed / 4.0;

                blurGreen += copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen;
                blurGreen += copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen;
                blurGreen = blurGreen / 4.0;

                blurBlue += copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue;
                blurBlue += copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue;
                blurBlue = blurBlue / 4.0;

                image[i][j].rgbtRed = round(blurRed);
                image[i][j].rgbtGreen = round(blurGreen);
                image[i][j].rgbtBlue = round(blurBlue);
            }

            //Bottom right corner
            else if (i == (height - 1) && j == (height - 1))
            {
                blurRed += copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed;
                blurRed += copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed;
                blurRed = blurRed / 4.0;

                blurGreen += copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen;
                blurGreen += copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen;
                blurGreen = blurGreen / 4.0;

                blurBlue += copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue;
                blurBlue += copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue;
                blurBlue = blurBlue / 4.0;

                image[i][j].rgbtRed = round(blurRed);
                image[i][j].rgbtGreen = round(blurGreen);
                image[i][j].rgbtBlue = round(blurBlue);
            }

            //Top line
            else if (i == 0 && j > 0 && j < (width - 1))
            {
                blurRed += copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed;
                blurRed += copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed;
                blurRed = (blurRed / 6.0);

                blurGreen += copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen;
                blurGreen += copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen;
                blurGreen = (blurGreen / 6.0);

                blurBlue += copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue;
                blurBlue += copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue;
                blurBlue = (blurBlue / 6.0);

                image[i][j].rgbtRed = round(blurRed);
                image[i][j].rgbtGreen = round(blurGreen);
                image[i][j].rgbtBlue = round(blurBlue);
            }

            //Bottom line
            else if (i == (height - 1) && j > 0 && j < (width - 1))
            {
                blurRed += copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed;
                blurRed += copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed;
                blurRed = (blurRed / 6.0);

                blurGreen += copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen;
                blurGreen += copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen;
                blurGreen = (blurGreen / 6.0);

                blurBlue += copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue;
                blurBlue += copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue;
                blurBlue = (blurBlue / 6.0);

                image[i][j].rgbtRed = round(blurRed);
                image[i][j].rgbtGreen = round(blurGreen);
                image[i][j].rgbtBlue = round(blurBlue);
            }

            //Left column
            else if (i > 0 && i < (height - 1) && j == 0)
            {
                blurRed += copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed;
                blurRed += copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed;
                blurRed += copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed;
                blurRed = (blurRed / 6.0);

                blurGreen += copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen;
                blurGreen += copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen;
                blurGreen += copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen;
                blurGreen = (blurGreen / 6.0);

                blurBlue += copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue;
                blurBlue += copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue;
                blurBlue += copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue;
                blurBlue = (blurBlue / 6.0);

                image[i][j].rgbtRed = round(blurRed);
                image[i][j].rgbtGreen = round(blurGreen);
                image[i][j].rgbtBlue = round(blurBlue);

            }

            //Right column
            else if (i > 0 && i < (height - 1) && j == (width - 1))
            {
                blurRed += copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed;
                blurRed += copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed;
                blurRed += copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed;
                blurRed = (blurRed / 6.0);

                blurGreen += copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen;
                blurGreen += copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen;
                blurGreen += copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen;
                blurGreen = (blurGreen / 6.0);

                blurBlue += copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue;
                blurBlue += copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue;
                blurBlue += copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue;
                blurBlue = (blurBlue / 6.0);

                image[i][j].rgbtRed = round(blurRed);
                image[i][j].rgbtGreen = round(blurGreen);
                image[i][j].rgbtBlue = round(blurBlue);
            }

            //Default
            else
            {
                blurRed += copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed;
                blurRed += copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed;
                blurRed += copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed;
                blurRed = (blurRed / 9.0);

                blurGreen += copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen;
                blurGreen += copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen;
                blurGreen += copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen;
                blurGreen = (blurGreen / 9.0);

                blurBlue += copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue;
                blurBlue += copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue;
                blurBlue += copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue;
                blurBlue = (blurBlue / 9.0);

                image[i][j].rgbtRed = round(blurRed);
                image[i][j].rgbtGreen = round(blurGreen);
                image[i][j].rgbtBlue = round(blurBlue);
            }
        }
    }

    return;
}
