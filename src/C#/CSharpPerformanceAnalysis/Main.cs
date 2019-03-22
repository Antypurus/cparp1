using System;
using System.Diagnostics;

namespace CSharpPerformanceAnalysis
{
    class Program
    {
        static void Main(string[] args)
        {
            SerialMatrix A = new SerialMatrix(4000, 4000, false, 2,512);
            SerialMatrix B = new SerialMatrix(4000, 4000, true, 2,512);

            Stopwatch sw = new Stopwatch();
            sw.Start();

            var C = A * B;

            sw.Stop();
            Console.WriteLine("Elapsed={0}", sw.Elapsed);
            Console.WriteLine(C.getValue(0, 0));
        }
    }
}
