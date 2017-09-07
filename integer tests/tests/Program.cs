using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace tests
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                string input;
                int flag=0;
                WriteColor wrc=new WriteColor("Enter an integer:");
                input = Console.ReadLine();
                input = input.Trim();
                input = input.Replace(" ", "");
                if (!int.TryParse(input,out flag))
                {
                    wrc=new WriteColor("This is not an integer"+"\n");
                    Console.Beep(3000,500);
                }
                else
                {
                    wrc=new WriteColor(input+"\n");
                }
            }
        }
    }
    class WriteColor
    {
        public WriteColor(string strin)
        {
            str=strin;
            WriteC(str);
            }
        private void WriteC(string strout)
        {
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine(strout);
            Console.ResetColor();
        }
       private string str;
    }
}
