using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace Interop
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct LoginRequest
    {

        [MarshalAs(UnmanagedType.LPStr)] public string _username;
        [MarshalAs(UnmanagedType.LPStr)] public string _password;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct SignUpRequest
    {

        [MarshalAs(UnmanagedType.LPStr)] public string _username;
        [MarshalAs(UnmanagedType.LPStr)] public string _password;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct LoginResponse
    {
        public uint status;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct SignUpResponse
    {
        public uint status;
    }


    class Wrapper
    {

        [DllImport("communicate_dll.dll")]
        public static extern void serializeLogin(ref LoginRequest req);

        [DllImport("communicate_dll.dll")]
        public static extern LoginResponse deserializeLogin();

        [DllImport("communicate_dll.dll")]
        public static extern void serializeSignUp(ref SignUpRequest req);

        [DllImport("communicate_dll.dll")]
        public static extern SignUpResponse deserializeSignUp();
        [DllImport("communicate_dll.dll")]
        public static extern SignUpResponse test5();
    }
}