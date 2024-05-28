using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace Trivia_Client
{
    enum RequestId
    {
        MT_RESPONSE_OK = 0,
        MT_LOGIN_REQUEST = 1,
        MT_SIGNUP_REQUEST = 2,
        MT_SIGNOUT_REQUEST = 3,
        MT_GET_ROOMS_REQUEST = 4,
        MT_GET_PLAYERS_IN_ROOM_REQUEST = 5,
        MT_GET_STATISTICS = 6,
        MT_GET_HIGHSCORES = 7,
        MT_JOIN_ROOM = 8,
        MT_CREATE_ROOM = 9,
        MT_CLOSE_ROOM = 10,
        MT_START_GAME = 11,
        MT_LEAVE_ROOM = 12,
        MT_EXIT = 99,
        MT_ERROR = 99
    };

    public class messageInfo
    {
        private int code;
        private JObject json;

        public messageInfo(String message)
        {
            Code = Convert.ToInt32(message[0]) - 48;
            int len = Convert.ToInt32(message.Substring(1, 4));
            string jsonStr = message.Substring(5, len);
            Json = JObject.Parse(jsonStr);
        }

        public int Code { get => code; set => code = value; }
        public JObject Json { get => json; set => json = value; }
    }
    public class Communicator
    {
        private NetworkStream clientStream;
        private TcpClient client;
        private IPEndPoint ipend;
        public Communicator()
        {
            this.client = new TcpClient();
            this.ipend = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 200);
            client.Connect(this.ipend);
            this.clientStream = this.client.GetStream();


        }
        public messageInfo loginRequest(string name, string password)
        {
            JObject o = new JObject
            {
                {"username",name},
                {"password",password }
            };

            byte[] buffer = new ASCIIEncoding().GetBytes(Serializer.serializeResponse((int)RequestId.MT_LOGIN_REQUEST, o));

            return new messageInfo(sendToServer(buffer));


        }
        public messageInfo signUpRequest(string name, string password, string email)
        {
            JObject o = new JObject
            {
                {"username",name},
                {"password",password },
                {"mail",email }
            };
            byte[] buffer = new ASCIIEncoding().GetBytes(Serializer.serializeResponse((int)RequestId.MT_SIGNUP_REQUEST, o));
            return new messageInfo(sendToServer(buffer));
        }
        public messageInfo getRoomsRequest()
        {
            JObject o = new JObject { };
            byte[] buffer = new ASCIIEncoding().GetBytes(Serializer.serializeResponse((int)RequestId.MT_GET_ROOMS_REQUEST, o));
            return new messageInfo(sendToServer(buffer));
        }
        public messageInfo joinRoomRequest(int roomId)
        {
            JObject o = new JObject
            {
                {"roomID",roomId }
            };
            byte[] buffer = new ASCIIEncoding().GetBytes(Serializer.serializeResponse((int)RequestId.MT_JOIN_ROOM, o));
            return new messageInfo(sendToServer(buffer));
        }
        public messageInfo getPlayersRequest(int roomId)
        {
            JObject o = new JObject
            {
                {"roomID",roomId }
            };
            byte[] buffer = new ASCIIEncoding().GetBytes(Serializer.serializeResponse((int)RequestId.MT_GET_PLAYERS_IN_ROOM_REQUEST, o));
            return new messageInfo(sendToServer(buffer));
        }
        public messageInfo signOutRequest()
        {
            JObject o = new JObject { };
            byte[] buffer = new ASCIIEncoding().GetBytes(Serializer.serializeResponse((int)RequestId.MT_SIGNOUT_REQUEST, o));
            return new messageInfo(sendToServer(buffer));
        }
        public messageInfo createRoomRequest(string roomName, int maxUsers, int qCount, int answerTime)
        {
            JObject o = new JObject
            {
                {"roomName",roomName },
                { "maxUsers",maxUsers},
                {"questionCount",qCount },
                {"answerTimeout",answerTime }


            };
            byte[] buffer = new ASCIIEncoding().GetBytes(Serializer.serializeResponse((int)RequestId.MT_CREATE_ROOM, o));
            return new messageInfo(sendToServer(buffer));
        }
        public messageInfo highScoreRequest()
        {
            JObject o = new JObject { };
            byte[] buffer = new ASCIIEncoding().GetBytes(Serializer.serializeResponse((int)RequestId.MT_GET_HIGHSCORES, o));
            return new messageInfo(sendToServer(buffer));

        }
        public messageInfo getStatisitcs()
        {
            JObject o = new JObject { };
            byte[] buffer = new ASCIIEncoding().GetBytes(Serializer.serializeResponse((int)RequestId.MT_GET_STATISTICS, o));
            return new messageInfo(sendToServer(buffer));
        }
        public messageInfo closeRoomRequest()
        {
            JObject o = new JObject { };
            byte[] buffer = new ASCIIEncoding().GetBytes(Serializer.serializeResponse((int)RequestId.MT_CLOSE_ROOM, o));
            return new messageInfo(sendToServer(buffer));
        }
        public messageInfo startGameRequest()
        {
            JObject o = new JObject { };
            byte[] buffer = new ASCIIEncoding().GetBytes(Serializer.serializeResponse((int)RequestId.MT_START_GAME, o));
            return new messageInfo(sendToServer(buffer));
        }
        private string sendToServer(byte[] buffer)
        {
            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();
            buffer = new byte[4096];
            int bytesRead = clientStream.Read(buffer, 0, 4096);
            return Encoding.UTF8.GetString(buffer);
        }
    }
}
