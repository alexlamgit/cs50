#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void apply_Gx(int postion, int *sumRx, int *sumGx, int *sumBx, RGBTRIPLE pixel);
void apply_Gy(int postion, int *sumRy, int *sumGy, int *sumBy, RGBTRIPLE pixel);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        {
            for (int j = 0; j < width; j++)
            {
                BYTE average = (BYTE)round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);

                image[i][j].rgbtRed = average;
                image[i][j].rgbtGreen = average;
                image[i][j].rgbtBlue = average;
            }
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        {
            for (int j = 0; j < width; j++)
            {
                BYTE redByte = image[i][j].rgbtRed;
                BYTE greenByte = image[i][j].rgbtGreen;
                BYTE blueByte = image[i][j].rgbtBlue;

                // Sepia array for SepiaRed, SepiaGreen and SepiaBlue values respectively in order
                double sepia_ints[3];

                sepia_ints[0] = round(redByte * 0.393 + greenByte * 0.769 + 0.189 * blueByte);
                sepia_ints[1] = round(redByte * 0.349 + greenByte * 0.686 + 0.168 * blueByte);
                sepia_ints[2] = round(redByte * 0.272 + greenByte * 0.534 + 0.131 * blueByte);

                // Make sure value isn't over 255
                for (int k = 0; k < 3; k++)
                {
                    if (sepia_ints[k] > 255)
                    {
                        sepia_ints[k] = 255;
                    }
                }

                image[i][j].rgbtRed = (BYTE) sepia_ints[0];
                image[i][j].rgbtGreen = (BYTE) sepia_ints[1];
                image[i][j].rgbtBlue = (BYTE) sepia_ints[2];
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int middle = (int) width / 2;
    for (int i = 0; i < height; i++)
    {
        {
            for (int j = 0; j < width; j++)
            {
                // To make sure not to cpy the same information again
                if (j < middle)
                {
                    RGBTRIPLE temp = image[i][j];
                    image[i][j] = image[i][width - (j + 1)];
                    image[i][width - (j + 1)] = temp;
                }
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];

    for (int f = 0; f < height; f++)
    {
        for (int u = 0; u < width; u++)
        {
            // Copy image so that the k & l loop doesn't calculate values from an already modified pixel
            image_copy[f][u] = image[f][u];
        }
    }

    for (int i = 0; i < height; i++)
    {
        {
            for (int j = 0; j < width; j++)
            {
                // Sums of rgb values of all pixels part of the subgroup
                int sumR = 0;
                int sumG = 0;
                int sumB = 0;

                //Max widths and heights for the upcoming loops
                int maxh = (i == (height - 1) ? i : i + 1);
                int maxw = (j == (width - 1) ? j : j + 1);

                // Number of pixels that were added in the average
                double denominator = 0;

                /* Loops to iterate over the values that are no further than
                   1 array index in any direction from the origin */
                for (int k = (i == 0) ? i : i - 1; k <= maxh; k++)
                {
                    for (int l = (j == 0) ? j : j - 1; l <= maxw; l++)
                    {
                        {
                            sumR += image_copy[k][l].rgbtRed;
                            sumG += image_copy[k][l].rgbtGreen;
                            sumB += image_copy[k][l].rgbtBlue;
                            denominator++;
                        }
                    }
                }

                // Averages of each color values assigned to the pixels
                image[i][j].rgbtRed = (BYTE) round(sumR / denominator);
                image[i][j].rgbtGreen = (BYTE) round(sumG / denominator);
                image[i][j].rgbtBlue = (BYTE) round(sumB / denominator);
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];

    for (int f = 0; f < height; f++)
    {
        for (int u = 0; u < width; u++)
        {
            // Copy image so that the k & l loop doesn't calculate values from an already modified pixel
            image_copy[f][u] = image[f][u];
        }
    }

    for (int i = 0; i < height; i++)
    {
        {
            for (int j = 0; j < width; j++)
            {
                /*
                    Sums of rgb values of all pixels part of the subgroup
                    after Gx convolution matrix
                */
                int sumRx = 0;
                int sumGx = 0;
                int sumBx = 0;

                /*
                    Sums of rgb values of all pixels part of the subgroup
                    after Gy convolution matrix
                */
                int sumRy = 0;
                int sumGy = 0;
                int sumBy = 0;

                // Position in the subarray around the value at (i, j)
                int position = 0;

                /*
                    Loops to iterate over the values that are no further than
                    1 array index in any direction from the origin
                */
                for (int k = i - 1; k <= i + 1; k++)
                {
                    for (int l = j - 1; l <= j + 1; l++)
                    {
                        // Current pixel which will be passed to Gx and Gy functions
                        RGBTRIPLE pixel;

                        // If current pixel is out of bounds, RGB values = 0
                        if (k > (height - 1) || l > (width - 1) || k < 0 || l < 0)
                        {
                            pixel.rgbtRed = 0;
                            pixel.rgbtGreen = 0;
                            pixel.rgbtBlue = 0;
                        }
                        else
                        {
                            pixel.rgbtRed = image_copy[k][l].rgbtRed;
                            pixel.rgbtGreen = image_copy[k][l].rgbtGreen;
                            pixel.rgbtBlue = image_copy[k][l].rgbtBlue;
                        }

                        // Applying Gx and Gy convolution matrices
                        apply_Gx(position, &sumRx, &sumGx, &sumBx, pixel);
                        apply_Gy(position, &sumRy, &sumGy, &sumBy, pixel);

                        position++;
                    }
                }

                // Final colour values for each subpixel
                double f_valR = sqrt((sumRx * sumRx) + (sumRy * sumRy));
                double f_valG = sqrt((sumGx * sumGx) + (sumGy * sumGy));
                double f_valB = sqrt((sumBx * sumBx) + (sumBy * sumBy));

                double f_vals[3] = {f_valR, f_valG, f_valB};

                // Cap values at 255
                for (int s = 0; s < 3; s++)
                {
                    if (f_vals[s] > 255)
                    {
                        f_vals[s] = 255;
                    }
                }

                // Weighted sums assigned to each of the pixels
                image[i][j].rgbtRed = (BYTE) round(f_vals[0]);
                image[i][j].rgbtGreen = (BYTE) round(f_vals[1]);
                image[i][j].rgbtBlue = (BYTE) round(f_vals[2]);
            }
        }
    }
    return;
}

void apply_Gx(int position, int *sumRx, int *sumGx, int *sumBx, RGBTRIPLE pixel)
{
    /*
        See Gx matrix in pset4 description.
        Could have used a switch but I believe its
        better with if statements.
    */
    if (position == 0 || position == 6)
    {
        *sumRx += pixel.rgbtRed * -1;
        *sumGx += pixel.rgbtGreen * -1;
        *sumBx += pixel.rgbtBlue * -1;
    }
    if (position == 2 || position == 8)
    {
        *sumRx += pixel.rgbtRed;
        *sumGx += pixel.rgbtGreen;
        *sumBx += pixel.rgbtBlue;
    }
    if (position == 3)
    {
        *sumRx += pixel.rgbtRed * -2;
        *sumGx += pixel.rgbtGreen * -2;
        *sumBx += pixel.rgbtBlue * -2;
    }
    if (position == 5)
    {
        *sumRx += pixel.rgbtRed * 2;
        *sumGx += pixel.rgbtGreen * 2;
        *sumBx += pixel.rgbtBlue * 2;
    }
    return;
}

void apply_Gy(int position, int *sumRy, int *sumGy, int *sumBy, RGBTRIPLE pixel)
{
    if (position == 0 || position == 2)
    {
        *sumRy += pixel.rgbtRed * -1;
        *sumGy += pixel.rgbtGreen * -1;
        *sumBy += pixel.rgbtBlue * -1;
    }
    if (position == 6 || position == 8)
    {
        *sumRy += pixel.rgbtRed;
        *sumGy += pixel.rgbtGreen;
        *sumBy += pixel.rgbtBlue;
    }
    if (position == 1)
    {
        *sumRy += pixel.rgbtRed * -2;
        *sumGy += pixel.rgbtGreen * -2;
        *sumBy += pixel.rgbtBlue * -2;
    }
    if (position == 7)
    {
        *sumRy += pixel.rgbtRed * 2;
        *sumGy += pixel.rgbtGreen * 2;
        *sumBy += pixel.rgbtBlue * 2;
    }
    return;
}
