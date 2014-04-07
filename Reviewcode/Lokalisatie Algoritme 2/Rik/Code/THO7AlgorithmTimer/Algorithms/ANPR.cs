using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Xml;
using System.Windows.Forms;

namespace THO7AlgorithmTimerApplication
{
    class ANPR : VisionAlgorithm
    {
        public ANPR(String name) : base(name) { }
        public override System.Drawing.Bitmap DoAlgorithm(System.Drawing.Bitmap sourceImage)
        {
            Bitmap returnImage = new Bitmap(sourceImage);
            int yellowCount = 0;
            int width = returnImage.Width;
            int height = returnImage.Height;
            int r, g, b;
            int[] histoX = new int[height];
            int[] histoY = new int[width];
            int topLeftX, topLeftY, topRightX, topRightY, bottomRightX, bottomRightY, bottomLeftX, bottomLeftY;
            topLeftX = topLeftY = topRightX = topRightY = bottomRightX = bottomRightY = bottomLeftX = bottomLeftY = 0;

            Rectangle rect = new Rectangle(0, 0, width, height);

            BitmapData bmpData = returnImage.LockBits(rect, ImageLockMode.ReadWrite, PixelFormat.Format32bppArgb);

            IntPtr ptr = bmpData.Scan0;
            int[] rgbValues = new int[width * height];
            int[] rgbValuesNew = new int[width * height];
            System.Runtime.InteropServices.Marshal.Copy(ptr, rgbValues, 0, height * width);

            for (int counter = 0; counter < rgbValues.Length; counter++)
            {
                r = ((rgbValues[counter] & 0x00FF0000) >> 16);
                g = ((rgbValues[counter] & 0x0000FF00) >> 8);
                b = (rgbValues[counter] & 0x000000FF);

                /*if (r > 80 && g > 70 && g < 120 && b < 70)
                {
                    if (r > 200)
                    {
                    }
                    else
                    {
                        rgbValues[counter] = unchecked((int)0xFF000000);
                    }
                }
                else
                {
                    r += 120;
                    g += 130;
                    b -= 20;

                    if (r > 255)
                    {
                        r = 255;
                    }
                    if (g > 255)
                    {
                        g = 255;
                    }
                    if (r > 200 && g > 170 && b < 40)
                    {
                        rgbValues[counter] = unchecked((int)0xFFFFFFFF);
                    }
                    else
                    {
                        rgbValues[counter] = unchecked((int)0xFF000000);
                    }
                }*/

                if (r > 180 && g > 130 && b < 40)
                {
                    rgbValuesNew[counter] = unchecked((int)0xFFFFFFFF);
                    yellowCount++;
                }
                else
                {
                    rgbValuesNew[counter] = unchecked((int)0xFF000000);
                }
            }

            Console.WriteLine("Yellowcount: " + yellowCount + " #pixels in 1% of image: " + (int)(rgbValues.Length * 0.01));

            if (yellowCount < (int)(rgbValues.Length * 0.005))
            {
                for (int counter = 0; counter < rgbValues.Length; counter++)
                {
                    r = ((rgbValues[counter] & 0x00FF0000) >> 16);
                    g = ((rgbValues[counter] & 0x0000FF00) >> 8);
                    b = (rgbValues[counter] & 0x000000FF);
                    if (r > 80 && g > 70 && g < 120 && b < 70)
                    {
                        if (r > 200)
                        {
                        }
                        else
                        {
                            rgbValues[counter] = unchecked((int)0xFF000000);
                        }
                    }
                    else
                    {
                        r += 120;
                        g += 130;
                        b -= 20;

                        if (r > 255)
                        {
                            r = 255;
                        }
                        if (g > 255)
                        {
                            g = 255;
                        }
                        if (r > 200 && g > 170 && b < 40)
                        {
                            rgbValues[counter] = unchecked((int)0xFFFFFFFF);
                        }
                        else
                        {
                            rgbValues[counter] = unchecked((int)0xFF000000);
                        }
                    }
                }
            }
            else
            {
                for (int i = 0; i < rgbValues.Length; i++)
                {
                    if (rgbValuesNew[i] != 0)
                    {
                        rgbValues[i] = rgbValuesNew[i];
                        rgbValuesNew[i] = 0;
                    }
                }
            }

            for (int h = 0; h < height; h++)
            {
                for (int w = 0; w < width; w++)
                {
                    if (rgbValues[w + h * width] == unchecked((int)0xFFFFFFFF))
                    {
                        histoX[h]++;
                        histoY[w]++;
                    }
                }
            }
            int highestHistoXValue = 0;
            int highestHistoYValue = 0;

            for (int i = 0; i < histoX.Length; i++)
            {
                if (histoX[i] > highestHistoXValue)
                {
                    highestHistoXValue = histoX[i];
                }
            }

            for (int i = 0; i < histoY.Length; i++)
            {
                if (histoY[i] > highestHistoYValue)
                {
                    highestHistoYValue = histoY[i];
                }
            }


            for (int h = 1; h < height - 1; h++)
            {
                //if (histoX[h] > (highestHistoXValue * 0.2))
                {
                    for (int w = 1; w < width - 1; w++)
                    {
                        //if (histoY[w] > (highestHistoYValue * 0.2))
                        {
                            double white = 0;

                            for (int i = -1; i < 2; i++)
                            {
                                for (int j = -1; j < 2; j++)
                                {
                                    if (rgbValues[w + i + (h + j) * width] == unchecked((int)0xFFFFFFFF))
                                    {
                                        white++;
                                    }
                                }
                            }
                            if (white == 9)
                            {
                                rgbValuesNew[w + h * width] = unchecked((int)0xFFCD0000);

                                if (topLeftX > w || topLeftX == 0 && topLeftY > h || topLeftY == 0)
                                {
                                    topLeftX = w;
                                    topLeftY = h;                                    
                                }

                                if (topRightX < w || topRightX == 0 && topRightY > h || topRightY == 0)
                                {
                                    topRightX = w;
                                    topRightY = h;
                                }

                                if ((bottomLeftX > w || bottomLeftX == 0) && (bottomLeftY > h || bottomLeftY == 0) && w > topLeftY)
                                {
                                    bottomLeftX = w;
                                    bottomLeftY = h;
                                }

                                if ((bottomRightX < w || bottomRightX == 0) && (bottomRightY < h || bottomRightY == 0) && w > topRightY)
                                {
                                    bottomRightX = w;
                                    bottomRightY = h;
                                }
                                bottomRightX = w;
                                bottomRightY = h;
                            }
                            else
                            {
                                rgbValuesNew[w + h * width] = unchecked((int)0xFF000000);
                            }
                        }
                    }
                }
            }
            Console.WriteLine("Topleft: " + topLeftX + ", " + topLeftY);
            Console.WriteLine("Topright: " + topRightX + ", " + topRightY);
            Console.WriteLine("Bottomleft: " + bottomLeftX + ", " + bottomLeftY);
            Console.WriteLine("Bottomright: " + bottomRightX + ", " + bottomRightY);

            /*rgbValuesNew[topLeftX + topLeftY * width] = unchecked((int)0xFF37FDFC);
            rgbValuesNew[topRightX + topRightX * width] = unchecked((int)0xFF37FDFC);
            rgbValuesNew[bottomLeftX + bottomLeftY * width] = unchecked((int)0xFF37FDFC);
            rgbValuesNew[bottomRightX + bottomRightY * width] = unchecked((int)0xFF37FDFC);*/

            for (int i = 0; i < rgbValues.Length; i++)
            {
                if (rgbValuesNew[i] != 0)
                {
                    rgbValues[i] = rgbValuesNew[i];
                }
            }

            System.Runtime.InteropServices.Marshal.Copy(rgbValues, 0, ptr, height * width);

            returnImage.UnlockBits(bmpData);

            Graphics gr = Graphics.FromImage(returnImage);

            //topleft
            Pen p1 = new Pen(Color.Blue, 3);

            //topright
            Pen p2 = new Pen(Color.Green, 3);

            //bottomleft
            Pen p3 = new Pen(Color.Red, 3);

            //bottomright
            Pen p4 = new Pen(Color.Yellow, 3);

            gr.DrawImage(returnImage, 0, 0);

            gr.DrawLine(p1, topLeftX, 0, topLeftX, height);
            gr.DrawLine(p1, 0, topLeftY, width, topLeftY);

            gr.DrawLine(p2, topRightX, 0, topRightX, height);
            gr.DrawLine(p2, 0, topRightY, width, topRightY);

            gr.DrawLine(p3, bottomLeftX, 0, bottomLeftX, height);
            gr.DrawLine(p3, 0, bottomLeftY, width, bottomLeftY);

            gr.DrawLine(p4, bottomRightX, 0, bottomRightX, height);
            gr.DrawLine(p4, 0, bottomRightY, width, bottomRightY);

            //gr.DrawLine(p, topRightX, topRightY, topLeftX, topLeftY);
            return returnImage;
        }
    }
}
