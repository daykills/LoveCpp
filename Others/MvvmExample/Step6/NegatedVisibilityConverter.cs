using System;
using System.Globalization;
using System.Windows;
using System.Windows.Data;

namespace MvvmExampleStep8.Step6
{
	public class NegatedVisibilityConverter : IValueConverter
	{
		public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
		{
			if (value is bool)
			{
				return (bool) value ? Visibility.Collapsed : Visibility.Visible;
			}
			else
			{
				return Binding.DoNothing;
			}
		}

		public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
		{
			throw new NotImplementedException();
		}
	}
}
