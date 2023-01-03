/*
* DESCRIPTION		:
* 	A program that get two args (file path, and file size)
* 	Creates a file and runs a TASK up to the file size you specify
* 	25 TASKs are set to meet requirements
*/
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using static System.Net.Mime.MediaTypeNames;

namespace a04
{
    internal class Program
    {
        // Constants
        public const string HELP = "Usage: Write <full path and file name> <size of file to be create>\n" +
                            "---- ex, [a04.exe C:/test/test.txt 100000] ----";
        public const int TASKS = 25;

        static void Main(string[] args)
        {
            string path = args[0];
            // Display Usage
            if (args[0] == "/?")
            {
                Console.WriteLine(HELP);
                return;
            }
            // check the exact args number
            if (args.Length != 2)
            {
                Console.WriteLine("Incorrect arguments");
                Console.WriteLine("Please use /? for help");
                return;
            }            

            int size;
            bool sizeCheck = int.TryParse(args[1], out size);
            // Check the minimum, maximum sizes and integer
            if (sizeCheck)
            {
                if (size < 1000 || size > 20000000)
                {
                    Console.WriteLine("The minimum size is 1,000, and the maximum size is 20,000,000");
                    return;
                }
            }
            else
            {
                Console.WriteLine("File size must be a valid integer");
                return;
            }

            string filename = Path.GetFileName(path);
            string directory = Path.GetDirectoryName(path);
            FileIO fio = new FileIO(path, size);
            // Check the path entered by the user is correct
            if (Path.IsPathRooted(path))
            {
                // Check the file name entered by the user is correct
                if (filename == null || filename == "")
                {
                    Console.WriteLine("Missing filename");
                    return ;
                }
                else
                {
                    // Check the path of the user exists and create a file
                    try
                    {
                        if (!Directory.Exists(directory))
                        {
                            Directory.CreateDirectory(directory);
                            fio.CreateFile(path);
                        }
                        else
                        {
                            if (!fio.CheckFileExists(path))
                            {
                                fio.CreateFile(path);
                            }
                            else
                            {
                                return;
                            }
                        }
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine("Exception: " + ex.ToString());
                    }
                }
            }
            else
            {
                Console.WriteLine(HELP);
                return ;
            }

            Task[] tasks = new Task[TASKS];
            Task checkSize = new Task(fio.CheckFileSize);
            // Run File Size Check Task
            checkSize.Start();      
            // Run All Tasks
            try
            {
                for (int i = 0; i < tasks.Length; i++)
                {
                    tasks[i] = new Task(fio.WriteRandomData);
                    tasks[i].Start();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception: " + ex.ToString());
            }


            Console.ReadKey();                        
        }       
    }
}
