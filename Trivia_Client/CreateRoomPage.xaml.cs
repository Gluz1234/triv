using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Trivia_Client
{
    /// <summary>
    /// Interaction logic for CreateRoomPage.xaml
    /// </summary>
    public partial class CreateRoomPage : Page
    {
        private string _username;
        private Communicator _coms;

        public CreateRoomPage(string username, Communicator communicator)
        {
            InitializeComponent();
            _username = username;
            _coms = communicator;
        }

        private void CreateRoomButton_Click(object sender, RoutedEventArgs e)
        {
            string roomName = RoomNameTextBox.Text;
            int timePerQuestion = int.Parse(TimePerQuestionTextBox.Text);
            int numberOfPlayers = int.Parse(NumberOfPlayersTextBox.Text);
            int numOfQuestions = 5;
            messageInfo info = _coms.createRoomRequest(roomName, numberOfPlayers, numOfQuestions, timePerQuestion);
            AdminTextBlock.Text = $"Admin: {_username}";
            PlayersTextBlock.Text = "Players: " + _username;

        }
        private void GoBackButton_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.GoBack();
        }
    }
}
