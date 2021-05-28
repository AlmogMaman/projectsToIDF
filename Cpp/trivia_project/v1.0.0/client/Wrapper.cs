using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace client
{
    //the import of the c++ Dll library
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
    public struct SignOutRequest
    {

        [MarshalAs(UnmanagedType.LPStr)] public string _username;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct PlayerStatusRequest
    {
        [MarshalAs(UnmanagedType.LPStr)] public string _name;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct ExitRequest
    {

        [MarshalAs(UnmanagedType.LPStr)] public string _username;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct TopPlayerRequest
    {
        [MarshalAs(UnmanagedType.LPStr)] public string _username;
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

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct PlayerResultsResponse
    {
        public uint gamesPlayed;
        public uint gamesWin;
        public uint correctAnswerCount;
        public uint wrongAnswerCount;
        public float averageAnswerTime;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct TopPlayersResponse
    {
        public uint place;
        public IntPtr first;
        public IntPtr secound;
        public IntPtr third;
    }


    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct listRoomsResponse
    {
        public IntPtr name;
        public uint numOfPlayers;
        public uint maxNum;
        public uint lvl;
        public uint id;
        public unsafe listRoomsResponse* next;
    }


    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct LeaveRoomRequest
    {
        [MarshalAs(UnmanagedType.LPStr)] public string _username;
        public uint _roomId;
        public uint _admin;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct JoinRoomRequest
    {
        [MarshalAs(UnmanagedType.LPStr)] public string _username;
        public uint _roomId;
    }




    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct CreateRoomRequest
    {
        [MarshalAs(UnmanagedType.LPStr)] public string adminName;
        [MarshalAs(UnmanagedType.LPStr)] public string roomName;
        public uint maxUsers;
        public uint questionCount;
        public uint ansCount;
        public uint answerTimeout;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct JoinRoomResponse
    {
        public uint enter;
        public IntPtr roomName;
        public uint maxUsers;
        public uint questionCount;
        public uint ansCount;
        public uint answerTimeout;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct usersInRoomResponse
    {
        public IntPtr name;
        public unsafe usersInRoomResponse* next;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct ListUserRequest
    {
        public uint _roomId;
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
        public static extern void serializeSignOut(ref SignOutRequest req);


        [DllImport("communicate_dll.dll")]
        public static extern void serializeStatus(ref PlayerStatusRequest req);

        [DllImport("communicate_dll.dll")]
        public static extern PlayerResultsResponse deserializePlayreStatusRequest();


        [DllImport("communicate_dll.dll")]
        public static extern void serializeExit(ref ExitRequest req);


        [DllImport("communicate_dll.dll")]
        public static extern void serializeTopPlayers(ref TopPlayerRequest req);


        [DllImport("communicate_dll.dll")]
        public static extern TopPlayersResponse deserializeTopPlayersRequest();

        [DllImport("communicate_dll.dll")]
        public static extern void serializeListRoom();

        [DllImport("communicate_dll.dll")]
        public static extern listRoomsResponse deserializelistRoomsRequest();

        [DllImport("communicate_dll.dll")]
        public static extern void serializeCreateRoom(ref CreateRoomRequest req);


        [DllImport("communicate_dll.dll")]
        public static extern void serializeLeaveRoom(ref LeaveRoomRequest req);

        [DllImport("communicate_dll.dll")]
        public static extern void serializeJoinRoom(ref JoinRoomRequest req);

        [DllImport("communicate_dll.dll")]
        public static extern JoinRoomResponse deserializeJoinRoomResponse();

        [DllImport("communicate_dll.dll")]
        public static extern void serializeListUsers(ref ListUserRequest req);

        [DllImport("communicate_dll.dll")]
        public static extern usersInRoomResponse deserializeUserInRoom();

    }
}