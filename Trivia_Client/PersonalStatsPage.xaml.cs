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
    /// Interaction logic for PersonalStatsPage.xaml
    /// </summary>
    public partial class PersonalStatsPage : Page
    {
        private string _username;
        private Communicator _coms;
        public PersonalStatsPage(string username, Communicator coms)
        {
            InitializeComponent();
            _username = username;
            _coms = coms;
            messageInfo info = _coms.getStatisitcs();
            if (info.Code == 1)
            {
                MessageBox.Show(info.Json.ToString());
            }
            else
            {
                string[] stats = info.Json["Statistics"].ToString().Split('-');
                AVGTimeValue.Text += stats[0];
                TotalCorrectAnswersValue.Text += stats[1];
                TotalAnswersValue.Text += stats[2];
                TimesPlayedValue.Text += stats[3];
            }
        }
        private void GoBackButton_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.GoBack();
        }
    }
}
