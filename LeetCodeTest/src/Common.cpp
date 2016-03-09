#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <memory>
#include <stdexcept>
#include <FileReader.h>
#include "Common.h"

using namespace std;
using namespace FileReader;

namespace CommonUtils
{
  vector<vector<int>> getIntVector()
  {
    return move(readData<int>("data\\int_array_data.txt"));
  }

  vector<vector<double>> getDoubleVector()
  {
    return move(readData<double>("data\\double_array_data.txt"));
  }

  vector<vector<string>> getStringVector()
  {
    return move(readData<string>("data\\string_array_data.txt"));
  }

  vector<string> getLines()
  {
    return move(readRawLines("data\\string_array_data.txt"));
  }
}