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
    /// Interaction logic for JoinRoomPage.xaml
    /// </summary>
    public partial class JoinRoomPage : Page
    {
        private string _username;
        private Communicator _coms;

        public JoinRoomPage(string username, Communicator coms)
        {
            InitializeComponent();
            _username = username;
            _coms = coms;
            ActiveRoomsListBox.Items.Add("Room 1");
            ActiveRoomsListBox.Items.Add("Room 2");
        }

        private void JoinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            string selectedRoom = (string)ActiveRoomsListBox.SelectedItem;
            if (selectedRoom != null)
            {
                AdminTextBlock.Text = $"Admin: {selectedRoom} Admin";
                PlayersTextBlock.Text = "Players: " + _username;

            }
            else
            {
                MessageBox.Show("Please select a room to join.");
            }
        }
        private void GoBackButton_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.GoBack();
        }
    }
}
