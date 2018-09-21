#ifndef SOCIAL_MOVIES_H
#define SOCIAL_MOVIES_H

#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <cassert>
#include <algorithm>
#include "Common.h"

#if 0

using namespace std;

namespace SocialNetwork
{
  // Enumeration of possible return values
  enum ResultCode {
    // The function was successful 
    SUCCESS = 0,
    // An error condition was encountered when executing the function
    FAILURE,
  };

  // Maintains a network of movies and customers
  // All methods should return ResultCode::SUCCESS when the operation completes successfully or
  // ResultCode::FAILURE when an error condition occurs.
  class SocialMovies
  {
  private:
    unordered_map<int, string> m_customers;
    unordered_map<int, string> m_movies;
    // maintain a hash table between movie id and its fan customers
    unordered_map<int, unordered_set<int>> m_likedMovies;
    // maintain a friend hash table
    unordered_map<int, set<int>> m_friends;
  public:
    // Defines a movie ID to title mapping in the system
    ResultCode addMovie(int movieId, const string& title)
    {
      if (m_movies.find(movieId) != m_movies.end())
        return ResultCode::FAILURE;
      m_movies.emplace(movieId, title);
      return ResultCode::SUCCESS;
    }

    // Gets the title of the given movie
    ResultCode lookupMovie(int movieId, string& movieTitle)
    {
      auto itor = m_movies.find(movieId);
      if (itor == m_movies.end())
        return ResultCode::FAILURE;
      movieTitle = itor->second;
      return ResultCode::SUCCESS;
    }

    // Defines a customer ID to name mapping in the system
    ResultCode addCustomer(int customerId, const string& name)
    {
      if (m_customers.find(customerId) != m_customers.end())
        return ResultCode::FAILURE;
      m_customers.emplace(customerId, name);
      return ResultCode::SUCCESS;
    }

    // Gets the name of the given customer
    ResultCode lookupCustomer(int customerId, string& customerName)
    {
      auto itor = m_customers.find(customerId);
      if (itor == m_customers.end())
        return ResultCode::FAILURE;
      customerName = itor->second;
      return ResultCode::SUCCESS;
    }

    // Record that a movie was "liked" by the given customer
    ResultCode addLikedMovie(int customerId, int movieId)
    {
      string str;
      if (lookupMovie(movieId, str) == ResultCode::FAILURE || lookupCustomer(customerId, str) == ResultCode::FAILURE)
        return ResultCode::FAILURE;

      // add it to m_likedMovies
      auto itor = m_likedMovies.find(movieId);
      if (itor == m_likedMovies.end())
        return ResultCode::FAILURE;

      auto& customers = itor->second;
      if (customers.find(customerId) != customers.end())
        return ResultCode::FAILURE;
      customers.emplace(customerId);
      return ResultCode::SUCCESS;
    }

    // Associate two customers as being friends
    ResultCode addFriend(int customerId1, int customerId2)
    {
      // can't be your self's friend
      if (customerId1 == customerId2)
        return ResultCode::FAILURE;
      //verify the customer id
      string name;
      if (lookupCustomer(customerId1, name) == ResultCode::FAILURE || lookupCustomer(customerId2, name) == ResultCode::FAILURE)
        return ResultCode::FAILURE;      
      // if friendship exists, return failure
      auto& friendsOfCustomer1 = m_friends[customerId1];
      if (friendsOfCustomer1.find(customerId2) == friendsOfCustomer1.end())
        return ResultCode::FAILURE;
      // add friends
      friendsOfCustomer1.emplace(customerId2);      
      // add customer1 to customer2
      return addFriend(customerId2, customerId1);
    }

    // The returned customer must be reachable by at most <maxDistance> friend links.
    void getFriends(int customerId, int maxDistance, unordered_set<int>& customerIds)
    {
      if (maxDistance == 1)
      {
        auto& friends = m_friends[customerId];

      }
    }

    // Gets the ID of the customer who has the most "likes" in common with the given
    // customer.  The returned customer must be reachable by at most <maxDistance> friend links.
    ResultCode getSimilarCustomerInNetwork(int customerId, int maxDistance, int& similarCustomerId)
    {

    }

    // Gets the IDs of the <maximumResults> movies with the highest total number of "likes".  All movies
    // returned must have a "like" count >= the like count of every non-returned movie.
    ResultCode getMostLikedMovies(int maximumResults, vector<int>& mostLikedMovieIds)
    {
      int maxLiked = 0;
      for (auto& movieCustomers : m_likedMovies)
      {
        if ((int)movieCustomers.second.size() > maxLiked)
          maxLiked = movieCustomers.second.size();
      }
      if (maxLiked == 0) return ResultCode::FAILURE;

      mostLikedMovieIds.clear();
      for (auto& movieCustomers : m_likedMovies)
      {
        if (movieCustomers.second.size() == maxLiked)
          mostLikedMovieIds.emplace_back(movieCustomers.first);
        if (mostLikedMovieIds.size() == maximumResults)
          break;
      }
      return ResultCode::SUCCESS;
    }
  };

  static void Test()
  {
    using namespace std;
    SocialMovies sm;
    sm.addCustomer(1, "a");
    sm.addCustomer(2, "b");
    sm.addCustomer(3, "c");
    sm.addCustomer(4, "d");
    string str;
    cout << (sm.lookupCustomer(1, str) == ResultCode::SUCCESS) << endl;
    cout << (sm.lookupCustomer(5, str) == ResultCode::FAILURE) << endl;

    sm.addMovie(11, "m1");
    sm.addMovie(12, "m2");
    sm.addMovie(13, "m3");
    sm.addMovie(14, "m4");

    sm.addLikedMovie(1, 11);
    sm.addLikedMovie(1, 12);
    sm.addLikedMovie(2, 11);
    sm.addLikedMovie(3, 12);
    sm.addLikedMovie(3, 13);
    sm.addLikedMovie(4, 14);

    sm.addFriend(1, 3);
    sm.addFriend(2, 3);
    sm.addFriend(4, 3);


  }
}

#endif

#endif//SOCIAL_MOVIES_H
