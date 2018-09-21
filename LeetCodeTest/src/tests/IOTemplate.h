
#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <cassert>
#include "Common.h"

//# define USE_BOOST

# ifdef USE_BOOST
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
# endif

namespace IOTemplate
{
  vector<int> readOneLine(const string& line)
  {
    using namespace std;
    // define delimiter
    static const char* delimiter = "/\\ .,;:\n\t\0";
    vector<string> fields;

# ifdef USE_BOOST
    boost::split(fields, line, boost::is_any_of(delimiter));
# else
    size_t prev_pos = 0, pos;
    while ((pos = line.find_first_of(delimiter, prev_pos)) != string::npos)
    {
      if (pos > prev_pos)
        fields.emplace_back(line.substr(prev_pos, pos - prev_pos));
      prev_pos = pos + 1;
    }
    if (prev_pos< line.length())
      fields.emplace_back(line.substr(prev_pos, string::npos));
# endif
    // process fields
    vector<int> data;
    for (const auto& field : fields)
    {
      if (field.empty())
        continue;
      int value = stoi(field);
      data.emplace_back(value);
    }
    return data;
  }

  vector<int> readData(const string& filename)
  {
    using namespace std;
    // read input file
    shared_ptr<ifstream> p_file(new ifstream(filename), [](ifstream* ptr) { ptr->close(); });
    assert(p_file->is_open());

    vector<int> data;
    while (!p_file->eof())
    {
      string line;
      getline(*p_file, line);
      auto dataOfLine = readOneLine(line);
      data.insert(data.begin(), dataOfLine.begin(), dataOfLine.end());
    }
    return data;
  }
  
  void Test()
  {
    auto data = readData("data\\int_array_data.txt");
    for (auto i : data)
      cout << " " << i;
    cout << endl;
  }
}
