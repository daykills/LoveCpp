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
    public class ViewInfrastructure
    {
        public MainView View { get; private set; }

        public PersonViewModel ViewModel { get; private set; }

        public PersonModel Model { get; private set; }

        public ViewInfrastructure(MainView view, PersonViewModel viewModel, PersonModel model)
        {
            this.View = view;
            this.ViewModel = viewModel;
            this.Model = model;
        }
    }
}
