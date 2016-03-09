using System.ComponentModel;

namespace MvvmExampleStep8.Step3
{
	public class ViewModel : INotifyPropertyChanged
	{
		private readonly Model model;

		public ViewModel(Model model)
		{
			this.model = model;
		}

		public event PropertyChangedEventHandler PropertyChanged;

		protected virtual void OnPropertyChanged(string propertyName)
		{
			var handler = PropertyChanged;
			if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
		}
	}
}