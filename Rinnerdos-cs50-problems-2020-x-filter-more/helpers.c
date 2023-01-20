#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avgByte = (float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
            image[i][j].rgbtRed = round(avgByte);
            image[i][j].rgbtGreen = round(avgByte);
            image[i][j].rgbtBlue = round(avgByte);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            BYTE tempByteRed = image[i][j].rgbtRed;
            BYTE tempByteGreen = image[i][j].rgbtGreen;
            BYTE tempByteBlue = image[i][j].rgbtBlue;
            
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = tempByteRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = tempByteGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = tempByteBlue;
            
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copyImage[height][width];
    /*
    for (int i = 0; i < height - 1; i++)
    {
        for (int j = 0; j < height - 1; j++)
        {
            originalImage[i][j] = image[i][j];
        }
    }
    */
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sumRed = 0;
            float sumGreen = 0;
            float sumBlue = 0;
            int count = 0;
            
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    
                    // If k or l out of bounds, iterate if under lower bound, break if over upper bound.
                    if (k < 0)
                    {
                        k++;
                    }
                    if (l < 0)
                    {
                        l++;
                    }
                    
                    if (k == height)
                    {
                        break;
                    }
                    if (l == width)
                    {
                        break;
                    }
                    sumRed += image[k][l].rgbtRed;
                    sumGreen += image[k][l].rgbtGreen;
                    sumBlue += image[k][l].rgbtBlue;
                    count++;
                }
            }
            copyImage[i][j].rgbtRed = round(sumRed / count);
            copyImage[i][j].rgbtGreen = round(sumGreen / count);
            copyImage[i][j].rgbtBlue = round(sumBlue / count);
        }
    }
    // Copy the blurred image to original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[i][j] = copyImage[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copyImage[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Create two 2D-arrays with the gx and gy values (Sobel operators), for handy multiplication later
            float gx[3][3] = 
            {
                {-1, 0, 1},
                {-2, 0, 2},
                {-1, 0, 1}
            };
            float gy[3][3] = 
            {
                {-1, -2, -1},
                {0, 0, 0},
                {1, 2, 1}
            };
            
            float gxRedSum = 0;
            float gyRedSum = 0;
            float gxGreenSum = 0;
            float gyGreenSum = 0;
            float gxBlueSum = 0;
            float gyBlueSum = 0;
            
            int yCount = 0;
            
            for (int k = i - 1; k < i + 2; k++)
            {
                int xCount = 0;
                
                for (int l = j - 1; l < j + 2; l++)
                {
                    if (!(l < 0 || k < 0 || k > height - 1 || l > width - 1))
                    {
                        gxRedSum += gx[xCount][yCount] * image[k][l].rgbtRed;
                        gyRedSum += gy[xCount][yCount] * image[k][l].rgbtRed;
                        gxGreenSum += gx[xCount][yCount] * image[k][l].rgbtGreen;
                        gyGreenSum += gy[xCount][yCount] * image[k][l].rgbtGreen;
                        gxBlueSum += gx[xCount][yCount] * image[k][l].rgbtBlue;
                        gyBlueSum += gy[xCount][yCount] * image[k][l].rgbtBlue;
                    }
                    
                    xCount++;
                }
                yCount++;
            }
            float gxRedAvg = sqrt((gxRedSum * gxRedSum) + (gyRedSum * gyRedSum));
            float gxGreenAvg = sqrt((gxGreenSum * gxGreenSum) + (gyGreenSum * gyGreenSum));
            float gxBlueAvg = sqrt((gxBlueSum * gxBlueSum) + (gyBlueSum * gyBlueSum));
            
            if (gxRedAvg >= 255)
            {
                copyImage[i][j].rgbtRed = 255;
            }
            else
            {
                copyImage[i][j].rgbtRed = round(gxRedAvg);
            }
            
            if (gxGreenAvg >= 255)
            {
                copyImage[i][j].rgbtGreen = 255;
            }
            else
            {
                copyImage[i][j].rgbtGreen = round(gxGreenAvg);
            }
            
            if (gxBlueAvg >= 255)
            {
                copyImage[i][j].rgbtBlue = 255;
            }
            else
            {
                copyImage[i][j].rgbtBlue = round(gxBlueAvg);
            }
        }
    }
    // Copy the edge image to original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[i][j] = copyImage[i][j];
        }
    }
    return;
}
