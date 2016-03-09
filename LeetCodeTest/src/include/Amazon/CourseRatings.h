#pragma once
/*
A social network is defined as all friends within social distance 2 (direct friends' direct friends.)
The recommendation logic is based on the following logic:
1. A user should only be recommended as course that their social network have attended, but they have not yet.
2. The recommendations priority is driven by how many people have attended the same course - the more people attend the rating is higher.

Two API will be provided
  vector<string> getDirectFriendsForUser(string user)
  vector<string> getAttendedCoursesForUser(string user)

Please write a function that provides a ranked (high to low) list of courses(course IDs) for a provided user.
  vector<string> getRankedCourses(string user)
*/

#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <cassert>
#include <algorithm>
#include "Common.h"

namespace CourseRatings
{
  // key is user ID and value is all the course IDs.
  static unordered_map<string, set<string>> m_userCourseMap;
  // key is user ID and value is all the direct friend IDs.
  static unordered_map<string, set<string>> m_friendMap;
  
  static void addUser(const string& user)
  {
    if (m_friendMap.find(user) == m_friendMap.end())
    {
      m_friendMap.emplace(user, set<string>());
    }
  }

  static void addAFriendForUser(const string& user, const string& friendId)
  {
    addUser(user);
    addUser(friendId);
    auto& friendsOfUser = m_friendMap[user];
    if (friendsOfUser.find(friendId) == friendsOfUser.end())
    {
      friendsOfUser.emplace(friendId);
    }
  }

  static void addFriendship(const string& user1, const string& user2)
  {
    addAFriendForUser(user1, user2);
    addAFriendForUser(user2, user1);
  }

  static void addCourseForUser(const string& user, const string& courseId)
  {
    if (m_userCourseMap.find(user) == m_userCourseMap.end())
    {
      m_userCourseMap.emplace(user, set<string>());
    }
    auto& courses = m_userCourseMap[user];
    if (courses.find(courseId) == courses.end())
    {
      courses.emplace(courseId);
    }
  }

  static vector<string> getAllUsers()
  {
    vector<string> result;
    for (const auto& friendship : m_friendMap)
    {
      result.emplace_back(friendship.first);
    }
    return result;
  }

  static vector<string> getDirectFriendsForUser(const string& user)
  {
    return vector<string>(m_friendMap[user].begin(), m_friendMap[user].end());
  }
  static vector<string> getAttendedCoursesForUser(const string& user)
  {
    return vector<string>(m_userCourseMap[user].begin(), m_userCourseMap[user].end());
  }

  static vector<string> getRankedCourses(string user)
  {
    auto friends = getDirectFriendsForUser(user);
    // created a hash table for all social friends
    set<string> allFriends(friends.begin(), friends.end());
    for (const auto& f: friends)
    {
      const auto friendsIndirect = getDirectFriendsForUser(f);
      for (const auto& friendIndirect : friendsIndirect)
      {
        if (allFriends.find(friendIndirect) == allFriends.end())
          allFriends.emplace(friendIndirect);
      }
    }
    allFriends.erase(user);
    // go through all friends to get the recommended course ratings
    // a map sorted by courses, value is the ratings
    map<string, int> courseRatings;
    for (const auto& f : allFriends)
    {
      auto courses = getAttendedCoursesForUser(f);
      for (const auto& course : courses)
      {
        courseRatings[course] += 1;
      }
    }
    // remove already taken courses
    auto coursesAlreadyTaken = getAttendedCoursesForUser(user);
    for (const auto& course : coursesAlreadyTaken)
    {
      courseRatings.erase(course);
    }
    // a map sorted by ratings, value is all the courses with the same rating
    map<int, vector<string>> ratingCourses;
    for (auto it = courseRatings.begin(); it != courseRatings.end(); ++it)
    {
      auto& course = it->first;
      auto rating = it->second;
      ratingCourses[rating].emplace_back(course);
    }
    // now ratingCourses is sorted by ratings
    vector<string> result;
    for (const auto& ratingCoursePair : ratingCourses)
    {
      // low ratings come first
      result.insert(result.begin(), ratingCoursePair.second.begin(), ratingCoursePair.second.end());
    }
    return result;
  }

  static void Test()
  {
    auto rawData = CommonUtils::getStringVector();
    //////////////////////////////////////////////////////////////
    /*
    A B C D
    B C D
    C F
    D E F
    */
    auto friendship = vector<vector<string>>(rawData.begin(), rawData.begin() + 4);
    for (auto& friends : friendship)
    {
      // go through each friend. update friendsOfUser
      auto& user = friends[0];
      for (auto iter = friends.begin() + 1; iter != friends.end(); iter++)
      {
        addFriendship(user, *iter);
      }
    }
    //////////////////////////////////////////////////////////////
    /*
    A 1 5
    B 1 4
    C 2
    D 5
    E 2 3
    F 3 4
    G 1 2 3 4 5
    */
    auto courseAttendance = vector<vector<string>>(rawData.begin() + 4, rawData.end());
    for (auto& courses : courseAttendance)
    {
      auto& user = courses[0];
      for (auto iter = courses.begin() + 1; iter != courses.end(); iter++)
      {
        addCourseForUser(user, *iter);
      }
    }
    //////////////////////////////////////////////////////////////
    // print all saved information
    auto allUsers = getAllUsers();
    for (const auto& user : allUsers)
    {
      cout << "Friends of user " << user << ":";
      const auto friends = getDirectFriendsForUser(user);
      for (const auto& friendOfUser : friends)
      {
        cout << " " << friendOfUser;
      }
      cout << endl << "Courses of user " << user << ":";
      const auto courses = getAttendedCoursesForUser(user);
      for (const auto& course : courses)
      {
        cout << " " << course;
      }
      cout << endl;
    }
    cout << endl;
    for (const auto& user : allUsers)
    {
      cout << "Ranked courses of user " << user << ":";
      const auto courses = getRankedCourses(user);
      for (const auto& course : courses)
      {
        cout << " " << course;
      }
      cout << endl;
    }
    //////////////////////////////////////////////////////////////
    cout << endl;
  }
}