using MvvmExample.Model;
using MvvmExample.View;
using MvvmExample.ViewModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MvvmExample.View
{
    public class ViewInfrastructureFactory
    {
        public ViewInfrastructure Create()
        {
            EraseDelegateCommand eraseDelegateCommand = new EraseDelegateCommand();
            SaveDelegateCommand saveDelegateCommand = new SaveDelegateCommand();
            PersonModel model = new PersonModel();
            model.IsMale = true;
            model.Name = "Yan";
            model.Address = "1611";
            model.BirthDate = new DateTime(1993, 2, 14);
            PersonViewModel viewModel = new PersonViewModel(model, saveDelegateCommand.Command, eraseDelegateCommand.Command);
            MainView view = new MainView();

            eraseDelegateCommand.ViewModel = viewModel;
            saveDelegateCommand.ViewModel = viewModel;

            return new ViewInfrastructure(view, viewModel, model);
        }
    }
}