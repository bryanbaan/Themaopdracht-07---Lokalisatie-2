using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace THO7AlgorithmTimerApplication
{
    class C_SaltPepper : VisionAlgorithm
    {
        [DllImport("../ImageProcessing.dll"
            , EntryPoint = "#8"
            , CallingConvention = CallingConvention.StdCall)]
        private static extern void SaltPepper(IntPtr originalImageData, IntPtr newImageData, int width, int height, int percentage);

        int percentage;
        public C_SaltPepper(String name) : base(name) {
        }

        public void setPercentage(int p)
        {
            percentage = p;
        }
        public override System.Drawing.Bitmap DoAlgorithm(System.Drawing.Bitmap sourceImage)
        {
            int width = sourceImage.Width;
            int height = sourceImage.Height;
            Bitmap returnImage = new Bitmap(sourceImage);
            BitmapData imageData = sourceImage.LockBits(new Rectangle(0, 0, width, height), ImageLockMode.ReadOnly, PixelFormat.Format32bppRgb);
            BitmapData returnData = returnImage.LockBits(new Rectangle(0, 0, width, height), ImageLockMode.WriteOnly, PixelFormat.Format32bppRgb);

            SaltPepper(imageData.Scan0, returnData.Scan0, width, height, percentage);

            sourceImage.UnlockBits(imageData);
            returnImage.UnlockBits(returnData);
            return returnImage;
        }
    }
}
