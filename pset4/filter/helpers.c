#include "helpers.h"
#include "stdio.h"
#include <math.h>

int calcSepia(float sepiaRed, int originalRed, float sepiaGreen, int originalGreen, float sepiaBlue, int originalBlue)
{
    int sepiaPixelValue = round((sepiaRed * originalRed) + (sepiaGreen * originalGreen) + (sepiaBlue * originalBlue));

    if (sepiaPixelValue < 0)
    {
        sepiaPixelValue = 0;
    }
    else if (sepiaPixelValue > 255)
    {
        sepiaPixelValue = 255;
    }

    return sepiaPixelValue;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate average RGB value to represent it in gray
            float calc = (round(image[i][j].rgbtBlue) + round(image[i][j].rgbtGreen) + round(image[i][j].rgbtRed)) / 3;
            int average = round(calc);

            // assign average to all RGB values
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
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
            // reverse array of pixels to create reflection effect
            RGBTRIPLE pixelCopy = image[i][j];

            image[i][j].rgbtRed = calcSepia(0.393, pixelCopy.rgbtRed, 0.769, pixelCopy.rgbtGreen, 0.189,  pixelCopy.rgbtBlue);
            image[i][j].rgbtGreen = calcSepia(0.349, pixelCopy.rgbtRed, 0.686, pixelCopy.rgbtGreen, 0.168,  pixelCopy.rgbtBlue);
            image[i][j].rgbtBlue = calcSepia(0.272, pixelCopy.rgbtRed, 0.534, pixelCopy.rgbtGreen, 0.131,  pixelCopy.rgbtBlue);
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // reverse array of pixels to create reflection effect
            RGBTRIPLE pixelCopy = image[i][j];

            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = pixelCopy;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pixelCopy[height][width];
    float red = 0.0;
    float green = 0.0;
    float blue = 0.0;

    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            pixelCopy[a][b].rgbtRed = image[a][b].rgbtRed;
            pixelCopy[a][b].rgbtGreen = image[a][b].rgbtGreen;
            pixelCopy[a][b].rgbtBlue = image[a][b].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                // R
                red = (
                    round(pixelCopy[i][j].rgbtRed) +
                    round(pixelCopy[i][j + 1].rgbtRed) +
                    round(pixelCopy[i + 1][j].rgbtRed) +
                    round(pixelCopy[i + 1][j + 1].rgbtRed)
                ) / 4;

                // G
                green = (
                    round(pixelCopy[i][j].rgbtGreen) +
                    round(pixelCopy[i][j + 1].rgbtGreen) +
                    round(pixelCopy[i + 1][j].rgbtGreen) +
                    round(pixelCopy[i + 1][j + 1].rgbtGreen)
                ) / 4;

                // B
                blue = (
                    round(pixelCopy[i][j].rgbtBlue) +
                    round(pixelCopy[i][j + 1].rgbtBlue) +
                    round(pixelCopy[i + 1][j].rgbtBlue) +
                    round(pixelCopy[i + 1][j + 1].rgbtBlue)
                ) / 4;
            }
            else if (i == 0 && j == width - 1)
            {
                // R
                red = (
                    round(pixelCopy[i][j - 1].rgbtRed) +
                    round(pixelCopy[i][j].rgbtRed) +
                    round(pixelCopy[i + 1][j - 1].rgbtRed) +
                    round(pixelCopy[i + 1][j].rgbtRed)
                ) / 4;

                // G
                green = (
                    round(pixelCopy[i][j - 1].rgbtGreen) +
                    round(pixelCopy[i][j].rgbtGreen) +
                    round(pixelCopy[i + 1][j - 1].rgbtGreen) +
                    round(pixelCopy[i + 1][j].rgbtGreen)
                ) / 4;

                // B
                blue = (
                    round(pixelCopy[i][j - 1].rgbtBlue) +
                    round(pixelCopy[i][j].rgbtBlue) +
                    round(pixelCopy[i + 1][j - 1].rgbtBlue) +
                    round(pixelCopy[i + 1][j].rgbtBlue)
                ) / 4;
            }
            else if (i == height - 1 && j == width - 1)
            {
                // R
                red = (
                    round(pixelCopy[i - 1][j - 1].rgbtRed) +
                    round(pixelCopy[i - 1][j].rgbtRed) +
                    round(pixelCopy[i][j - 1].rgbtRed) +
                    round(pixelCopy[i][j].rgbtRed)
                ) / 4;

                // G
                green = (
                    round(pixelCopy[i - 1][j - 1].rgbtGreen) +
                    round(pixelCopy[i - 1][j].rgbtGreen) +
                    round(pixelCopy[i][j - 1].rgbtGreen) +
                    round(pixelCopy[i][j].rgbtGreen)
                ) / 4;

                // B
                blue = (
                    round(pixelCopy[i - 1][j - 1].rgbtBlue) +
                    round(pixelCopy[i - 1][j].rgbtBlue) +
                    round(pixelCopy[i][j - 1].rgbtBlue) +
                    round(pixelCopy[i][j].rgbtBlue)
                ) / 4;
            }
            else if (i == height - 1 && j == 0)
            {
                // R
                red = (
                    round(pixelCopy[i - 1][j].rgbtRed) +
                    round(pixelCopy[i - 1][j + 1].rgbtRed) +
                    round(pixelCopy[i][j].rgbtRed) +
                    round(pixelCopy[i][j + 1].rgbtRed)
                ) / 4;

                // G
                green = (
                    round(pixelCopy[i - 1][j].rgbtGreen) +
                    round(pixelCopy[i - 1][j + 1].rgbtGreen) +
                    round(pixelCopy[i][j].rgbtGreen) +
                    round(pixelCopy[i][j + 1].rgbtGreen)
                ) / 4;

                // B
                blue = (
                    round(pixelCopy[i - 1][j].rgbtBlue) +
                    round(pixelCopy[i - 1][j + 1].rgbtBlue) +
                    round(pixelCopy[i][j].rgbtBlue) +
                    round(pixelCopy[i][j + 1].rgbtBlue)
                ) / 4;
            }
            else if (i == 0 && j != 0)
            {
                // R
                red = (
                    round(pixelCopy[i][j - 1].rgbtRed) +
                    round(pixelCopy[i][j].rgbtRed) +
                    round(pixelCopy[i][j + 1].rgbtRed) +
                    round(pixelCopy[i + 1][j - 1].rgbtRed) +
                    round(pixelCopy[i + 1][j].rgbtRed) +
                    round(pixelCopy[i + 1][j + 1].rgbtRed)
                ) / 6;

                // G
                green = (
                    round(pixelCopy[i][j - 1].rgbtGreen) +
                    round(pixelCopy[i][j].rgbtGreen) +
                    round(pixelCopy[i][j + 1].rgbtGreen) +
                    round(pixelCopy[i + 1][j - 1].rgbtGreen) +
                    round(pixelCopy[i + 1][j].rgbtGreen) +
                    round(pixelCopy[i + 1][j + 1].rgbtGreen)
                ) / 6;

                // B
                blue = (
                    round(pixelCopy[i][j - 1].rgbtBlue) +
                    round(pixelCopy[i][j].rgbtBlue) +
                    round(pixelCopy[i][j + 1].rgbtBlue) +
                    round(pixelCopy[i + 1][j - 1].rgbtBlue) +
                    round(pixelCopy[i + 1][j].rgbtBlue) +
                    round(pixelCopy[i + 1][j + 1].rgbtBlue)
                ) / 6;
            }
            else if (j == 0 && i != 0)
            {
                // R
                red = (
                    round(pixelCopy[i - 1][j].rgbtRed) +
                    round(pixelCopy[i - 1][j + 1].rgbtRed) +
                    round(pixelCopy[i][j].rgbtRed) +
                    round(pixelCopy[i][j + 1].rgbtRed) +
                    round(pixelCopy[i + 1][j].rgbtRed) +
                    round(pixelCopy[i + 1][j + 1].rgbtRed)
                ) / 6;

                // G
                green = (
                    round(pixelCopy[i - 1][j].rgbtGreen) +
                    round(pixelCopy[i - 1][j + 1].rgbtGreen) +
                    round(pixelCopy[i][j].rgbtGreen) +
                    round(pixelCopy[i][j + 1].rgbtGreen) +
                    round(pixelCopy[i + 1][j].rgbtGreen) +
                    round(pixelCopy[i + 1][j + 1].rgbtGreen)
                ) / 6;

                // B
                blue = (
                    round(pixelCopy[i - 1][j].rgbtBlue) +
                    round(pixelCopy[i - 1][j + 1].rgbtBlue) +
                    round(pixelCopy[i][j].rgbtBlue) +
                    round(pixelCopy[i][j + 1].rgbtBlue) +
                    round(pixelCopy[i + 1][j].rgbtBlue) +
                    round(pixelCopy[i + 1][j + 1].rgbtBlue)
                ) / 6;
            }
            else if (i == height - 1 && j != width - 1)
            {
                // R
                red = (
                    round(pixelCopy[i - 1][j - 1].rgbtRed) +
                    round(pixelCopy[i - 1][j].rgbtRed) +
                    round(pixelCopy[i - 1][j + 1].rgbtRed) +
                    round(pixelCopy[i][j - 1].rgbtRed) +
                    round(pixelCopy[i][j].rgbtRed) +
                    round(pixelCopy[i][j + 1].rgbtRed)
                ) / 6;

                // G
                green = (
                    round(pixelCopy[i - 1][j - 1].rgbtGreen) +
                    round(pixelCopy[i - 1][j].rgbtGreen) +
                    round(pixelCopy[i - 1][j + 1].rgbtGreen) +
                    round(pixelCopy[i][j - 1].rgbtGreen) +
                    round(pixelCopy[i][j].rgbtGreen) +
                    round(pixelCopy[i][j + 1].rgbtGreen)
                ) / 6;

                // B
                blue = (
                    round(pixelCopy[i - 1][j - 1].rgbtBlue) +
                    round(pixelCopy[i - 1][j].rgbtBlue) +
                    round(pixelCopy[i - 1][j + 1].rgbtBlue) +
                    round(pixelCopy[i][j - 1].rgbtBlue) +
                    round(pixelCopy[i][j].rgbtBlue) +
                    round(pixelCopy[i][j + 1].rgbtBlue)
                ) / 6;
            }
            else if (j == width - 1 && i != height - 1)
            {
                // R
                red = (
                    round(pixelCopy[i - 1][j - 1].rgbtRed) +
                    round(pixelCopy[i - 1][j].rgbtRed) +
                    round(pixelCopy[i][j - 1].rgbtRed) +
                    round(pixelCopy[i][j].rgbtRed) +
                    round(pixelCopy[i + 1][j - 1].rgbtRed) +
                    round(pixelCopy[i + 1][j].rgbtRed)
                ) / 6;

                // G
                green = (
                    round(pixelCopy[i - 1][j - 1].rgbtGreen) +
                    round(pixelCopy[i - 1][j].rgbtGreen) +
                    round(pixelCopy[i][j - 1].rgbtGreen) +
                    round(pixelCopy[i][j].rgbtGreen) +
                    round(pixelCopy[i + 1][j - 1].rgbtGreen) +
                    round(pixelCopy[i + 1][j].rgbtGreen)
                ) / 6;

                // B
                blue = (
                    round(pixelCopy[i - 1][j - 1].rgbtBlue) +
                    round(pixelCopy[i - 1][j].rgbtBlue) +
                    round(pixelCopy[i][j - 1].rgbtBlue) +
                    round(pixelCopy[i][j].rgbtBlue) +
                    round(pixelCopy[i + 1][j - 1].rgbtBlue) +
                    round(pixelCopy[i + 1][j].rgbtBlue)
                ) / 6;
            }
            else
            {
                // R
                red = (
                    round(pixelCopy[i - 1][j - 1].rgbtRed) +
                    round(pixelCopy[i - 1][j].rgbtRed) +
                    round(pixelCopy[i - 1][j + 1].rgbtRed) +
                    round(pixelCopy[i][j - 1].rgbtRed) +
                    round(pixelCopy[i][j].rgbtRed) +
                    round(pixelCopy[i][j + 1].rgbtRed) +
                    round(pixelCopy[i + 1][j - 1].rgbtRed) +
                    round(pixelCopy[i + 1][j].rgbtRed) +
                    round(pixelCopy[i + 1][j + 1].rgbtRed)
                ) / 9;

                // G
                green = (
                    round(pixelCopy[i - 1][j - 1].rgbtGreen) +
                    round(pixelCopy[i - 1][j].rgbtGreen) +
                    round(pixelCopy[i - 1][j + 1].rgbtGreen) +
                    round(pixelCopy[i][j - 1].rgbtGreen) +
                    round(pixelCopy[i][j].rgbtGreen) +
                    round(pixelCopy[i][j + 1].rgbtGreen) +
                    round(pixelCopy[i + 1][j - 1].rgbtGreen) +
                    round(pixelCopy[i + 1][j].rgbtGreen) +
                    round(pixelCopy[i + 1][j + 1].rgbtGreen)
                ) / 9;

                // B
                blue = (
                    round(pixelCopy[i - 1][j - 1].rgbtBlue) +
                    round(pixelCopy[i - 1][j].rgbtBlue) +
                    round(pixelCopy[i - 1][j + 1].rgbtBlue) +
                    round(pixelCopy[i][j - 1].rgbtBlue) +
                    round(pixelCopy[i][j].rgbtBlue) +
                    round(pixelCopy[i][j + 1].rgbtBlue) +
                    round(pixelCopy[i + 1][j - 1].rgbtBlue) +
                    round(pixelCopy[i + 1][j].rgbtBlue) +
                    round(pixelCopy[i + 1][j + 1].rgbtBlue)
                ) / 9;
            }

            image[i][j].rgbtRed = round(red);
            image[i][j].rgbtGreen = round(green);
            image[i][j].rgbtBlue = round(blue);
        }
    }

    return;
}
