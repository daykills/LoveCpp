/*
Merge sort
*/

#include <algorithm>
#include <cassert>
#include "Common.h"

namespace PriorityQueue
{
  class PriorityQueue
  {
  public:
    void Insert(int value)
    {
      // put the new value at the end of the array
      m_data.emplace_back(value);
      // bubble up
      auto iValue = size() - 1;
      while (iValue != 0)
      {
        auto iParent = parent(iValue);
        // check the "order condition" of the heap
        if (m_data[iParent] >= m_data[iValue]) break;
        swap(iValue, iParent);
        iValue = iParent;
      }
    }
    // remove the top
    void Pop()
    {
      // replace the top with the last value
      m_data.front() = m_data.back();
      // remove the last element
      m_data.pop_back();
      // bubble down
      auto iValue = 0;
      while (iValue < size())
      {
        auto iLeft = left(iValue);
        if (iLeft >= size()) break;
        
        // index of the larger child
        auto iLarger = iLeft;
       
        auto iRight = right(iValue);
        if (iRight >= size())
        {
          iLarger = iLeft;
        }
        else
        {
          iLarger = m_data[iLeft] > m_data[iRight] ? iLeft : iRight;
        }
        
        // shape is already good
        if (m_data[iValue] >= m_data[iLarger])
          break;
        // swap value with the larger node
        swap(iValue, iLarger);
        iValue = iLarger;
      }
    }
    int Top()
    {
      assert(size() != 0);
      return m_data.front();
    }
    bool Empty()
    {
      return m_data.empty();
    }
    void Print()
    {
      int n = size();
      if (n == 0) return;
      int numNodesOnLevel = 1;
      int count = 0;
      while (true)
      {
        cout << endl;
        for (int i = 0; i < numNodesOnLevel; i++)
        {
          if (count == n) return;
          cout << m_data[count] << " ";
          count++;          
        }        
        numNodesOnLevel *= 2;
      }
    }
  private:
    void swap(int index1, int index2)
    {
      auto temp = m_data[index1];
      m_data[index1] = m_data[index2];
      m_data[index2] = temp;
    }
    inline int size()
    {
      return m_data.size();
    }    
    // return the index of left child
    inline int left(int index)
    {
      return (index + 1) * 2 - 1;
    }
    // return the index of right child
    inline int right(int index)
    {
      return (index + 1) * 2;
    }
    // return the index of parent
    inline int parent(int index)
    {
      return (index - 1) / 2;
    }
    // heap data is kept in an array
    vector<int> m_data;
  };
  
  static bool Test()
  {
    vector<int> nums{ 3, 1, 7, 5, 10, 12, 13, 3 };
    for (auto i : nums)
      cout << " " << i;
    cout << endl;

    PriorityQueue queue;

    for (auto num : nums)
    {
      cout << endl << "Insert " << num;
      queue.Insert(num);
      queue.Print();
    }

    for (auto num : nums)
    {
      cout << endl << "Remove " << queue.Top();
      queue.Pop();
      queue.Print();
    }

    for (auto i : nums)
      cout << " " << i;
    cout << endl;

    return false;
  }
}