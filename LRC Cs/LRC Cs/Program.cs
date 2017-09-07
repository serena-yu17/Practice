using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LRC_Cs
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Your CRC is:");
            Console.WriteLine(CalculateLRC("<STX>T00<FS>1.28<FS>01<FS>100<FS><FS>1<FS><FS><FS><FS><FS><ETX>"));
            Console.ReadLine();
        }

        public static char CalculateLRC(string toEncode)
        {
            byte[] bytes = Encoding.ASCII.GetBytes(toEncode);
            byte LRC = 0;
            for (int i = 0; i < bytes.Length; i++)
            {
                LRC ^= bytes[i];
            }
            return Convert.ToChar(LRC);
        }
    }
}
