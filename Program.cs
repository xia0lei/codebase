using System;
class Program
{
    static void Main()
    {
        int packetSize = 10;
        Console.WriteLine("{0}", (byte)packetSize >> 8);
        Console.WriteLine("{0}", (byte)packetSize & 0xff);

        int[] a = {1,2,3,4,5,6,7,8,9,10};
        int[] copy = new int[a.Length];
        Console.WriteLine("Copy Length {0}, {1}", copy.Length, a[3]);
        a.CopyTo(copy, 3);
        foreach( var v in copy)
        {
            Console.WriteLine("{0}", v);
        }
    }
}
