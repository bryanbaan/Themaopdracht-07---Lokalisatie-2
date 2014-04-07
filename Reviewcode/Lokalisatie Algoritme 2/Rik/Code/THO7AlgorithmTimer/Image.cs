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
    unsafe class Image
    {
        private Bitmap image;
        private BitmapData imageData;
        public int width;
        public int height;
        private int* imagePointer;

        public Image(Bitmap image)
        {
            this.image = image;

            width = image.Width;
            height = image.Height;
            imageData = this.image.LockBits(new Rectangle(0, 0, image.Width, image.Height), ImageLockMode.ReadWrite, PixelFormat.Format32bppRgb);
            imagePointer = (int*)imageData.Scan0.ToPointer();
        }

        ~ Image()
        {
        }

        public int getPixel(int x, int y)
        {
            return imagePointer[x + y * width];
        }

        public void setPixel(int x, int y, int color)
        {
            imagePointer[x + y * width] = color;
        }

        public Bitmap getBitmap()
        {
            image.UnlockBits(imageData);
            return image;
        }
    }
}
