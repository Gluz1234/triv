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
    /// Interaction logic for LoginPage.xaml
    /// </summary>
    public partial class LoginPage : Page
    {
        private Communicator _coms;
        public LoginPage()
        {
            InitializeComponent();
            _coms = new Communicator();
            
        }

        private void LoginButton_Click(object sender, RoutedEventArgs e)
        {
            string username = UsernameTextBox.Text;
            string password = PasswordBox.Password;
            messageInfo data = _coms.loginRequest(username, password);
            if(data.Code == 1) 
            {MessageBox.Show(data.Json.ToString());}
            else { NavigationService.Navigate(new MainMenuPage(username, _coms)); }         
        }

        private void SignupButton_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new SignupPage(_coms));
        }
    }
}
