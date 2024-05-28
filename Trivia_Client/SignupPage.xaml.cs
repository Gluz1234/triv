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
    /// Interaction logic for SignupPage.xaml
    /// </summary>
    public partial class SignupPage : Page
    {
        private Communicator _coms;
        public SignupPage(Communicator communicator)
        {
            _coms = communicator;
            InitializeComponent();
        }

        private void SignupButton_Click(object sender, RoutedEventArgs e)
        {
            string username = NewUsernameTextBox.Text;
            string password = NewPasswordBox.Password;
            string email = NewEmailTextBox.Text;
            messageInfo data = _coms.signUpRequest(username, password, email);
            if (data.Code == 1)
            {MessageBox.Show(data.Json.ToString());}
            else
            {NavigationService.Navigate(new MainMenuPage(username, _coms));}
        }

        private void BackToLoginButton_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new LoginPage());
        }
    }
}
