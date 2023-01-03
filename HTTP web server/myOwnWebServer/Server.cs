/*
* DESCRIPTION		:
* 	Runs the server and validates the values requested by the client
*   Responses the value to the client based on its validity
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Web;
using System.Security.Cryptography;
using System.Data;
using System.IO;
using System.Reflection;

namespace myOwnWebServer
{
    internal class Server
    {
        // Properties
        public string webRoot { get; set; }
        public string webIP { get; set; }
        public string webPort { get; set; }
        public volatile bool Done = false;

        /*
         * Method       : StartServer()
         * Description  : The method that runs the server
         * Parameters   : none
         * Return       : void
         */
        public void StartServer()
        {
            TcpListener server = null;
            try
            {
                // Set the TcpListener on port.
                Int32 port = Int32.Parse(webPort);
                IPAddress ip = IPAddress.Parse(webIP);

                // TcpListener server = new TcpListener(port);
                server = new TcpListener(ip, port);

                // Start listening for client requests.
                server.Start();

                // Enter the listening loop.
                while (!Done)
                {
                    // check the clients pending
                    if (server.Pending())
                    {
                        // Perform a blocking call to accept requests.
                        // You could also user server.AcceptSocket() here.
                        Socket client = server.AcceptSocket();
                        ParameterizedThreadStart ts = new ParameterizedThreadStart(RequestData);
                        Thread clientThread = new Thread(ts);
                        clientThread.Start(client);
                    }
                }
            }
            catch (SocketException e)
            {
                Logger.Log("[SocketException]: {0}" + e);
            }
            finally
            {
                // Stop listening for new clients.
                server.Stop();
                Done = true;
            }
        }

        /*
         * Method       : RequestData()
         * Description  : Method for validating request data
         * Parameters   : object o
         * Return       : void
         */
        public void RequestData(object o)
        {
            // request start line properties
            string startLineMethod;
            string startLineURL;
            string startLineVersion;
            string startLine;
            int startLineCount;

            // responses status line properties
            string statusLineCode;
            string responsesDate = DateTime.Now.ToString();
            string responsesServer = "myOwnWebServer";
            string responsesType = "text/html";
            string responsesBody;            
            int responsesEntityCount;

            Socket client = (Socket)o;
            // Buffer for reading data
            Byte[] bytes = new Byte[8192];

            int i;

            try
            {
                // Loop to receive all the data sent by the client.
                while ((i = client.Receive(bytes, bytes.Length, 0)) != 0)
                {
                    // Translate data bytes to a ASCII string.
                    String dataSet = System.Text.Encoding.ASCII.GetString(bytes, 0, i);

                    startLineMethod = dataSet.Split(' ')[0];
                    startLineURL = dataSet.Split(' ')[1];

                    // Request Log
                    Logger.Log("[Request]: " + startLineMethod + ", " + startLineURL);

                    startLine = dataSet.Split('\r')[0];
                    startLineCount = startLine.Split(' ').Length;

                    // check the start line count
                    if (startLineCount != 3)
                    {
                        statusLineCode = "400 Bad Request";
                        responsesBody = "<!DOCTYPE html><html><body>" + statusLineCode + "</body></html>";
                        responsesEntityCount = responsesBody.Length;
                        SendText(statusLineCode, responsesType, responsesEntityCount, responsesServer, responsesDate, responsesBody, client);
                        client.Close();
                        return;
                    }

                    startLineVersion = dataSet.Split(' ')[2];
                    startLineVersion = startLineVersion.Split('\r')[0];


                    // check the http version
                    if (startLineVersion != "HTTP/1.1")
                    {
                        statusLineCode = "505 HTTP Version Not Supported";
                        responsesBody = "<!DOCTYPE html><html><body>" + statusLineCode + "</body></html> ";
                        responsesEntityCount = responsesBody.Length;
                        SendText(statusLineCode, responsesType, responsesEntityCount, responsesServer, responsesDate, responsesBody, client);
                        client.Close();
                        return;
                    }

                    startLineURL = dataSet.Split(' ')[1];
                    string path = webRoot + startLineURL;

                    // check the file path
                    if (!File.Exists(path))
                    {
                        statusLineCode = "404 Not Found";
                        responsesBody = "<!DOCTYPE html><html><body>" + statusLineCode + "</body></html> ";
                        responsesEntityCount = responsesBody.Length;
                        SendText(statusLineCode, responsesType, responsesEntityCount, responsesServer, responsesDate, responsesBody, client);
                        client.Close();
                        return;
                    }

                    string type = startLineURL.Split('.')[1];
                    type = type.ToLower();

                    // check the file type
                    if (type == "acgi" || type == "htm" || type == "html" || type == "htmls" || type == "htx" || type == "shtml")
                    {
                        statusLineCode = "200 OK";
                        responsesType = "text/html";
                        responsesBody = File.ReadAllText(path);
                        responsesEntityCount = responsesBody.Length;
                        SendText(statusLineCode, responsesType, responsesEntityCount, responsesServer, responsesDate, responsesBody, client);
                        client.Close();
                        return;
                    }
                    else if (type == "txt")
                    {
                        statusLineCode = "200 OK";
                        responsesType = "text/plain";
                        responsesBody = File.ReadAllText(path);
                        responsesEntityCount = responsesBody.Length;
                        SendText(statusLineCode, responsesType, responsesEntityCount, responsesServer, responsesDate, responsesBody, client);
                        client.Close();
                        return;
                    }
                    else if (type == "jfif" || type == "jpe" || type == "jpeg" || type == "jpg")
                    {
                        statusLineCode = "200 OK";
                        responsesType = "image/jpeg";
                        Byte[] imageBody = File.ReadAllBytes(path);
                        responsesEntityCount = imageBody.Length;
                        SendImage(statusLineCode, responsesType, responsesEntityCount, responsesServer, responsesDate, imageBody, client);
                        client.Close();
                        return;
                    }
                    else if (type == "gif")
                    {
                        statusLineCode = "200 OK";
                        responsesType = "image/gif";
                        Byte[] imageBody = File.ReadAllBytes(path);
                        responsesEntityCount = imageBody.Length;
                        SendImage(statusLineCode, responsesType, responsesEntityCount, responsesServer, responsesDate, imageBody, client);
                        client.Close();
                        return;
                    }
                    else
                    {
                        statusLineCode = "415 Unsupported Media Type";
                        responsesBody = "<!DOCTYPE html><html><body>" + statusLineCode + "</body></html> ";
                        responsesEntityCount = responsesBody.Length;
                        SendText(statusLineCode, responsesType, responsesEntityCount, responsesServer, responsesDate, responsesBody, client);
                        client.Close();
                        return;
                    }
                }
            }
            catch (Exception ex)
            {
                Logger.Log("[Exception]: " + ex.ToString());
            }

            // Shutdown and end connection
            client.Close();

        }


        /*
        * Method       : SendText()
        * Description  : A method for setting data to pass to the client
        * Parameters   : string code    : Status Line Code
        *                string type    : Responses Type
        *                int length     : Responses Entity Count
        *                string server  : Responses Server
        *                string date    : Responses Date
        *                string body    : Responses Body
        *                object o       : Sokect client object
        * Return       : void
        */
        public static void SendText(string code, string type, int length, string server, string date, string body, object o)
        {
            try
            {
                Socket client = (Socket)o;
                string responses = "HTTP/1.1 " + code + "\r\n"
                                               + "Content-Type: " + type + "\r\n"
                                               + "Server: " + server + "\r\n"
                                               + "Date: " + date + "\r\n"
                                               + "Content-Length: " + length + "\r\n"
                                               + "\r\n"
                                               + body;

                Byte[] responsesData = System.Text.Encoding.ASCII.GetBytes(responses);
                client.Send(responsesData);
                Logger.Log("[Responses]: " + code + ", " + type + ", " + server + ", " + date + ", " + length);
            }
            catch (Exception ex)
            {
                Logger.Log("Exception: " + ex.ToString());
            }
            
            
        }

        /*
        * Method       : SendImage()
        * Description  : A method for setting data to pass to the client
        * Parameters   : string code    : Status Line Code
        *                string type    : Responses Type
        *                int length     : Responses Entity Count
        *                string server  : Responses Server
        *                string date    : Responses Date
        *                byte[] body    : Responses Body
        *                object o       : Sokect client object
        * Return       : void
        */
        public static void SendImage(string code, string type, int length, string server, string date, byte[] body, object o)
        {
            try
            {
                Socket client = (Socket)o;
                string responses = "HTTP/1.1 " + code + "\r\n"
                                               + "Content-Type: " + type + "\r\n"
                                               + "Server: " + server + "\r\n"
                                               + "Date: " + date + "\r\n"
                                               + "Content-Length: " + length + "\r\n"
                                               + "\r\n";

                Byte[] responsesData = System.Text.Encoding.ASCII.GetBytes(responses);
                Byte[] imageResponses = new byte[responsesData.Length + body.Length];
                Buffer.BlockCopy(responsesData, 0, imageResponses, 0, responsesData.Length);
                Buffer.BlockCopy(body, 0, imageResponses, responsesData.Length, body.Length);

                client.Send(imageResponses);
                Logger.Log("[Responses]: " + code + ", " + type + ", " + server + ", " + date + ", " + length);
            }
            catch (Exception ex)
            {
                Logger.Log("Exception: " + ex.ToString());
            }
        }
    }
}
