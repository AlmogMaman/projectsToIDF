using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using System.Runtime.InteropServices;


namespace client
{

    

    //class Person
    //{
    //    public string username { get; set; }
    //    public string password { get; set; }
    //}


    class communication
    {

        public uint login(string us, string pa)
        {
            LoginRequest req;
            req._username = us;
            req._password = pa;
            jsonSerializer.serializeLogin(ref req);

            return jsonDeseriallizer.deserializeLogin().status;
        }

        public uint Signup(string us, string pa)
        {
            SignUpRequest req;
            req._username = us;
            req._password = pa;
            jsonSerializer.serializeSignUp(ref req);

            return jsonDeseriallizer.deserializeSignUp().status;
        }

        public void Signout(string us)
        {
            SignOutRequest req;
            req._username = us;
            jsonSerializer.serializeSignOut(ref req);
            
        }

        public bool exit(string us)
        {
            ExitRequest req;
            req._username = us;
            jsonSerializer.serializeExit(ref req);
            
            return true;
        }

        public TopPlayersResponse get_top_players(string name)
        {
            TopPlayerRequest req;
            req._username = name;
            jsonSerializer.serializeTopPlayers(ref req);

            return jsonDeseriallizer.deserializeTopPlayersRequest();
        }


        public PlayerResultsResponse get_status(string name)
        {
            PlayerStatusRequest req;
            req._name = name;
            jsonSerializer.serializeStatus(ref req);

            return jsonDeseriallizer.deserializePlayreStatusRequest();
        }

        public listRoomsResponse get_room_list()
        {
            jsonSerializer.serializeListRoom();
            return jsonDeseriallizer.deserializelistRoomsRequest();
        }

        public bool create_room(string username, string roomName, int maxUsers, int questionCount, int ansCount, int answerTimeout)
        {
            CreateRoomRequest newRoom;
            newRoom.adminName = username;
            newRoom.ansCount = (uint)ansCount;
            newRoom.answerTimeout = (uint)answerTimeout;
            newRoom.maxUsers = (uint)maxUsers;
            newRoom.questionCount = (uint)questionCount;
            newRoom.roomName = roomName;
            jsonSerializer.serializeCreateRoom(ref newRoom);

            return true;
        }

        public JoinRoomResponse join_room(uint id,string usename)
        {
            JoinRoomRequest req;
            req._roomId = id;
            req._username = usename;
            jsonSerializer.serializeJoinRoom(ref req);

            return jsonDeseriallizer.deserializeJoinRoomResponse();
        }

        public void leave_room(uint id, string usename, bool admin)
        {
            LeaveRoomRequest req;
            req._roomId = id;
            req._username = usename;
            if(admin)
                req._admin = 1;
            else
                req._admin = 0;
            jsonSerializer.serializeLeaveRoom(ref req);
            
        }

        public usersInRoomResponse users_in_room(uint id)
        {
            ListUserRequest req;
            req._roomId = id;
            jsonSerializer.serializeListUsers(ref req);

            return jsonDeseriallizer.deserializeUserInRoom();
        }






        //string StringToBinary(string data)
        //{
        //    StringBuilder sb = new StringBuilder();

        //    foreach (char c in data.ToCharArray())
        //    {
        //        sb.Append(Convert.ToString(c, 2).PadLeft(8, '0'));
        //    }
        //    return sb.ToString();
        //}

        //static string BinaryToString(string data)
        //{
        //    List<Byte> byteList = new List<Byte>();

        //    for (int i = 0; i < data.Length; i += 8)
        //    {
        //        byteList.Add(Convert.ToByte(data.Substring(i, 8), 2));
        //    }
        //    return Encoding.ASCII.GetString(byteList.ToArray());
        //}
    }
}