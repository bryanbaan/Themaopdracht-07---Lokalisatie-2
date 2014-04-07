using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;

namespace THO7AlgorithmTimerApplication
{
    class C_BlackAlgorithm : VisionAlgorithm
    {
        [DllImport("../ImageProcessing.dll"
            , EntryPoint = "#2"
            , CallingConvention = CallingConvention.StdCall)]
        private static extern void Black(IntPtr imageData, int size);

        public C_BlackAlgorithm(String name) : base(name) { }
        public override System.Drawing.Bitmap DoAlgorithm(System.Drawing.Bitmap sourceImage)
        {
            Bitmap returnImage = new Bitmap(sourceImage.Width, sourceImage.Height);
            BitmapData returnData = returnImage.LockBits(new Rectangle(0, 0, returnImage.Width, returnImage.Height), ImageLockMode.WriteOnly, PixelFormat.Format32bppRgb);
            
            Black(returnData.Scan0, returnData.Width * returnData.Height * 4);

            returnImage.UnlockBits(returnData);
            return returnImage;
        }
    }
}