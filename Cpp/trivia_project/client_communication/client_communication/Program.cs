using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
namespace Interop
{
    class Program
    {
        static void Main(string[] args)
        {
            //example
            LoginRequest req;
            req._username = "hello";
            req._password = "bye";
            jsonSerializer.serializeLogin(ref req);

            LoginResponse a = jsonDeseriallizer.deserializeLogin();
            Console.WriteLine(a.status);
        }
    }
}
