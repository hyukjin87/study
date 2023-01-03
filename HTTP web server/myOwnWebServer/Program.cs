/*
* DESCRIPTION		:
* 	A server program that uses TCP Listener 
* 	It is responsible for sending and receiving http messages to and from clients
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace myOwnWebServer
{
    internal class Program
    {
        // Properties
        public static string webRoot { get; set; }
        public static string webIP { get; set; }
        public static string webPort { get; set; }

        static void Main(string[] args)
        {
            if(ParseArgs(args))
            {
                Server server = new Server();
                // Setting the Server properties
                server.webRoot = webRoot;
                server.webIP = webIP;
                server.webPort = webPort;

                // Server Start Log
                Logger.Log("[Start Server]: " + webRoot + ", " + webIP + ", " + webPort);
                server.StartServer();
            }

            Console.WriteLine("Press Enter to End");
            Console.ReadLine();

            // Server Stop Log
            Logger.Log("[SERVER STOP]");            
        }


        /*
         * Method       : ParseArgs()
         * Description  : Split the input arguments in the console window
         * Parameters   : string[] args
         * Return       : void
         */
        public static bool ParseArgs(string[] args)
        {
            // count args
            if(args.Length == 3)
            {
                string root = args[0].Split('=')[0];
                string ip = args[1].Split('=')[0];
                string port = args[2].Split('=')[0];

                // set the webRoot, webIP, and webPort
                if(root == "-webRoot" && ip == "-webIP" && port == "-webPort")
                {
                    webRoot = args[0].Split('=')[1];
                    webIP = args[1].Split('=')[1];
                    webPort = args[2].Split('=')[1];
                    return true;
                }
                else
                {
                    Logger.Log("[ERROR]: Incorrect argument format.");
                    return false;
                }
            }
            else
            {
                Logger.Log("[ERROR]: Incorrect number of arguments");
                return false;
            }
        }
    }
}
