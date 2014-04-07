using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace THO7AlgorithmTimerApplication
{
    class Median3Algorithm : VisionAlgorithm
    {
        public Median3Algorithm(String name) : base(name) { }

        public unsafe override System.Drawing.Bitmap DoAlgorithm(System.Drawing.Bitmap sourceImage)
        {
            int[] rmask = new int[9];
            int[] gmask = new int[9];
            int[] bmask = new int[9];
            Image originalImage = new Image(new Bitmap(sourceImage));
            Image returnImage = new Image(new Bitmap(sourceImage.Width, sourceImage.Height));
            
            for (int x = 1; x < originalImage.width - 1; x++)
            {
                for (int y = 1; y < originalImage.height - 1; y++)
                {
                        int count = 0;
                        for (int i = -1; i < 2; i++)
                        {
                            for (int j = -1; j < 2; j++)
                            {
                                rmask[count] = originalImage.getPixel(x + i, y + j) >> 16 & 0xFF;
                                gmask[count] = originalImage.getPixel(x + i, y + j) >> 8 & 0xFF;
                                bmask[count] = originalImage.getPixel(x + i, y + j) & 0xFF;
                                count++;
                            }
                        }
                        Array.Sort(rmask);
                        Array.Sort(gmask);
                        Array.Sort(bmask);
                        returnImage.setPixel(x, y, (255 << 24 | rmask[4] << 16 | gmask[4] << 8 | bmask[4]));
                    }
            }
            return returnImage.getBitmap();
        }
    }
}