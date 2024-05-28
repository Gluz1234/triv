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
    /// Interaction logic for MainMenuPage.xaml
    /// </summary>
    public partial class MainMenuPage : Page
    {
        private string _username;
        private Communicator _coms;

        public MainMenuPage(string username, Communicator communicator)
        {
            InitializeComponent();
            _username = username;
            _coms = communicator;
            UsernameTextBlock.Text = $"Welcome to MagshiTrivia: {_username}";
        }

        private void CreateRoomButton_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new CreateRoomPage(_username, _coms));
        }

        private void JoinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new JoinRoomPage(_username, _coms));
        }

        private void StatisticsButton_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new StatisticsPage(_username,_coms));
        }

        private void ExitButton_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }
    }
}

