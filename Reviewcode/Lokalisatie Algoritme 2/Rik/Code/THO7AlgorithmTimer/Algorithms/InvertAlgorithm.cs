using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;

namespace THO7AlgorithmTimerApplication
{
    class InvertAlgorithm : VisionAlgorithm
    {
        public InvertAlgorithm(String name) : base(name) { }
        public unsafe override System.Drawing.Bitmap DoAlgorithm(System.Drawing.Bitmap sourceImage)
        {
            int originalWidth = sourceImage.Width;
            int originalHeight = sourceImage.Height;
            int* pWidth = &originalWidth, pHeight = &originalHeight;
            Bitmap returnImage = new Bitmap(sourceImage.Width, sourceImage.Height);
            BitmapData originalData = sourceImage.LockBits(new Rectangle(0, 0, *pWidth, *pHeight), ImageLockMode.ReadOnly, PixelFormat.Format32bppRgb);
            BitmapData returnData = returnImage.LockBits(new Rectangle(0, 0, *pWidth, *pHeight), ImageLockMode.WriteOnly, PixelFormat.Format32bppRgb);

            int[] lut = new int[256];
            for (int i = 0; i < lut.Length; i++)
            {
                lut[i] = 255 - i;
            }
            int* originalPointer = (int*)originalData.Scan0.ToPointer();
            int* returnPointer = (int*)returnData.Scan0.ToPointer();
            int sourcePosition;
            int* pSourcePosition = &sourcePosition;
            for (int y = 0; y < *pHeight; y++)
            {
                for (int x = 0; x < *pWidth; x++)
                {
                    *pSourcePosition = (x + (y * *pWidth));
                    //returnPointer[*pSourcePosition] = ((originalPointer[*pSourcePosition] & (0xFF << 24)) | ((255 - ((originalPointer[*pSourcePosition] >> 16) & 0xFF)) << 16) | ((255 - ((originalPointer[*pSourcePosition] >> 8) & 0xFF)) << 8) | (255 - (originalPointer[*pSourcePosition] & 0xFF)));
                    returnPointer[*pSourcePosition] = ((originalPointer[*pSourcePosition] & (0xFF << 24) | ((lut[((originalPointer[*pSourcePosition] >> 16) & 0xFF)]) << 16) | ((lut[((originalPointer[*pSourcePosition] >> 8) & 0xFF)]) << 8) | (lut[(originalPointer[*pSourcePosition] & 0xFF)])));
                }
            }
            sourceImage.UnlockBits(originalData);
            returnImage.UnlockBits(returnData);

            return returnImage;
        }
    }
}