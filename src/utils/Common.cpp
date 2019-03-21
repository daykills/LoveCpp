#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <memory>
#include <stdexcept>

#include "Common.h"
#include "FileReader.h"

using namespace std;
using namespace FileReader;

namespace CommonUtils
{
  vector<vector<int>> getIntVector()
  {
    return readData<int>("Resources/int_array_data.txt");
  }

  vector<vector<double>> getDoubleVector()
  {
    return readData<double>("Resources/double_array_data.txt");
  }

  vector<vector<string>> getStringVector()
  {
    return readData<string>("Resources/string_array_data.txt");
  }

  vector<string> getLines()
  {
    return readRawLines("Resources/string_array_data.txt");
  }
}
