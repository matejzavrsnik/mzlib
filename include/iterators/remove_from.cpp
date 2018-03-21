//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "remove_from.h"

TEST(remove_from, strings_which_end_with)
{
   std::vector<std::string> list;
   list.push_back("I must not fear"); 
   list.push_back("Fear is the mind-killer");
   list.push_back("Fear is the little-death that brings total obliteration");
   list.push_back("I will face my fear");
   list.push_back("I will permit it to pass over me and through me");
   
   std::vector<std::string> endings = {"mind-killer", "obliteration", "me"};
   auto filtered = mzlib::remove_from(list.begin(), list.end())
      .which().end().with(endings.begin(), endings.end());
   
   auto not_found = filtered.end();
   ASSERT_EQ(2, filtered.size());
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "I must not fear"));   
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "I will face my fear"));
}

TEST(remove_from, strings_which_start_with)
{
   std::vector<std::string> list;
   list.push_back("I must not fear"); 
   list.push_back("Fear is the mind-killer");
   list.push_back("Fear is the little-death that brings total obliteration");
   list.push_back("I will face my fear");
   list.push_back("I will permit it to pass over me and through me");
   
   std::vector<std::string> endings = {"I must", "Fear"};
   auto filtered = mzlib::remove_from(list.begin(), list.end())
      .which().start().with(endings.begin(), endings.end());
   
   auto not_found = filtered.end();
   ASSERT_EQ(2, filtered.size());
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "I will face my fear"));
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "I will permit it to pass over me and through me"));
}

TEST(remove_from, strings_which_dont_start_with)
{
   std::vector<std::string> list;
   list.push_back("I must not fear"); 
   list.push_back("Fear is the mind-killer");
   list.push_back("Fear is the little-death that brings total obliteration");
   list.push_back("I will face my fear");
   list.push_back("I will permit it to pass over me and through me");
   
   std::vector<std::string> endings = {"I must", "Fear"};
   auto filtered = mzlib::remove_from(list.begin(), list.end())
      .which_do_not().start().with(endings.begin(), endings.end());
   
   auto not_found = filtered.end();
   ASSERT_EQ(3, filtered.size());
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "I must not fear"));
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "Fear is the mind-killer")); 
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "Fear is the little-death that brings total obliteration"));
}

TEST(remove_from, strings_which_dont_end_with)
{
   std::vector<std::string> list;
   list.push_back("I must not fear"); 
   list.push_back("Fear is the mind-killer");
   list.push_back("Fear is the little-death that brings total obliteration");
   list.push_back("I will face my fear");
   list.push_back("I will permit it to pass over me and through me");
   
   std::vector<std::string> endings = {"mind-killer", "obliteration"};
   auto filtered = mzlib::remove_from(list.begin(), list.end())
      .which_do_not().end().with(endings.begin(), endings.end());
   
   auto not_found = filtered.end();
   ASSERT_EQ(2, filtered.size());
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "Fear is the mind-killer"));
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "Fear is the little-death that brings total obliteration"));
}

TEST(remove_from, vectors_which_end_with)
{
   std::vector<std::vector<int>> list;
   list.push_back({1,2,3,4,5}); 
   list.push_back({6,7,8,9,10});
   list.push_back({3,2,1,4,4});
   list.push_back({1,1,1,1,1,4,5});
   list.push_back({1,2,3,4,5,6,7});
   
   std::vector<std::string> endings = {{4,5}, {5,6,7}};
   auto filtered = mzlib::remove_from(list.begin(), list.end())
      .which().end().with(endings.begin(), endings.end());
   
   auto not_found = filtered.end();
   ASSERT_EQ(2, filtered.size());
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), 
      std::vector<int>({6,7,8,9,10})));
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), 
      std::vector<int>({3,2,1,4,4})));
}