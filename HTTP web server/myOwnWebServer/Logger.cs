/*
* DESCRIPTION		:
* 	Log server behavior to a log file
*/


using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;

namespace myOwnWebServer
{
    internal class Logger
    {
        /*
         * Method       : Log()
         * Description  : Check the path to create a file or add content to save the log
         * Parameters   : string message
         * Return       : void
         */
        public static void Log(string message)
        {
            string exePath = Assembly.GetExecutingAssembly().Location;
            string filePath = Path.GetDirectoryName(exePath);
            string path = filePath + "\\myOwnWebServer.log";
            try
            {
                // Generate logs based on the presence or absence of a file
                if (!File.Exists(path))
                {
                    using (StreamWriter sw = File.CreateText(path))
                    {
                        sw.WriteLine(DateTime.Now.ToString() + ": " + message.ToString());
                    }
                }
                else
                {
                    using (StreamWriter writer = File.AppendText(path))
                    {
                        writer.WriteLine(DateTime.Now.ToString() + ": " + message.ToString());
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }
    }
}
