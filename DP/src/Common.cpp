#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "Common.h"

using namespace std;

namespace CommonUtils
{
  template<typename T, typename T_F>
  static vector<T> getData(string filename, T_F converter)
  {
    // define delimiter
    static const char* delimiter = " ,;\n\t\0";
    // read input file
    shared_ptr<ifstream> p_file(new ifstream(filename), [](ifstream* ptr) { ptr->close(); });
    assert(p_file->is_open());

    vector<T> data;
    while (!p_file->eof())
    {
      string str;
      getline(*p_file, str);
      boost::trim_if(str, boost::is_any_of(delimiter));
      vector<string> fields;
      boost::split(fields, str, boost::is_any_of(delimiter));
      for (const auto& field : fields)
      {
        if (field.empty()) continue;
        try
        {
          data.emplace_back(converter(field));
        }
        catch (std::exception& error)
        {
          cout << "Failed to parse data [" << field << "]: " << error.what() << endl;
        }        
      }
    }
    return move(data);
  }

  vector<int> getIntVector()
  {
    auto converter = [](string field)
    {
      return boost::lexical_cast<int>(field);
    };
    return std::move(getData<int>("data\\int_array_data.txt", converter));
  }

  vector<double> getDoubleVector()
  {
    auto converter = [](string field)
    {
      return boost::lexical_cast<double>(field);
    };
    return std::move(getData<double>("data\\double_array_data.txt", converter));
  }

  vector<string> getStringVector()
  {
    auto converter = [](string field)
    {
      return move(field);
    };
    return std::move(getData<string>("data\\string_array_data.txt", converter));
  }
}