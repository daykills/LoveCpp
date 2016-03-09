namespace MvvmExampleStep8.Step8
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

			eraseDelegateCommand.ViewModel = viewModel;
			saveDelegateCommand.ViewModel = viewModel;

			return new ViewInfrastructure(view, viewModel, model);
		}
	}
}
