using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;

namespace THO7AlgorithmTimerApplication
{
    class BlackAlgorithm : VisionAlgorithm
    {
        public BlackAlgorithm(String name) : base(name) { }
        public override System.Drawing.Bitmap DoAlgorithm(System.Drawing.Bitmap sourceImage)
        {
            int length = sourceImage.Width * sourceImage.Height;
            Bitmap returnImage = new Bitmap(sourceImage.Width, sourceImage.Height);
            BitmapData returnData = returnImage.LockBits(new Rectangle(0, 0, returnImage.Width, returnImage.Height), ImageLockMode.WriteOnly, PixelFormat.Format32bppRgb);
            unsafe
            {
                int* returnPointer = (int*)returnData.Scan0.ToPointer();
                for (int i = 0; i < length; i++)
                {
                    returnPointer[i] = 0;
                }
            }
            returnImage.UnlockBits(returnData);
            return returnImage;
        }
    }
}