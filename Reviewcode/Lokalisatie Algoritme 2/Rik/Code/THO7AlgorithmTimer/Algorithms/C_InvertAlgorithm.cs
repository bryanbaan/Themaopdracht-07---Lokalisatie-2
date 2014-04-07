using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;

namespace THO7AlgorithmTimerApplication
{
    class C_InvertAlgorithm : VisionAlgorithm
    {
        [DllImport("../ImageProcessing.dll"
            , EntryPoint = "#4"
            , CallingConvention = CallingConvention.StdCall)]
        private static extern void Invert(IntPtr originalImageData, IntPtr newImageData, int size);


        public C_InvertAlgorithm(String name) : base(name) { }

        public override System.Drawing.Bitmap DoAlgorithm(System.Drawing.Bitmap sourceImage)
        {
            int originalWidth = sourceImage.Width;
            int originalHeight = sourceImage.Height;
            Bitmap returnImage = new Bitmap(sourceImage.Width, sourceImage.Height);
            BitmapData originalData = sourceImage.LockBits(new Rectangle(0, 0, originalWidth, originalHeight), ImageLockMode.ReadOnly, PixelFormat.Format32bppRgb);
            BitmapData returnData = returnImage.LockBits(new Rectangle(0, 0, originalWidth, originalHeight), ImageLockMode.WriteOnly, PixelFormat.Format32bppRgb);

            Invert(originalData.Scan0, returnData.Scan0, originalWidth*originalHeight*4);

            sourceImage.UnlockBits(originalData);
            returnImage.UnlockBits(returnData);

            return returnImage;
        }
    }
}