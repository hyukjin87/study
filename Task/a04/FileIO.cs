/*
* DESCRIPTION		:
* 	It's a class that summarizes file-related methods
* 	It has the ability to create and check files and add arbitrary characters
*/
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace a04
{
    internal class FileIO
    {
        // Properties
        public static Mutex mutex = new Mutex();
        public static bool done = false;
        private string path { get; set; }
        private int size { get; set; }

        // Constructor
        public FileIO()
        { }

        // Constructor
        public FileIO(string fPath, int fSize)
        {
            this.path = fPath;
            this.size = fSize;
        }

        /*
         * Method       : CreateFile()
         * Description  : Create a file in the forwarded path
         * Parameters   : string fPath : file path
         * Return       : void
         */
        public void CreateFile(string fPath)
        {
            try
            {
                StreamWriter sw = File.CreateText(fPath);
                sw.Close();
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception: " + ex.ToString());
            }
            
        }

        /*
         * Method       : CheckFileExists()
         * Description  : Check the file exists
         * Parameters   : string fPath : file path
         * Return       : void
         */
        public bool CheckFileExists(string fPath)
        {
            try
            {
                if (File.Exists(fPath))
                {
                    Console.WriteLine("The file exists. Do you want to overwrite it?");
                    Console.WriteLine("If you want overwrite, Please press Y");
                    // Check the file is overwritten
                    ConsoleKeyInfo key = Console.ReadKey(true);
                    if (key.KeyChar == 'Y' || key.KeyChar == 'y')
                    {
                        CreateFile(fPath);
                    }
                    else
                    {
                        Console.WriteLine("Same file exists");
                    }
                    return true;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception: " + ex.ToString());
            }
            
            return false;
        }

        /*
         * Method       : WriteRandomData()
         * Description  : Add random data to the file
         * Parameters   : none
         * Return       : void
         */
        public void WriteRandomData()
        {
            while (!done)
            {
                mutex.WaitOne();
                try
                {
                    using (StreamWriter sw = File.AppendText(path))
                    {
                        sw.WriteLine(Guid.NewGuid().ToString());
                        sw.Close();
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Exception: " + ex.ToString());
                }
                finally
                {
                    mutex.ReleaseMutex();
                }
            }
        }

        /*
         * Method       : CheckFileSize()
         * Description  : Check the file size every 0.5 seconds
         *              : Exits the program when the file size is larger than the size you specify
         * Parameters   : none
         * Return       : void
         */
        public void CheckFileSize()
        {
            while (!done)
            {
                try
                {
                    long length = new FileInfo(path).Length;
                    Console.WriteLine("File size: " + length + " bytes");
                    if (length >= size)
                    {
                        done = true;
                    }
                    Thread.Sleep(500);
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Exception: " + ex.ToString());
                }
            }

            long finalLength = new FileInfo(path).Length;
            Console.WriteLine("Final size: " + path + " " + finalLength + " bytes");
        }
    }
}
