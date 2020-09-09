#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redPixels = image[i][j].rgbtRed;
            int greenPixels = image[i][j].rgbtGreen;
            int bluePixels = image[i][j].rgbtBlue;
            double average = (double)(redPixels + greenPixels + bluePixels) / 3.0; //finds average of RGB pixels
            int averagePixel = round(average);
            image[i][j].rgbtRed = averagePixel;
            image[i][j].rgbtGreen = averagePixel;
            image[i][j].rgbtBlue = averagePixel;  //makes each of the RGB pixels the average value
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redPixels = image[i][j].rgbtRed;
            int greenPixels = image[i][j].rgbtGreen;
            int bluePixels = image[i][j].rgbtBlue;
            double sepiaRedPix = (0.393 * redPixels) + (0.769 * greenPixels) + (0.189 * bluePixels);
            double sepiaGreenPix = (0.349 * redPixels) + (0.686 * greenPixels) + (0.168 * bluePixels);
            double sepiaBluePix = (0.272 * redPixels) + (0.534 * greenPixels) + (0.131 * bluePixels); //calculates sepia values for RGB
            int sepiaRedPixels = round(sepiaRedPix);
            int sepiaGreenPixels = round(sepiaGreenPix);
            int sepiaBluePixels = round(sepiaBluePix);
            if (sepiaRedPixels >= 0 && sepiaRedPixels <= 255) //handles if RGB sepia values need to be capped at 255
            {
                image[i][j].rgbtRed = sepiaRedPixels;
            }
            else if (sepiaRedPixels > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            if (sepiaGreenPixels >= 0 && sepiaGreenPixels <= 255)
            {
                image[i][j].rgbtGreen = sepiaGreenPixels;
            }
            else if (sepiaGreenPixels > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            if (sepiaBluePixels >= 0 && sepiaBluePixels <= 255)
            {
                image[i][j].rgbtBlue = sepiaBluePixels;
            }
            else if (sepiaBluePixels > 255)
            {
                image[i][j].rgbtBlue = 255;
            }

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //for each row in the second for loop start at i and up to half; swap right and left; use k = width and decrement
    for (int i = 0; i < height; i++)
    {
        int k = width - 1;
        for (int j = 0; j < (width / 2); j++)
        {
            int tempRed = image[i][j].rgbtRed;    //swapping algorithm from lecture 4
            int tempGreen = image[i][j].rgbtGreen;
            int tempBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = image[i][k].rgbtRed;
            image[i][j].rgbtGreen = image[i][k].rgbtGreen;
            image[i][j].rgbtBlue = image[i][k].rgbtBlue;
            image[i][k].rgbtRed = tempRed;
            image[i][k].rgbtGreen = tempGreen;
            image[i][k].rgbtBlue = tempBlue;
            k--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE tempImage[height][width]; //creates a copy of the image

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redPixels = 0;
            int greenPixels = 0;
            int bluePixels = 0;
            double counter = 0.0;
            for (int c = -1; c < 2; c++)
            {
                for (int d = -1; d < 2; d++)
                {
                    if (i + c < 0 || i + c >= height || j + d < 0 || j + d >= width) //handles if pixels are on the edges
                    {
                        continue;
                    }
                    redPixels += image[i + c][j + d].rgbtRed;
                    greenPixels += image[i + c][j + d].rgbtGreen;
                    bluePixels += image[i + c][j + d].rgbtBlue;
                    counter++;   //calculates pixel values for RBG and counts number of pixels used for calculation
                }
            }

            tempImage[i][j].rgbtRed = round(redPixels / counter);
            tempImage[i][j].rgbtGreen = round(greenPixels / counter);
            tempImage[i][j].rgbtBlue = round(bluePixels / counter);

        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tempImage[i][j].rgbtRed;   //copies values from the temp into actual image
            image[i][j].rgbtGreen = tempImage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tempImage[i][j].rgbtBlue;
        }
    }
    return;
}
