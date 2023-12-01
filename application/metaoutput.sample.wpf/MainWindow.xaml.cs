using System.Windows;

namespace metaoutput.sample.wpf
{
    public partial class MainWindow : Window
    {
        void DoNavigate(string url)
        {
            Title = "NAVIGATE TO: " + url;
        }

        public MainWindow()
        {
            {
                InitializeComponent();
            }
            {
                pattern.host.MetaOutput.Connect("6311C8B8-C0C5-42E5-887C-09ACCC30BE88", "MetaOutput.Sample.WPF", "1.0", DoNavigate);
            }
            {
                MetaOutputParent.Children.Add(pattern.host.MetaOutput.Update(0, 0, (int)MetaOutputParent.Width, (int)MetaOutputParent.Height, true) as FrameworkElement);
            }
        }

        ~MainWindow()
        {
            pattern.host.MetaOutput.Disconnect();
        }

        private void SendButton_Click(object sender, RoutedEventArgs e)
        {
            pattern.host.MetaOutput.SendTml(RequestTextBox.Text);
        }

        private void MetaOutputParent_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            pattern.host.MetaOutput.Update(0, 0, (int)e.NewSize.Width, (int)e.NewSize.Height, true);
        }
    }
}
