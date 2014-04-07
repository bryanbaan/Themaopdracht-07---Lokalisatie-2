using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace THO7AlgorithmTimerApplication
{
    class C_FindLicenseplate : VisionAlgorithm
    {
        [DllImport("../ImageProcessing.dll"
            , EntryPoint = "#9"
            , CallingConvention = CallingConvention.StdCall)]

        private static extern void SearchLicenseplateCoordinates(IntPtr originalImageData, IntPtr newImageData, int width, int height);

        public C_FindLicenseplate(String name) : base(name) {
        }

        public override System.Drawing.Bitmap DoAlgorithm(System.Drawing.Bitmap sourceImage)
        {
            int width = sourceImage.Width;
            int height = sourceImage.Height;
            Bitmap returnImage = new Bitmap(sourceImage);
            BitmapData imageData = sourceImage.LockBits(new Rectangle(0, 0, width, height), ImageLockMode.ReadOnly, PixelFormat.Format32bppRgb);
            BitmapData returnData = returnImage.LockBits(new Rectangle(0, 0, width, height), ImageLockMode.WriteOnly, PixelFormat.Format32bppRgb);

            SearchLicenseplateCoordinates(imageData.Scan0, returnData.Scan0, width, height);

            sourceImage.UnlockBits(imageData);
            returnImage.UnlockBits(returnData);
            return returnImage;
        }

    }
}
