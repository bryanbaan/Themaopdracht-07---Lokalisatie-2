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
    class Median11Algorithm : VisionAlgorithm
    {
        public Median11Algorithm(String name) : base(name) { }
        public unsafe override System.Drawing.Bitmap DoAlgorithm(System.Drawing.Bitmap sourceImage)
        {
            int[] rmask = new int[121];
            int[] gmask = new int[121];
            int[] bmask = new int[121];
            Image originalImage = new Image(new Bitmap(sourceImage));
            Image returnImage = new Image(new Bitmap(sourceImage.Width, sourceImage.Height));

            for (int x = 5; x < originalImage.width - 5; x++)
            {
                for (int y = 5; y < originalImage.height - 5; y++)
                {
                    int count = 0;
                    for (int i = -5; i < 6; i++)
                    {
                        for (int j = -5; j < 6; j++)
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
                    returnImage.setPixel(x, y, 255 << 24 | rmask[61] << 16 | gmask[61] << 8 | bmask[61]);
                }
            }
            return returnImage.getBitmap();
        }
    }
}