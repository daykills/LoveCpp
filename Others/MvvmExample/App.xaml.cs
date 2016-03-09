using System.Diagnostics.CodeAnalysis;
using System.Windows;
using MvvmExampleStep8.Step2;

namespace MvvmExampleStep8
{
	[SuppressMessage("ReSharper", "UnusedMember.Local")]
	public partial class App : Application
	{
		private void App_OnStartup(object sender, StartupEventArgs e)
		{
			// this.Step2(); Uncomment to use the example of the step 2
			// this.Step3(); Uncomment to use the example of the step 3
			// this.Step4(); Uncomment to use the example of the step 4
			// this.Step5(); Uncomment to use the example of the step 5
			// this.Step6(); Uncomment to use the example of the step 6
			// this.Step7(); Uncomment to use the example of the step 7
			this.Step8();
		}

		private void Step2()
		{
			ViewFactory factory = new ViewFactory();

			ViewInfrastructure infrastructure = factory.Create();

			infrastructure.View.DataContext = infrastructure.ViewModel;
			infrastructure.View.Show();			
		}

		private void Step3()
		{
			Step3.ViewFactory factory = new Step3.ViewFactory();

			Step3.ViewInfrastructure infrastructure = factory.Create();

			infrastructure.View.DataContext = infrastructure.ViewModel;
			infrastructure.View.Show();
		}

		private void Step4()
		{
			Step4.ViewFactory factory = new Step4.ViewFactory();

			Step4.ViewInfrastructure infrastructure = factory.Create();

			infrastructure.View.DataContext = infrastructure.ViewModel;
			infrastructure.View.Show();
		}

		private void Step5()
		{
			Step5.ViewFactory factory = new Step5.ViewFactory();

			Step5.ViewInfrastructure infrastructure = factory.Create();

			infrastructure.View.DataContext = infrastructure.ViewModel;
			infrastructure.View.Show();
		}

		private void Step6()
		{
			Step6.ViewFactory factory = new Step6.ViewFactory();

			Step6.ViewInfrastructure infrastructure = factory.Create();

			infrastructure.View.DataContext = infrastructure.ViewModel;
			infrastructure.View.Show();
		}

		private void Step7()
		{
			Step7.ViewFactory factory = new Step7.ViewFactory();

			Step7.ViewInfrastructure infrastructure = factory.Create();

			infrastructure.View.DataContext = infrastructure.ViewModel;
			infrastructure.View.Show();
		}

		private void Step8()
		{
			Step8.ViewFactory factory = new Step8.ViewFactory();

			Step8.ViewInfrastructure infrastructure = factory.Create();

			infrastructure.View.DataContext = infrastructure.ViewModel;
			infrastructure.View.Show();
		}
	}
}
