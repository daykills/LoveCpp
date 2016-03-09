using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MvvmExample.Model
{
    public class PersonModel
    {
        public string Name { get; set; }

        public string Address { get; set; }

        public bool IsMale { get; set; }

        public DateTime BirthDate { get; set; }
    }
}
