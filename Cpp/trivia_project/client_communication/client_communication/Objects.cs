using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;


/*
 connectors functions and interfaces to connecting the c++ imported library.
*/
namespace Interop
{
    class jsonSerializer
    {
        public static void serializeLogin(ref LoginRequest req)
        {
            Wrapper.serializeLogin(ref req);
        }

        public static void serializeSignUp(ref SignUpRequest req)
        {
            Wrapper.serializeSignUp(ref req);
        }
    }

    class jsonDeseriallizer
    {
        public static LoginResponse deserializeLogin()
        {
            return Wrapper.deserializeLogin();
        }

        public static SignUpResponse deserializeSignUp()
        {
            return Wrapper.deserializeSignUp();
        }
    }
}