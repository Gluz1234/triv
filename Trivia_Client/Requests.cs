using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace Trivia_Client
{
    public class Requests
    {

    }

    public class Login : Requests
    {
        private string _name;
        private string _password;

        public string Name { get => _name; set => _name = value; }
        public string Password { get => _password; set => _password = value; }
    }
    public class signUp : Requests
    {
        private string _name;
        private string _password;
        private string _email;

        public string Name { get => _name; set => _name = value; }
        public string Password { get => _password; set => _password = value; }
        public string Email { get => _email; set => _email = value; }
    }
    public class getPlayers : Requests
    {
        private string _roomId;

        public string RoomId { get => _roomId; set => _roomId = value; }
    }
    public class joinRoom : Requests
    {
        private string _roomId;

        public string RoomId { get => _roomId; set => _roomId = value; }
    }
    public class createRoom : Requests
    {
        private string _roomName;
        private int _maxUsers;
        private int _questionCount;
        private int _answerTimeOut;

        public string RoomName { get => _roomName; set => _roomName = value; }
        public int MaxUsers { get => _maxUsers; set => _maxUsers = value; }
        public int QuestionCount { get => _questionCount; set => _questionCount = value; }
        public int AnswerTimeOut { get => _answerTimeOut; set => _answerTimeOut = value; }
    }

}