using System;
using System.Net;
using System.Net.Sockets;

public class UserToken
{
    public string IP{get;set;}
    public int Port{get;set;}
}

class TestClientRaw
{

    public static Socket m_socket;
    public static SocketAsyncEventArgs m_writeEvent = new SocketAsyncEventArgs();
    public static SocketAsyncEventArgs m_readEvent = new SocketAsyncEventArgs();

    private static void OnConnectComplete(object o)
    {
        SocketAsyncEventArgs args = o as SocketAsyncEventArgs;
        Console.WriteLine(String.Format("{0}", args.SocketError));
        if(args.SocketError == SocketError.Success)
        {
            Console.WriteLine("Connect Success");
        }
        else{
            Console.WriteLine(String.Format("Connect failed, {0}", args.SocketError));
        }
        m_socket.Close();
    }

    private static void IO_Complete(object sender, object o)
    {
        SocketAsyncEventArgs args = o as SocketAsyncEventArgs;
        switch(args.LastOperation)
        {
            case SocketAsyncOperation.Connect:
                {
                    Console.WriteLine("IO_Complete Connect");
                }
                break;
            case SocketAsyncOperation.Disconnect:
                {
                    Console.WriteLine("Disconnect");
                }
                break;
            default:
                break;
        }
    }

    public static void BeginConnect(IPEndPoint endPoint)
    {
        m_writeEvent.RemoteEndPoint = endPoint;
        bool willRaiseEvent = m_socket.ConnectAsync(m_writeEvent);
        if(!willRaiseEvent)
        {
            OnConnectComplete(m_writeEvent);
        }
    }

    static void Main(string[] args)
    {
        m_socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        var address = IPAddress.Parse("127.0.0.1");
        var endPoint = new IPEndPoint(address, 8888);

        m_writeEvent.Completed += IO_Complete;
        BeginConnect(endPoint);
        Console.ReadKey();
    }
}
