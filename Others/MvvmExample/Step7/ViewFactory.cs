namespace MvvmExampleStep8.Step7
{
	public class ViewFactory
	{
		public ViewInfrastructure Create()
		{
			EraseDelegateCommand eraseDelegateCommand = new EraseDelegateCommand();
			SaveDelegateCommand saveDelegateCommand = new SaveDelegateCommand();
			Model model = new Model();
			ViewModel viewModel = new ViewModel(model, saveDelegateCommand.Command, eraseDelegateCommand.Command);
			View view = new View();

			return new ViewInfrastructure(view, viewModel, model);
		}
	}
}
