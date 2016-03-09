using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace MvvmExample.ViewModel
{
    public class SaveDelegateCommand
	{
		private PersonViewModel viewModel;

		public DelegateCommand Command { get; private set; }

        public PersonViewModel ViewModel
		{
			get
			{
				return viewModel;
			}
			set
			{
				if (viewModel != value)
				{
					if (viewModel != null)
					{
						viewModel.PropertyChanged -= this.OnViewModelPropertyChanged;	
					}
					viewModel = value;
					viewModel.PropertyChanged += this.OnViewModelPropertyChanged;
				}
			}
		}

		public SaveDelegateCommand()
		{
			this.Command = new DelegateCommand(this.ExecuteSave, this.CanSave);
		}

		public void ExecuteSave(object unused)
		{
			MessageBox.Show("Save done");
		}

		public bool CanSave(object unused)
		{
			return this.ViewModel.BirthYear != 1 && !string.IsNullOrEmpty(this.ViewModel.Address) && !string.IsNullOrEmpty(this.ViewModel.Name);
		}

		private void OnViewModelPropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
		{
			this.Command.RaiseCanExecuteChanged();
		}
	}
}
