#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int rgbAverage = (image[h][w].rgbtBlue + image[h][w].rgbtRed + image[h][w].rgbtGreen) / 3.0 + 0.5;
            image[h][w].rgbtBlue = rgbAverage;
            image[h][w].rgbtRed = rgbAverage;
            image[h][w].rgbtGreen = rgbAverage;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Declare BYTEs for swapping values in the image
    BYTE tempR, tempB, tempG;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {
            tempR = image[h][w].rgbtRed;
            tempB = image[h][w].rgbtBlue;
            tempG = image[h][w].rgbtGreen;

            image[h][w].rgbtRed = image[h][width - w - 1].rgbtRed;
            image[h][w].rgbtBlue = image[h][width - w - 1].rgbtBlue;
            image[h][w].rgbtGreen = image[h][width - w - 1].rgbtGreen;

            image[h][width - w - 1].rgbtRed = tempR;
            image[h][width - w - 1].rgbtBlue = tempB;
            image[h][width - w - 1].rgbtGreen = tempG;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a dummy RGBTRIPLE with which to initialize newImage
    RGBTRIPLE temp;
    temp.rgbtRed = 0;
    temp.rgbtBlue = 0;
    temp.rgbtGreen = 0;

    // Declare newImage with the same dimensions as that given
    RGBTRIPLE newImage[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int j = 0; j < width; j++)
        {
            newImage[h][j] = temp;
        }
    }

    // Cycle through all the pixels in the image,
    // check if the pixel (h, w) is an edge or a corner,
    // and appropriately sum the values for each color for all the pixels surrounding pixel (h, w)
    int sumR, sumB, sumG;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            sumR = image[h][w].rgbtRed;
            sumB = image[h][w].rgbtBlue;
            sumG = image[h][w].rgbtGreen;

            float counter = 1.0;

            if (h == 0)
            {
                sumR += image[h + 1][w].rgbtRed;
                sumB += image[h + 1][w].rgbtBlue;
                sumG += image[h + 1][w].rgbtGreen;

                counter++;

                if (w == 0)
                {
                    sumR += image[h][w + 1].rgbtRed;
                    sumB += image[h][w + 1].rgbtBlue;
                    sumG += image[h][w + 1].rgbtGreen;

                    sumR += image[h + 1][w + 1].rgbtRed;
                    sumB += image[h + 1][w + 1].rgbtBlue;
                    sumG += image[h + 1][w + 1].rgbtGreen;

                    counter += 2;
                }
                else if (w == width - 1)
                {
                    sumR += image[h][w - 1].rgbtRed;
                    sumB += image[h][w - 1].rgbtBlue;
                    sumG += image[h][w - 1].rgbtGreen;

                    sumR += image[h + 1][w - 1].rgbtRed;
                    sumB += image[h + 1][w - 1].rgbtBlue;
                    sumG += image[h + 1][w - 1].rgbtGreen;

                    counter += 2;
                }
                else
                {
                    sumR += image[h][w + 1].rgbtRed;
                    sumB += image[h][w + 1].rgbtBlue;
                    sumG += image[h][w + 1].rgbtGreen;

                    sumR += image[h + 1][w + 1].rgbtRed;
                    sumB += image[h + 1][w + 1].rgbtBlue;
                    sumG += image[h + 1][w + 1].rgbtGreen;

                    sumR += image[h][w - 1].rgbtRed;
                    sumB += image[h][w - 1].rgbtBlue;
                    sumG += image[h][w - 1].rgbtGreen;

                    sumR += image[h + 1][w - 1].rgbtRed;
                    sumB += image[h + 1][w - 1].rgbtBlue;
                    sumG += image[h + 1][w - 1].rgbtGreen;

                    counter += 4;
                }
            }
            else if (h == height - 1)
            {
                sumR += image[h - 1][w].rgbtRed;
                sumB += image[h - 1][w].rgbtBlue;
                sumG += image[h - 1][w].rgbtGreen;

                counter++;

                if (w == 0)
                {
                    sumR += image[h][w + 1].rgbtRed;
                    sumB += image[h][w + 1].rgbtBlue;
                    sumG += image[h][w + 1].rgbtGreen;

                    sumR += image[h - 1][w + 1].rgbtRed;
                    sumB += image[h - 1][w + 1].rgbtBlue;
                    sumG += image[h - 1][w + 1].rgbtGreen;

                    counter += 2;
                }
                else if (w == width - 1)
                {
                    sumR += image[h][w - 1].rgbtRed;
                    sumB += image[h][w - 1].rgbtBlue;
                    sumG += image[h][w - 1].rgbtGreen;

                    sumR += image[h - 1][w - 1].rgbtRed;
                    sumB += image[h - 1][w - 1].rgbtBlue;
                    sumG += image[h - 1][w - 1].rgbtGreen;

                    counter += 2;
                }
                else
                {
                    sumR += image[h][w + 1].rgbtRed;
                    sumB += image[h][w + 1].rgbtBlue;
                    sumG += image[h][w + 1].rgbtGreen;

                    sumR += image[h - 1][w + 1].rgbtRed;
                    sumB += image[h - 1][w + 1].rgbtBlue;
                    sumG += image[h - 1][w + 1].rgbtGreen;

                    sumR += image[h][w - 1].rgbtRed;
                    sumB += image[h][w - 1].rgbtBlue;
                    sumG += image[h][w - 1].rgbtGreen;

                    sumR += image[h - 1][w - 1].rgbtRed;
                    sumB += image[h - 1][w - 1].rgbtBlue;
                    sumG += image[h - 1][w - 1].rgbtGreen;

                    counter += 4;
                }
            }
            else if (w == 0)
            {
                sumR += image[h][w + 1].rgbtRed;
                sumB += image[h][w + 1].rgbtBlue;
                sumG += image[h][w + 1].rgbtGreen;

                sumR += image[h + 1][w].rgbtRed;
                sumB += image[h + 1][w].rgbtBlue;
                sumG += image[h + 1][w].rgbtGreen;

                sumR += image[h + 1][w + 1].rgbtRed;
                sumB += image[h + 1][w + 1].rgbtBlue;
                sumG += image[h + 1][w + 1].rgbtGreen;

                sumR += image[h - 1][w].rgbtRed;
                sumB += image[h - 1][w].rgbtBlue;
                sumG += image[h - 1][w].rgbtGreen;

                sumR += image[h - 1][w + 1].rgbtRed;
                sumB += image[h - 1][w + 1].rgbtBlue;
                sumG += image[h - 1][w + 1].rgbtGreen;

                counter += 5;
            }
            else if (w == width - 1)
            {
                sumR += image[h][w - 1].rgbtRed;
                sumB += image[h][w - 1].rgbtBlue;
                sumG += image[h][w - 1].rgbtGreen;

                sumR += image[h + 1][w].rgbtRed;
                sumB += image[h + 1][w].rgbtBlue;
                sumG += image[h + 1][w].rgbtGreen;

                sumR += image[h + 1][w - 1].rgbtRed;
                sumB += image[h + 1][w - 1].rgbtBlue;
                sumG += image[h + 1][w - 1].rgbtGreen;

                sumR += image[h - 1][w].rgbtRed;
                sumB += image[h - 1][w].rgbtBlue;
                sumG += image[h - 1][w].rgbtGreen;

                sumR += image[h - 1][w - 1].rgbtRed;
                sumB += image[h - 1][w - 1].rgbtBlue;
                sumG += image[h - 1][w - 1].rgbtGreen;

                counter += 5;
            }
            else
            {
                sumR += image[h][w + 1].rgbtRed;
                sumB += image[h][w + 1].rgbtBlue;
                sumG += image[h][w + 1].rgbtGreen;

                sumR += image[h][w - 1].rgbtRed;
                sumB += image[h][w - 1].rgbtBlue;
                sumG += image[h][w - 1].rgbtGreen;

                sumR += image[h + 1][w].rgbtRed;
                sumB += image[h + 1][w].rgbtBlue;
                sumG += image[h + 1][w].rgbtGreen;

                sumR += image[h + 1][w + 1].rgbtRed;
                sumB += image[h + 1][w + 1].rgbtBlue;
                sumG += image[h + 1][w + 1].rgbtGreen;

                sumR += image[h + 1][w - 1].rgbtRed;
                sumB += image[h + 1][w - 1].rgbtBlue;
                sumG += image[h + 1][w - 1].rgbtGreen;

                sumR += image[h - 1][w].rgbtRed;
                sumB += image[h - 1][w].rgbtBlue;
                sumG += image[h - 1][w].rgbtGreen;

                sumR += image[h - 1][w + 1].rgbtRed;
                sumB += image[h - 1][w + 1].rgbtBlue;
                sumG += image[h - 1][w + 1].rgbtGreen;

                sumR += image[h - 1][w - 1].rgbtRed;
                sumB += image[h - 1][w - 1].rgbtBlue;
                sumG += image[h - 1][w - 1].rgbtGreen;

                counter += 8;
            }

            // Set the red, blue, and green components of the pixel (h, w) in newImage
            // to the average of the pixels surrounding it (including itself)
            newImage[h][w].rgbtRed = (int) sumR / counter + 0.5;
            newImage[h][w].rgbtBlue = (int) sumB / counter + 0.5;
            newImage[h][w].rgbtGreen = (int) sumG / counter + 0.5;
        }
    }

    // Map newImage to that given (image)
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = newImage[h][w];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a dummy RGBTRIPLE with which to initialize newImage
    RGBTRIPLE temp;
    temp.rgbtRed = 0;
    temp.rgbtBlue = 0;
    temp.rgbtGreen = 0;

    // Declare newImage with the same dimensions as that given
    RGBTRIPLE newImage[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int j = 0; j < width; j++)
        {
            newImage[h][j] = temp;
        }
    }

    // Declare three int matrices to hold the values of the red, green, and blue components
    // of the pixels in the 3x3 box surrounding pixel (h, w)
    int red[3][3] = {0}, blue[3][3] = {0}, green[3][3] = {0};

    // Cycle through all the pixels in the image,
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Initialize red, green, and blue matrices with all zeroes
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    red[i][j] = 0;
                    blue[i][j] = 0;
                    green[i][j] = 0;
                }
            }

            // Check to see if the current pixel (h, w) is a corner or on the edge of the image,
            // and then assign values to the red, blue, and green matrices
            if (h == 0)
            {
                if (w == 0)
                {
                    for (int i = 1; i < 3; i++)
                    {
                        for (int j = 1; j < 3; j++)
                        {
                            red[i][j] = image[h + i - 1][w + j - 1].rgbtRed;
                            blue[i][j] = image[h + i - 1][w + j - 1].rgbtBlue;
                            green[i][j] = image[h + i - 1][w + j - 1].rgbtGreen;
                        }
                    }
                }
                else if (w == width - 1)
                {
                    for (int i = 1; i < 3; i++)
                    {
                        for (int j = 0; j < 2; j++)
                        {
                            red[i][j] = image[h + i - 1][w + j - 1].rgbtRed;
                            blue[i][j] = image[h + i - 1][w + j - 1].rgbtBlue;
                            green[i][j] = image[h + i - 1][w + j - 1].rgbtGreen;
                        }
                    }
                }
                else
                {
                    for (int i = 1; i < 3; i++)
                    {
                        for (int j = 0; j < 3; j++)
                        {
                            red[i][j] = image[h + i - 1][w + j - 1].rgbtRed;
                            blue[i][j] = image[h + i - 1][w + j - 1].rgbtBlue;
                            green[i][j] = image[h + i - 1][w + j - 1].rgbtGreen;
                        }
                    }
                }
            }
            else if (h == height - 1)
            {
                if (w == 0)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        for (int j = 1; j < 3; j++)
                        {
                            red[i][j] = image[h + i - 1][w + j - 1].rgbtRed;
                            blue[i][j] = image[h + i - 1][w + j - 1].rgbtBlue;
                            green[i][j] = image[h + i - 1][w + j - 1].rgbtGreen;
                        }
                    }
                }
                else if (w == width - 1)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        for (int j = 0; j < 2; j++)
                        {
                            red[i][j] = image[h + i - 1][w + j - 1].rgbtRed;
                            blue[i][j] = image[h + i - 1][w + j - 1].rgbtBlue;
                            green[i][j] = image[h + i - 1][w + j - 1].rgbtGreen;
                        }
                    }
                }
                else
                {
                    for (int i = 0; i < 2; i++)
                    {
                        for (int j = 0; j < 3; j++)
                        {
                            red[i][j] = image[h + i - 1][w + j - 1].rgbtRed;
                            blue[i][j] = image[h + i - 1][w + j - 1].rgbtBlue;
                            green[i][j] = image[h + i - 1][w + j - 1].rgbtGreen;
                        }
                    }
                }
            }
            else if (w == 0)
            {
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 1; j < 3; j++)
                    {
                        red[i][j] = image[h + i - 1][w + j - 1].rgbtRed;
                        blue[i][j] = image[h + i - 1][w + j - 1].rgbtBlue;
                        green[i][j] = image[h + i - 1][w + j - 1].rgbtGreen;
                    }
                }
            }
            else if (w == width - 1)
            {
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        red[i][j] = image[h + i - 1][w + j - 1].rgbtRed;
                        blue[i][j] = image[h + i - 1][w + j - 1].rgbtBlue;
                        green[i][j] = image[h + i - 1][w + j - 1].rgbtGreen;
                    }
                }
            }
            else
            {
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        red[i][j] = image[h + i - 1][w + j - 1].rgbtRed;
                        blue[i][j] = image[h + i - 1][w + j - 1].rgbtBlue;
                        green[i][j] = image[h + i - 1][w + j - 1].rgbtGreen;
                    }
                }
            }

            // Define matrices for Gx and Gy
            int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

            // Multiply each entry in the red[][], blue[][], and green[][] matrices by the corresponding matrix in Gx and Gy,
            // and then sum these products.
            float sumGxRed = 0, sumGxBlue = 0, sumGxGreen = 0;
            float sumGyRed = 0, sumGyBlue = 0, sumGyGreen = 0;

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    sumGxRed += red[i][j] * Gx[i][j];
                    sumGyRed += red[i][j] * Gy[i][j];

                    sumGxBlue += blue[i][j] * Gx[i][j];
                    sumGyBlue += blue[i][j] * Gy[i][j];

                    sumGxGreen += green[i][j] * Gx[i][j];
                    sumGyGreen += green[i][j] * Gy[i][j];
                }
            }

            // Find Gx^2 + Gy^2, check to see if it is greater than 0xff, and then assign
            // the correct value to the pixel (h, w) in newImage
            if (sqrtf(sumGxRed * sumGxRed + sumGyRed * sumGyRed) > 255)
            {
                newImage[h][w].rgbtRed = 255;
            }
            else
            {
                newImage[h][w].rgbtRed = (int) (sqrtf(sumGxRed * sumGxRed + sumGyRed * sumGyRed) + 0.5);
            }

            if (sqrtf(sumGxBlue * sumGxBlue + sumGyBlue * sumGyBlue) > 255)
            {
                newImage[h][w].rgbtBlue = 255;
            }
            else
            {
                newImage[h][w].rgbtBlue = (int) (sqrtf(sumGxBlue * sumGxBlue + sumGyBlue * sumGyBlue) + 0.5);
            }

            if (sqrtf(sumGxGreen * sumGxGreen + sumGyGreen * sumGyGreen) > 255)
            {
                newImage[h][w].rgbtGreen = 255;
            }
            else
            {
                newImage[h][w].rgbtGreen = (int) (sqrtf(sumGxGreen * sumGxGreen + sumGyGreen * sumGyGreen) + 0.5);
            }
        }
    }

    // Map newImage to that given (image)
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = newImage[h][w];
        }
    }

    return;
}
