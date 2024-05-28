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
    /// Interaction logic for StatisticsPage.xaml
    /// </summary>
    public partial class StatisticsPage : Page
    {
        private string _username;
        private Communicator _coms;
        public StatisticsPage(string username, Communicator coms)
        {
            InitializeComponent();
            _username = username;
            _coms = coms;
        }

        private void PersonalStatsButton_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new PersonalStatsPage(_username,_coms));
        }

        private void BestScoresButton_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new BestStatsPage(_username, _coms));
        }
        private void GoBackButton_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.GoBack();
        }
    }
}
