namespace MvvmExampleStep8.Step8
{
	public class EraseDelegateCommand
	{
		public DelegateCommand Command { get; private set; }

		public ViewModel ViewModel { get; set; }

		public EraseDelegateCommand()
		{
			this.Command = new DelegateCommand(this.ExecuteErase, this.CanErase);
		}

		public void ExecuteErase(object unused)
		{
			this.ViewModel.Address = string.Empty;
			this.ViewModel.BirthDay = 1;
			this.ViewModel.BirthMonth = 1;
			this.ViewModel.BirthYear = 1990;
			this.ViewModel.IsMale = true;
			this.ViewModel.Name = string.Empty;
		}

		public bool CanErase(object unused)
		{
			return true;
		}
	}
}
