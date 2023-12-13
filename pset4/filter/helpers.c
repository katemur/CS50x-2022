#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //finding average value of colors
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = (int)average;
            image[i][j].rgbtGreen = (int)average;
            image[i][j].rgbtBlue = (int)average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // for images with even width
        if (width % 2 == 0)
        {
            for (int j = 0; j < width / 2; j++)
            {
                RGBTRIPLE buffer;
                buffer = image[i][j];
                image[i][j] = image[i][width - 1 - j];
                image[i][width - 1 - j] = buffer;
            }
        }
        else
        {
            // for images with uneven width
            for (int j = 0; j <= width / 2; j++)
            {
                //for a pixel in the middle
                if (j == width / 2)
                {
                    image[i][j] = image[i][j];
                }
                else
                {
                    RGBTRIPLE buffer;
                    buffer = image[i][j];
                    image[i][j] = image[i][width - 1 - j];
                    image[i][width - 1 - j] = buffer;
                }

            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // creating a buffer if the same size
    RGBTRIPLE buffer[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // for pixels in the middle
            if ((i != 0) && (j != 0) && (i != height - 1) && (j != width - 1))
            {
                int blurRed = lround((image[i][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                      image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j +
                                              1].rgbtRed) / 9.0);
                int blurGreen = lround((image[i][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j +
                                        1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                        image[i + 1][j + 1].rgbtGreen) / 9.0);
                int blurBlue = lround((image[i][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue
                                       + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j +
                                               1].rgbtBlue) / 9.0);
                buffer[i][j].rgbtRed = blurRed;
                buffer[i][j].rgbtGreen = blurGreen;
                buffer[i][j].rgbtBlue = blurBlue;
            }
            // for left upper corner
            else if ((i == 0) && (j == 0))
            {
                int blurRed = lround((image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed) / 4.0);
                int blurGreen = lround((image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i][j +
                                        1].rgbtGreen) / 4.0);
                int blurBlue = lround((image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue) /
                                      4.0);
                buffer[i][j].rgbtRed = blurRed;
                buffer[i][j].rgbtGreen = blurGreen;
                buffer[i][j].rgbtBlue = blurBlue;
            }
            // for right upper corner
            else if ((i == 0) && (j == width - 1))
            {
                int blurRed = lround((image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed) / 4.0);
                int blurGreen = lround((image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i][j -
                                        1].rgbtGreen) / 4.0);
                int blurBlue = lround((image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue) /
                                      4.0);
                buffer[i][j].rgbtRed = blurRed;
                buffer[i][j].rgbtGreen = blurGreen;
                buffer[i][j].rgbtBlue = blurBlue;
            }
            // for left lower corner
            else if ((i == height - 1) && (j == 0))
            {
                int blurRed = lround((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed) / 4.0);
                int blurGreen = lround((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j +
                                        1].rgbtGreen) / 4.0);
                int blurBlue = lround((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue) /
                                      4.0);
                buffer[i][j].rgbtRed = blurRed;
                buffer[i][j].rgbtGreen = blurGreen;
                buffer[i][j].rgbtBlue = blurBlue;
            }
            // for right lower corner
            else if ((i == height - 1) && (j == width - 1))
            {
                int blurRed = lround((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed) / 4.0);
                int blurGreen = lround((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j -
                                        1].rgbtGreen) / 4.0);
                int blurBlue = lround((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue) /
                                      4.0);
                buffer[i][j].rgbtRed = blurRed;
                buffer[i][j].rgbtGreen = blurGreen;
                buffer[i][j].rgbtBlue = blurBlue;
            }
            // for the first  row
            else if ((i == 0) && ((j != 0) || (j != width - 1)))
            {
                int blurRed = lround((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                      image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0);
                int blurGreen = lround((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j -
                                        1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0);
                int blurBlue = lround((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                       image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0);
                buffer[i][j].rgbtRed = blurRed;
                buffer[i][j].rgbtGreen = blurGreen;
                buffer[i][j].rgbtBlue = blurBlue;
            }
            // for the last row
            else if ((i == height - 1) && ((j != 0) || (j != width - 1)))
            {
                int blurRed = lround((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed +
                                      image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6.0);
                int blurGreen = lround((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j -
                                        1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6.0);
                int blurBlue = lround((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                                       image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6.0);
                buffer[i][j].rgbtRed = blurRed;
                buffer[i][j].rgbtGreen = blurGreen;
                buffer[i][j].rgbtBlue = blurBlue;
            }
            // for the first column
            else if ((j == 0) && ((i != 0) || (i != height - 1)))
            {
                int blurRed = lround((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                      image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0);
                int blurGreen = lround((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j +
                                        1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0);
                int blurBlue = lround((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                       image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0);
                buffer[i][j].rgbtRed = blurRed;
                buffer[i][j].rgbtGreen = blurGreen;
                buffer[i][j].rgbtBlue = blurBlue;
            }
            // for the last column
            else if ((j == width - 1) && ((i != 0) || (i != height - 1)))
            {
                int blurRed = lround((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed +
                                      image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6.0);
                int blurGreen = lround((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j -
                                        1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6.0);
                int blurBlue = lround((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                                       image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6.0);
                buffer[i][j].rgbtRed = blurRed;
                buffer[i][j].rgbtGreen = blurGreen;
                buffer[i][j].rgbtBlue = blurBlue;
            }
        }
    }
    // copying blurred image from the buffer
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = buffer[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // creating a buffer if the same size
    RGBTRIPLE buffer[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // for pixels in the middle
            if ((i != 0) && (j != 0) && (i != height - 1) && (j != width - 1))
            {
                // computing Gx value of red in the middle pixel
                int GxRed = image[i][j].rgbtRed * 0 + image[i - 1][j - 1].rgbtRed * (-1) + image[i - 1][j].rgbtRed * 0 + image[i - 1][j +
                            1].rgbtRed * 1 + image[i][j - 1].rgbtRed * (-2) + image[i][j + 1].rgbtRed * 2 + image[i + 1][j - 1].rgbtRed *
                            (-1) + image[i + 1][j].rgbtRed * 0 + image[i + 1][j + 1].rgbtRed * 1;
                // computing Gy value of red in the middle pixel
                int GyRed = image[i][j].rgbtRed * 0 + image[i - 1][j - 1].rgbtRed * (-1) + image[i - 1][j].rgbtRed *
                            (-2) + image[i - 1][j + 1].rgbtRed * (-1) + image[i][j - 1].rgbtRed * 0 + image[i][j + 1].rgbtRed * 0 + image[i + 1][j - 1].rgbtRed
                            * 1 + image[i + 1][j].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed * 1;
                // computing Gx value of green in the middle pixel
                int GxGreen = image[i][j].rgbtGreen * 0 + image[i - 1][j - 1].rgbtGreen * (-1) + image[i - 1][j].rgbtGreen * 0 + image[i - 1][j +
                              1].rgbtGreen * 1 + image[i][j - 1].rgbtGreen * (-2) + image[i][j + 1].rgbtGreen * 2 + image[i + 1][j - 1].rgbtGreen *
                              (-1) + image[i + 1][j].rgbtGreen * 0 + image[i + 1][j + 1].rgbtGreen * 1;
                // computing Gy value of green in the middle pixel
                int GyGreen = image[i][j].rgbtGreen * 0 + image[i - 1][j - 1].rgbtGreen * (-1) + image[i - 1][j].rgbtGreen *
                              (-2) + image[i - 1][j + 1].rgbtGreen * (-1) + image[i][j - 1].rgbtGreen * 0 + image[i][j + 1].rgbtGreen * 0 + image[i + 1][j -
                                      1].rgbtGreen * 1 + image[i + 1][j].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1;
                // computing Gx value of blue in the middle pixel
                int GxBlue = image[i][j].rgbtBlue * 0 + image[i - 1][j - 1].rgbtBlue * (-1) + image[i - 1][j].rgbtBlue * 0 + image[i - 1][j +
                             1].rgbtBlue * 1 + image[i][j - 1].rgbtBlue * (-2) + image[i][j + 1].rgbtBlue * 2 + image[i + 1][j - 1].rgbtBlue *
                             (-1) + image[i + 1][j].rgbtBlue * 0 + image[i + 1][j + 1].rgbtBlue * 1;
                // computing Gy value of Blue in the middle pixel
                int GyBlue = image[i][j].rgbtBlue * 0 + image[i - 1][j - 1].rgbtBlue * (-1) + image[i - 1][j].rgbtBlue *
                             (-2) + image[i - 1][j + 1].rgbtBlue * (-1) + image[i][j - 1].rgbtBlue * 0 + image[i][j + 1].rgbtBlue * 0 + image[i + 1][j -
                                     1].rgbtBlue * 1 + image[i + 1][j].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue * 1;
                // computing a result Red value for buffer
                int GxyRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                //cheching if the result is greater than 255
                if (GxyRed > 255)
                {
                    buffer[i][j].rgbtRed = 255;
                }
                else
                {
                    buffer[i][j].rgbtRed = GxyRed;
                }
                // computing a result Green value for buffer
                int GxyGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                //cheching if the result is greater than 255
                if (GxyGreen > 255)
                {
                    buffer[i][j].rgbtGreen = 255;
                }
                else
                {
                    buffer[i][j].rgbtGreen = GxyGreen;
                }
                // computing a result Blue value for buffer
                int GxyBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                //cheching if the result is greater than 255
                if (GxyBlue > 255)
                {
                    buffer[i][j].rgbtBlue = 255;
                }
                else
                {
                    buffer[i][j].rgbtBlue = GxyBlue;
                }
            }
            // for left upper corner
            else if ((i == 0) && (j == 0))
            {
                // computing Gx value of Red in the left upper corner pixel
                int GxRed = image[i][j].rgbtRed * 0 + image[i + 1][j].rgbtRed * 0 + image[i + 1][j + 1].rgbtRed * 1 + image[i][j + 1].rgbtRed * 2;
                // computing Gy value of Red in the left upper corner pixel
                int GyRed = image[i][j].rgbtRed * 0 + image[i + 1][j].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed * 1 + image[i][j + 1].rgbtRed * 0;
                // computing Gx value of Green in the left upper corner pixel
                int GxGreen = image[i][j].rgbtGreen * 0 + image[i + 1][j].rgbtGreen * 0 + image[i + 1][j + 1].rgbtGreen * 1 + image[i][j +
                              1].rgbtGreen * 2;
                // computing Gy value of Green in the left upper corner pixel
                int GyGreen = image[i][j].rgbtGreen * 0 + image[i + 1][j].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1 + image[i][j +
                              1].rgbtGreen * 0;
                // computing Gx value of Blue in the left upper corner pixel
                int GxBlue = image[i][j].rgbtBlue * 0 + image[i + 1][j].rgbtBlue * 0 + image[i + 1][j + 1].rgbtBlue * 1 + image[i][j + 1].rgbtBlue *
                             2;
                // computing Gy value of Blue in the left upper corner pixel
                int GyBlue = image[i][j].rgbtBlue * 0 + image[i + 1][j].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue * 1 + image[i][j + 1].rgbtBlue *
                             0;
                // computing a result Red value for buffer
                int GxyRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                //cheching if the result is greater than 255
                if (GxyRed > 255)
                {
                    buffer[i][j].rgbtRed = 255;
                }
                else
                {
                    buffer[i][j].rgbtRed = GxyRed;
                }
                // computing a result Green value for buffer
                int GxyGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                //cheching if the result is greater than 255
                if (GxyGreen > 255)
                {
                    buffer[i][j].rgbtGreen = 255;
                }
                else
                {
                    buffer[i][j].rgbtGreen = GxyGreen;
                }
                // computing a result Blue value for buffer
                int GxyBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                //cheching if the result is greater than 255
                if (GxyBlue > 255)
                {
                    buffer[i][j].rgbtBlue = 255;
                }
                else
                {
                    buffer[i][j].rgbtBlue = GxyBlue;
                }
            }
            // for right upper corner
            else if ((i == 0) && (j == width - 1))
            {
                // computing Gx value of Red in the right upper corner pixel
                int GxRed = image[i][j].rgbtRed * 0 + image[i + 1][j].rgbtRed * 0 + image[i + 1][j - 1].rgbtRed * (-1) + image[i][j - 1].rgbtRed *
                            (-2);
                // computing Gy value of Red in the right upper corner pixel
                int GyRed = image[i][j].rgbtRed * 0 + image[i + 1][j].rgbtRed * 2 + image[i + 1][j - 1].rgbtRed * 1 + image[i][j - 1].rgbtRed * 0;
                // computing Gx value of Green in the right upper corner pixel
                int GxGreen = image[i][j].rgbtGreen * 0 + image[i + 1][j].rgbtGreen * 0 + image[i + 1][j - 1].rgbtGreen *
                              (-1) + image[i][j - 1].rgbtGreen * (-2);
                // computing Gy value of Green in the right upper corner pixel
                int GyGreen = image[i][j].rgbtGreen * 0 + image[i + 1][j].rgbtGreen * 2 + image[i + 1][j - 1].rgbtGreen * 1 + image[i][j -
                              1].rgbtGreen * 0;
                // computing Gx value of Blue in the right upper corner pixel
                int GxBlue = image[i][j].rgbtBlue * 0 + image[i + 1][j].rgbtBlue * 0 + image[i + 1][j - 1].rgbtBlue *
                             (-1) + image[i][j - 1].rgbtBlue * (-2);
                // computing Gy value of Green in the right upper corner pixel
                int GyBlue = image[i][j].rgbtBlue * 0 + image[i + 1][j].rgbtBlue * 2 + image[i + 1][j - 1].rgbtBlue * 1 + image[i][j - 1].rgbtBlue *
                             0;
                // computing a result Red value for buffer
                int GxyRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                //cheching if the result is greater than 255
                if (GxyRed > 255)
                {
                    buffer[i][j].rgbtRed = 255;
                }
                else
                {
                    buffer[i][j].rgbtRed = GxyRed;
                }
                // computing a result Green value for buffer
                int GxyGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                //cheching if the result is greater than 255
                if (GxyGreen > 255)
                {
                    buffer[i][j].rgbtGreen = 255;
                }
                else
                {
                    buffer[i][j].rgbtGreen = GxyGreen;
                }
                // computing a result Blue value for buffer
                int GxyBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                //cheching if the result is greater than 255
                if (GxyBlue > 255)
                {
                    buffer[i][j].rgbtBlue = 255;
                }
                else
                {
                    buffer[i][j].rgbtBlue = GxyBlue;
                }
            }
            // for left lower corner
            else if ((i == height - 1) && (j == 0))
            {
                // computing Gx value of Red in the left lower corner pixel
                int GxRed = image[i][j].rgbtRed * 0 + image[i - 1][j].rgbtRed * 0 + image[i - 1][j + 1].rgbtRed * 1 + image[i][j + 1].rgbtRed * 2;
                // computing Gy value of Red in the left lower corner pixel
                int GyRed = image[i][j].rgbtRed * 0 + image[i - 1][j].rgbtRed * (-2) + image[i - 1][j + 1].rgbtRed *
                            (-1) + image[i][j + 1].rgbtRed * 0;
                // computing Gx value of Green in the left lower corner pixel
                int GxGreen = image[i][j].rgbtGreen * 0 + image[i - 1][j].rgbtGreen * 0 + image[i - 1][j + 1].rgbtGreen * 1 + image[i][j +
                              1].rgbtGreen * 2;
                // computing Gy value of Green in the left lower corner pixel
                int GyGreen = image[i][j].rgbtGreen * 0 + image[i - 1][j].rgbtGreen * (-2) + image[i - 1][j + 1].rgbtGreen *
                              (-1) + image[i][j + 1].rgbtGreen * 0;
                // computing Gx value of Blue in the left lower corner pixel
                int GxBlue = image[i][j].rgbtBlue * 0 + image[i - 1][j].rgbtBlue * 0 + image[i - 1][j + 1].rgbtBlue * 1 + image[i][j + 1].rgbtBlue *
                             2;
                // computing Gy value of Blue in the left lower corner pixel
                int GyBlue = image[i][j].rgbtBlue * 0 + image[i - 1][j].rgbtBlue * (-2) + image[i - 1][j + 1].rgbtBlue *
                             (-1) + image[i][j + 1].rgbtBlue * 0;
                // computing a result Red value for buffer
                int GxyRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                //cheching if the result is greater than 255
                if (GxyRed > 255)
                {
                    buffer[i][j].rgbtRed = 255;
                }
                else
                {
                    buffer[i][j].rgbtRed = GxyRed;
                }
                // computing a result Green value for buffer
                int GxyGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                //cheching if the result is greater than 255
                if (GxyGreen > 255)
                {
                    buffer[i][j].rgbtGreen = 255;
                }
                else
                {
                    buffer[i][j].rgbtGreen = GxyGreen;
                }
                // computing a result Blue value for buffer
                int GxyBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                //cheching if the result is greater than 255
                if (GxyBlue > 255)
                {
                    buffer[i][j].rgbtBlue = 255;
                }
                else
                {
                    buffer[i][j].rgbtBlue = GxyBlue;
                }
            }
            // for right lower corner
            else if ((i == height - 1) && (j == width - 1))
            {
                // computing Gx value of Red in the right lower corner pixel
                int GxRed = image[i][j].rgbtRed * 0 + image[i - 1][j].rgbtRed * 0 + image[i - 1][j - 1].rgbtRed * (-1) + image[i][j - 1].rgbtRed *
                            (-2);
                // computing Gy value of Red in the right lower corner pixel
                int GyRed = image[i][j].rgbtRed * 0 + image[i - 1][j].rgbtRed * (-2) + image[i - 1][j - 1].rgbtRed *
                            (-1) + image[i][j - 1].rgbtRed * 0;
                // computing Gx value of Green in the right lower corner pixel
                int GxGreen = image[i][j].rgbtGreen * 0 + image[i - 1][j].rgbtGreen * 0 + image[i - 1][j - 1].rgbtGreen *
                              (-1) + image[i][j - 1].rgbtGreen * (-2);
                // computing Gy value of Green in the right lower corner pixel
                int GyGreen = image[i][j].rgbtGreen * 0 + image[i - 1][j].rgbtGreen * (-2) + image[i - 1][j - 1].rgbtGreen *
                              (-1) + image[i][j - 1].rgbtGreen * 0;
                // computing Gx value of Blue in the right lower corner pixel
                int GxBlue = image[i][j].rgbtBlue * 0 + image[i - 1][j].rgbtBlue * 0 + image[i - 1][j - 1].rgbtBlue *
                             (-1) + image[i][j - 1].rgbtBlue * (-2);
                // computing Gy value of Blue in the right lower corner pixel
                int GyBlue = image[i][j].rgbtBlue * 0 + image[i - 1][j].rgbtBlue * (-2) + image[i - 1][j - 1].rgbtBlue *
                             (-1) + image[i][j - 1].rgbtBlue * 0;
                // computing a result Red value for buffer
                int GxyRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                //cheching if the result is greater than 255
                if (GxyRed > 255)
                {
                    buffer[i][j].rgbtRed = 255;
                }
                else
                {
                    buffer[i][j].rgbtRed = GxyRed;
                }
                // computing a result Green value for buffer
                int GxyGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                //cheching if the result is greater than 255
                if (GxyGreen > 255)
                {
                    buffer[i][j].rgbtGreen = 255;
                }
                else
                {
                    buffer[i][j].rgbtGreen = GxyGreen;
                }
                // computing a result Blue value for buffer
                int GxyBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                //cheching if the result is greater than 255
                if (GxyBlue > 255)
                {
                    buffer[i][j].rgbtBlue = 255;
                }
                else
                {
                    buffer[i][j].rgbtBlue = GxyBlue;
                }
            }
            // for the first  row
            else if ((i == 0) && ((j != 0) || (j != width - 1)))
            {
                // computing Gx value of Red in the first row
                int GxRed = image[i][j].rgbtRed * 0 + image[i][j - 1].rgbtRed * (-2) + image[i][j + 1].rgbtRed * 2 + image[i + 1][j - 1].rgbtRed *
                            (-1) + image[i + 1][j].rgbtRed * 0 + image[i + 1][j + 1].rgbtRed * 1;
                // computing Gy value of Red in the first row
                int GyRed = image[i][j].rgbtRed * 0 + image[i][j - 1].rgbtRed * 0 + image[i][j + 1].rgbtRed * 0 + image[i + 1][j - 1].rgbtRed * 1 +
                            image[i + 1][j].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed * 1;
                // computing Gx value of Green in the first row
                int GxGreen = image[i][j].rgbtGreen * 0 + image[i][j - 1].rgbtGreen * (-2) + image[i][j + 1].rgbtGreen * 2 + image[i + 1][j -
                              1].rgbtGreen * (-1) + image[i + 1][j].rgbtGreen * 0 + image[i + 1][j + 1].rgbtGreen * 1;
                // computing Gy value of Green in the first row
                int GyGreen = image[i][j].rgbtGreen * 0 + image[i][j - 1].rgbtGreen * 0 + image[i][j + 1].rgbtGreen * 0 + image[i + 1][j -
                              1].rgbtGreen * 1 + image[i + 1][j].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1;
                // computing Gx value of Blue in the first row
                int GxBlue = image[i][j].rgbtBlue * 0 + image[i][j - 1].rgbtBlue * (-2) + image[i][j + 1].rgbtBlue * 2 + image[i + 1][j -
                             1].rgbtBlue * (-1) + image[i + 1][j].rgbtBlue * 0 + image[i + 1][j + 1].rgbtBlue * 1;
                // computing Gy value of Blue in the first row
                int GyBlue = image[i][j].rgbtBlue * 0 + image[i][j - 1].rgbtBlue * 0 + image[i][j + 1].rgbtBlue * 0 + image[i + 1][j - 1].rgbtBlue *
                             1 + image[i + 1][j].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue * 1;
                // computing a result Red value for buffer
                int GxyRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                //cheching if the result is greater than 255
                if (GxyRed > 255)
                {
                    buffer[i][j].rgbtRed = 255;
                }
                else
                {
                    buffer[i][j].rgbtRed = GxyRed;
                }
                // computing a result Green value for buffer
                int GxyGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                //cheching if the result is greater than 255
                if (GxyGreen > 255)
                {
                    buffer[i][j].rgbtGreen = 255;
                }
                else
                {
                    buffer[i][j].rgbtGreen = GxyGreen;
                }
                // computing a result Blue value for buffer
                int GxyBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                //cheching if the result is greater than 255
                if (GxyBlue > 255)
                {
                    buffer[i][j].rgbtBlue = 255;
                }
                else
                {
                    buffer[i][j].rgbtBlue = GxyBlue;
                }
            }
            // for the last row
            else if ((i == height - 1) && ((j != 0) || (j != width - 1)))
            {
                // computing Gx value of Red in the last row
                int GxRed = image[i][j].rgbtRed * 0 + image[i][j - 1].rgbtRed * (-2) + image[i][j + 1].rgbtRed * 2 + image[i - 1][j - 1].rgbtRed *
                            (-1) + image[i - 1][j].rgbtRed * 0 + image[i - 1][j + 1].rgbtRed * 1;
                // computing Gy value of Red in the last row
                int GyRed = image[i][j].rgbtRed * 0 + image[i][j - 1].rgbtRed * 0 + image[i][j + 1].rgbtRed * 0 + image[i - 1][j - 1].rgbtRed *
                            (-1) + image[i - 1][j].rgbtRed * (-2) + image[i - 1][j + 1].rgbtRed * (-1);
                // computing Gx value of Green in the last row
                int GxGreen = image[i][j].rgbtGreen * 0 + image[i][j - 1].rgbtGreen * (-2) + image[i][j + 1].rgbtGreen * 2 + image[i - 1][j -
                              1].rgbtGreen * (-1) + image[i - 1][j].rgbtGreen * 0 + image[i - 1][j + 1].rgbtGreen * 1;
                // computing Gy value of Green in the last row
                int GyGreen = image[i][j].rgbtGreen * 0 + image[i][j - 1].rgbtGreen * 0 + image[i][j + 1].rgbtGreen * 0 + image[i - 1][j -
                              1].rgbtGreen * (-1) + image[i - 1][j].rgbtGreen * (-2) + image[i - 1][j + 1].rgbtGreen * (-1);
                // computing Gx value of Blue in the last row
                int GxBlue = image[i][j].rgbtBlue * 0 + image[i][j - 1].rgbtBlue * (-2) + image[i][j + 1].rgbtBlue * 2 + image[i - 1][j -
                             1].rgbtBlue * (-1) + image[i - 1][j].rgbtBlue * 0 + image[i - 1][j + 1].rgbtBlue * 1;
                // computing Gy value of Blue in the last row
                int GyBlue = image[i][j].rgbtBlue * 0 + image[i][j - 1].rgbtBlue * 0 + image[i][j + 1].rgbtBlue * 0 + image[i - 1][j - 1].rgbtBlue
                             * (-1) + image[i - 1][j].rgbtBlue * (-2) + image[i - 1][j + 1].rgbtBlue * (-1);
                // computing a result Red value for buffer
                int GxyRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                //cheching if the result is greater than 255
                if (GxyRed > 255)
                {
                    buffer[i][j].rgbtRed = 255;
                }
                else
                {
                    buffer[i][j].rgbtRed = GxyRed;
                }
                // computing a result Green value for buffer
                int GxyGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                //cheching if the result is greater than 255
                if (GxyGreen > 255)
                {
                    buffer[i][j].rgbtGreen = 255;
                }
                else
                {
                    buffer[i][j].rgbtGreen = GxyGreen;
                }
                // computing a result Blue value for buffer
                int GxyBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                //cheching if the result is greater than 255
                if (GxyBlue > 255)
                {
                    buffer[i][j].rgbtBlue = 255;
                }
                else
                {
                    buffer[i][j].rgbtBlue = GxyBlue;
                }
            }
            // for the first column
            else if ((j == 0) && ((i != 0) || (i != height - 1)))
            {
                // computing Gx value of Red in the first column
                int GxRed = image[i][j].rgbtRed * 0 + image[i][j + 1].rgbtRed * 2 + image[i - 1][j].rgbtRed * 0 + image[i - 1][j + 1].rgbtRed * 1
                            + image[i + 1][j].rgbtRed * 0 + image[i + 1][j + 1].rgbtRed * 1;
                // computing Gy value of Red in the first column
                int GyRed = image[i][j].rgbtRed * 0 + image[i][j + 1].rgbtRed * 0 + image[i - 1][j].rgbtRed * (-2) + image[i - 1][j + 1].rgbtRed *
                            (-1) + image[i + 1][j].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed * 1;
                // computing Gx value of Green in the first column
                int GxGreen = image[i][j].rgbtGreen * 0 + image[i][j + 1].rgbtGreen * 2 + image[i - 1][j].rgbtGreen * 0 + image[i - 1][j +
                              1].rgbtGreen * 1 + image[i + 1][j].rgbtGreen * 0 + image[i + 1][j + 1].rgbtGreen * 1;
                // computing Gy value of Green in the first column
                int GyGreen = image[i][j].rgbtGreen * 0 + image[i][j + 1].rgbtGreen * 0 + image[i - 1][j].rgbtGreen *
                              (-2) + image[i - 1][j + 1].rgbtGreen * (-1) + image[i + 1][j].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1;
                // computing Gx value of Blue in the first column
                int GxBlue = image[i][j].rgbtBlue * 0 + image[i][j + 1].rgbtBlue * 2 + image[i - 1][j].rgbtBlue * 0 + image[i - 1][j + 1].rgbtBlue *
                             1 + image[i + 1][j].rgbtBlue * 0 + image[i + 1][j + 1].rgbtBlue * 1;
                // computing Gy value of Blue in the first column
                int GyBlue = image[i][j].rgbtBlue * 0 + image[i][j + 1].rgbtBlue * 0 + image[i - 1][j].rgbtBlue *
                             (-2) + image[i - 1][j + 1].rgbtBlue * (-1) + image[i + 1][j].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue * 1;
                // computing a result Red value for buffer
                int GxyRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                //cheching if the result is greater than 255
                if (GxyRed > 255)
                {
                    buffer[i][j].rgbtRed = 255;
                }
                else
                {
                    buffer[i][j].rgbtRed = GxyRed;
                }
                // computing a result Green value for buffer
                int GxyGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                //cheching if the result is greater than 255
                if (GxyGreen > 255)
                {
                    buffer[i][j].rgbtGreen = 255;
                }
                else
                {
                    buffer[i][j].rgbtGreen = GxyGreen;
                }
                // computing a result Blue value for buffer
                int GxyBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                //cheching if the result is greater than 255
                if (GxyBlue > 255)
                {
                    buffer[i][j].rgbtBlue = 255;
                }
                else
                {
                    buffer[i][j].rgbtBlue = GxyBlue;
                }
            }
            // for the last column
            else if ((j == width - 1) && ((i != 0) || (i != height - 1)))
            {
                // computing Gx value of Red in the last column
                int GxRed = image[i][j].rgbtRed * 0 + image[i][j - 1].rgbtRed * (-2) + image[i - 1][j].rgbtRed * 0 + image[i - 1][j - 1].rgbtRed *
                            (-1) + image[i + 1][j].rgbtRed * 0 + image[i + 1][j - 1].rgbtRed * (-1);
                // computing Gy value of Red in the last column
                int GyRed = image[i][j].rgbtRed * 0 + image[i][j - 1].rgbtRed * 0 + image[i - 1][j].rgbtRed * (-2) + image[i - 1][j - 1].rgbtRed *
                            (-1) + image[i + 1][j].rgbtRed * 2 + image[i + 1][j - 1].rgbtRed * 1;
                // computing Gx value of Green in the last column
                int GxGreen = image[i][j].rgbtGreen * 0 + image[i][j - 1].rgbtGreen * (-2) + image[i - 1][j].rgbtGreen * 0 + image[i - 1][j -
                              1].rgbtGreen * (-1) + image[i + 1][j].rgbtGreen * 0 + image[i + 1][j - 1].rgbtGreen * (-1);
                // computing Gy value of Green in the last column
                int GyGreen = image[i][j].rgbtGreen * 0 + image[i][j - 1].rgbtGreen * 0 + image[i - 1][j].rgbtGreen *
                              (-2) + image[i - 1][j - 1].rgbtGreen * (-1) + image[i + 1][j].rgbtGreen * 2 + image[i + 1][j - 1].rgbtGreen * 1;
                // computing Gx value of Blue in the last column
                int GxBlue = image[i][j].rgbtBlue * 0 + image[i][j - 1].rgbtBlue * (-2) + image[i - 1][j].rgbtBlue * 0 + image[i - 1][j -
                             1].rgbtBlue * (-1) + image[i + 1][j].rgbtBlue * 0 + image[i + 1][j - 1].rgbtBlue * (-1);
                // computing Gy value of Blue in the last column
                int GyBlue = image[i][j].rgbtBlue * 0 + image[i][j - 1].rgbtBlue * 0 + image[i - 1][j].rgbtBlue *
                             (-2) + image[i - 1][j - 1].rgbtBlue * (-1) + image[i + 1][j].rgbtBlue * 2 + image[i + 1][j - 1].rgbtBlue * 1;
                // computing a result Red value for buffer
                int GxyRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                //cheching if the result is greater than 255
                if (GxyRed > 255)
                {
                    buffer[i][j].rgbtRed = 255;
                }
                else
                {
                    buffer[i][j].rgbtRed = GxyRed;
                }
                // computing a result Green value for buffer
                int GxyGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                //cheching if the result is greater than 255
                if (GxyGreen > 255)
                {
                    buffer[i][j].rgbtGreen = 255;
                }
                else
                {
                    buffer[i][j].rgbtGreen = GxyGreen;
                }
                // computing a result Blue value for buffer
                int GxyBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                //cheching if the result is greater than 255
                if (GxyBlue > 255)
                {
                    buffer[i][j].rgbtBlue = 255;
                }
                else
                {
                    buffer[i][j].rgbtBlue = GxyBlue;
                }
            }

        }

    }
    // copying edged image from the buffer
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = buffer[i][j];
        }
    }
    return;
}
