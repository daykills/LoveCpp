namespace MvvmExampleStep8.Step7
{
	public class EraseDelegateCommand
	{
		public DelegateCommand Command { get; private set; }

		public EraseDelegateCommand()
		{
			this.Command = new DelegateCommand(this.ExecuteErase, this.CanErase);
		}

		public void ExecuteErase(object unused)
		{

		}

		public bool CanErase(object unused)
		{
			return true;
		}

	}
}
