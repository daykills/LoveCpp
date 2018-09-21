#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <memory>
#include <vector>
#include <stdexcept>

//#define USE_BOOST

#ifdef USE_BOOST
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#endif

namespace FileReader
{
  // anonymous namespace for all utility functions 
  namespace
  {
#ifndef USE_BOOST
    template<typename T>
    T standardParse(const std::string& field)
    {
      throw runtime_error("Generic functio is not implemented.");
    }

    template<>
    std::string standardParse(const std::string& field)
    {
      return field;
    }

    template<>
    int standardParse(const std::string& field)
    {
      return std::stoi(field);
    }

    template<>
    double standardParse(const std::string& field)
    {
      return std::stof(field);
    }
#endif

    template <typename T>
    T convert(const std::string& field)
    {
#ifdef USE_BOOST
      return boost::lexical_cast<T>(field);
#else
      return standardParse<T>(field);
#endif
    }

    // T is expected to be std::vector<T_D>
    template <typename T>
    static std::vector<T> readOneLine(const std::string& line)
    {
      // define delimiter
      static const char* delimiter = "/\\ ,;:\n\t\0";
      std::vector<std::string> fields;

#ifdef USE_BOOST
      boost::split(fields, line, boost::is_any_of(delimiter));
#else
      size_t prev_pos = 0, pos;
      while ((pos = line.find_first_of(delimiter, prev_pos)) != std::string::npos)
      {
        if (pos > prev_pos)
          fields.emplace_back(line.substr(prev_pos, pos - prev_pos));
        prev_pos = pos + 1;
      }
      if (prev_pos < line.length())
        fields.emplace_back(line.substr(prev_pos, std::string::npos));
#endif
      // process fields
      std::vector<T> data;
      for (const auto& field : fields)
      {
        if (field.empty())
          continue;
        data.emplace_back(convert<T>(field));
      }
      return data;
    }
  }

  // each line is converted to a std::vector of type T
  template <typename T>
  std::vector<std::vector<T>> readData(const std::string& filename)
  {
    // read input file
    std::shared_ptr<std::ifstream> p_file(new std::ifstream(filename), [](std::ifstream* ptr) { ptr->close(); });
    assert(p_file->is_open());

    std::vector<std::vector<T>> data;
    while (!p_file->eof())
    {
      std::string line;
      getline(*p_file, line);
      data.emplace_back(readOneLine<T>(line));
    }
    return data;
  }

  // read lines without extra parsing
  std::vector<std::string> readRawLines(const std::string& filename)
  {
    // read input file
    std::shared_ptr<std::ifstream> p_file(new std::ifstream(filename), [](std::ifstream* ptr) { ptr->close(); });
    assert(p_file->is_open());

    std::vector<std::string> data;
    while (!p_file->eof())
    {
      std::string line;
      getline(*p_file, line);
      data.emplace_back(line);
    }
    return data;
  }
}
