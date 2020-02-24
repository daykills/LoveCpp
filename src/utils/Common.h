#pragma once

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <iostream>
#include <functional>
#include <future>
#include <list>
#include <map>
#include <mutex>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <thread>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "TreePrinter.h"
#include "binarytree.hpp"
#include "linkedlist.hpp"
#include "Graph.h"

using namespace std;

namespace CommonUtils
{
  extern vector<vector<int>> getIntVector();
  extern void Test();
  extern vector<vector<double>> getDoubleVector();
  extern vector<vector<string>> getStringVector();
  extern vector<string> getLines();
}
