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
    class C_Median11AlgorithmLum : VisionAlgorithm
    {
        [DllImport("../ImageProcessing.dll"
            , EntryPoint = "#6"
            , CallingConvention = CallingConvention.StdCall)]
        private static extern void Median_11_lum(IntPtr originalImageData, IntPtr newImageData, int width, int height);

        public C_Median11AlgorithmLum(String name) : base(name) { }
        public override System.Drawing.Bitmap DoAlgorithm(System.Drawing.Bitmap sourceImage)
        {
            int width = sourceImage.Width;
            int height = sourceImage.Height;
            Bitmap returnImage = new Bitmap(sourceImage);
            BitmapData imageData = sourceImage.LockBits(new Rectangle(0, 0, width, height), ImageLockMode.ReadOnly, PixelFormat.Format32bppRgb);
            BitmapData returnData = returnImage.LockBits(new Rectangle(0, 0, width, height), ImageLockMode.WriteOnly, PixelFormat.Format32bppRgb);

            Median_11_lum(imageData.Scan0, returnData.Scan0, width, height);

            sourceImage.UnlockBits(imageData);
            returnImage.UnlockBits(returnData);
            return returnImage;
        }
    }
}