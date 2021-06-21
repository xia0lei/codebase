using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace SocketAsyncClient
{
    internal sealed class SocketClient : IDisposable
    {
        private const Int32 ReceiveOperation = 1, SendOperation = 0;
        private Socket clientSocket;
        private Boolean connected = false;
        private IPEndPoint hostEndPoint;
        private static AutoResetEvent autoConnectEvent = new AutoResetEvent(false);
        private static AutoResetEvent[] autoSendReceiveEvents = new AutoResetEvent[]{
            new AutoResetEvent(false),
                new AutoResetEvent(false)
        };


        internal SocketClient(String hostName, Int32 port)
        {
            IPHostEntry host = Dns.GetHostEntry(hostName);
            IPAddress[] addressList = host.AddressList;
            hostEndPoint = new IPEndPoint(addressList[addressList.Length -1], port);
            clientSocket = new Socket(hostEndPoint.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
        }

        internal void Connect()
        {
            SocketAsyncEventArgs connectArgs = new SocketAsyncEventArgs();
            connectArgs.UserToken = clientSocket;
        }

        public void Dispose()
        {
            autoConnectEvent.Close();
            autoSendReceiveEvents[SendOperation].Close();
            autoSendReceiveEvents[ReceiveOperation].Close();
            if(clientSocket.Connected)
            {
                clientSocket.Close();
            }
        }
    }
}
