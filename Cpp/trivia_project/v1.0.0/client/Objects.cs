using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;


//connectors function/classes for mor easy calling to dll functions
namespace client
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

        public static void serializeSignOut(ref SignOutRequest req)
        {
            Wrapper.serializeSignOut(ref req);
        }

        public static void serializeStatus(ref PlayerStatusRequest req)
        {
            Wrapper.serializeStatus(ref req);
        }

        public static void serializeExit(ref ExitRequest req)
        {
            Wrapper.serializeExit(ref req);
        }

        public static void serializeTopPlayers(ref TopPlayerRequest req)
        {
            Wrapper.serializeTopPlayers(ref req);
        }

        public static void serializeListRoom()
        {
            Wrapper.serializeListRoom();
        }

        public static void serializeCreateRoom(ref CreateRoomRequest req)
        {
            Wrapper.serializeCreateRoom(ref req);
        }

        public static void serializeLeaveRoom(ref LeaveRoomRequest req)
        {
            Wrapper.serializeLeaveRoom(ref req);
        }

        public static void serializeJoinRoom(ref JoinRoomRequest req)
        {
            Wrapper.serializeJoinRoom(ref req);
        }

        public static void serializeListUsers(ref ListUserRequest req)
        {
            Wrapper.serializeListUsers(ref req);
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

        public static PlayerResultsResponse deserializePlayreStatusRequest()
        {
            return Wrapper.deserializePlayreStatusRequest();
        }

        public static TopPlayersResponse deserializeTopPlayersRequest()
        {
            return Wrapper.deserializeTopPlayersRequest();
        }

        public static listRoomsResponse deserializelistRoomsRequest()
        {
            return Wrapper.deserializelistRoomsRequest();
        }

        public static JoinRoomResponse deserializeJoinRoomResponse()
        {
            return Wrapper.deserializeJoinRoomResponse();
        }

        public static usersInRoomResponse deserializeUserInRoom()
        {
            return Wrapper.deserializeUserInRoom();
        }
    }
}


