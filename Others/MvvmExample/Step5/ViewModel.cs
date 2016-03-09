using System;
using System.ComponentModel;

namespace MvvmExampleStep8.Step5
{
	public class ViewModel : INotifyPropertyChanged
	{
		private readonly Model model;

		public string Name
		{
			get
			{
				return this.model.Name;
			}
			set
			{
				if (this.model.Name != value)
				{
					this.model.Name = value;
					this.OnPropertyChanged("Name");
				}
			}
		}

		public string Address
		{
			get
			{
				return this.model.Address;
			}
			set
			{
				if (this.model.Address != value)
				{
					this.model.Address = value;
					this.OnPropertyChanged("Address");
				}
			}
		}

		public bool IsMale
		{
			get
			{
				return this.model.IsMale;
			}
			set
			{
				if (this.model.IsMale != value)
				{
					this.model.IsMale = value;
					this.OnPropertyChanged("IsMale");
				}
			}
		}

		public int BirthDay
		{
			get
			{
				return this.model.BirthDate.Day;
			}
			set
			{
				if (this.model.BirthDate.Day != value)
				{
					this.model.BirthDate = new DateTime(this.model.BirthDate.Year, this.model.BirthDate.Month, value);
					this.OnPropertyChanged("BirthDay");
				}
			}
		}

		public int BirthMonth
		{
			get
			{
				return this.model.BirthDate.Month;
			}
			set
			{
				if (this.model.BirthDate.Month != value)
				{
					this.model.BirthDate = new DateTime(this.model.BirthDate.Year, value, this.model.BirthDate.Day);
					this.OnPropertyChanged("BirthMonth");
				}
			}
		}

		public int BirthYear
		{
			get
			{
				return this.model.BirthDate.Year;
			}
			set
			{
				if (this.model.BirthDate.Year != value)
				{
					this.model.BirthDate = new DateTime(value, this.model.BirthDate.Month, this.model.BirthDate.Day);
					this.OnPropertyChanged("BirthYear");
				}
			}
		}

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