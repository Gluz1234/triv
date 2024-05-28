using Newtonsoft.Json.Linq;
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
    /// Interaction logic for BestStatsPage.xaml
    /// </summary>
    public partial class BestStatsPage : Page
    {
        private string _username;
        private Communicator _coms;

        public BestStatsPage(string username ,Communicator communicator)
        {
            InitializeComponent();
            _coms = communicator;
            LoadHighScores();
            _username = username;
        }

        private void LoadHighScores()
        {
            try
            {
                messageInfo data = _coms.highScoreRequest();
                JToken highScores = data.Json["Highscores"];
                foreach (var score in highScores.ToString().Split('-'))
                {
                    if (!string.IsNullOrEmpty(score))
                    {
                        string[] scoreDetails = score.Split('=');
                        TextBlock scoreTextBlock = new TextBlock
                        {
                            Text = $"{scoreDetails[0]}: {scoreDetails[1]}",
                            Margin = new Thickness(5)
                        };
                        ScoresStackPanel.Children.Add(scoreTextBlock);
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Error loading high scores: {ex.Message}");
            }
        }

        private void GoBackButton_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.GoBack();
        }
    }
}
