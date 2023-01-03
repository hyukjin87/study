/*
* DESCRIPTION		:
* 	A program that generates four types of arrays 
* 	and compares string search speed
* 	(string array, sorted string array, dictionary, hashtable)
*/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace a03
{
    internal class Program
    {
        // Constants
        public const int SMALL = 100;
        public const int MEDIUM = 100000;
        public const int LARGE = 5000000;
        static void Main(string[] args)
        {
            TestData tdSmall = new TestData(SMALL);
            TestData tdMedium = new TestData(MEDIUM);
            TestData tdLarge = new TestData(LARGE);

            // Compare the rate at which small amounts of data are retrieved
            Console.WriteLine("Small Search results:");
            tdSmall.GetRandomData(100);
            Console.WriteLine("Invalid Small Search results:");
            tdSmall.GetInvalidData(10);
            Console.WriteLine("");

            // Compare the rate at which medium amounts of data are retrieved
            Console.WriteLine("Medium Search results:");
            tdMedium.GetRandomData(100);
            Console.WriteLine("Invalid Medium Search results:");
            tdMedium.GetInvalidData(10);
            Console.WriteLine("");

            // Compare the rate at which large amounts of data are retrieved
            Console.WriteLine("Large Search results:");
            tdLarge.GetRandomData(100);
            Console.WriteLine("Invalid Large Search results:");
            tdLarge.GetInvalidData(10);

            Console.WriteLine("Press any key to end...");
            Console.ReadKey();
        }
    }
}
