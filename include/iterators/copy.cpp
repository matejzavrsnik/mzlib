//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "copy.h"

TEST(copy_iterators, equal_size) 
{
   std::string a = "Do You know Gods Of Death Love Apples?";
   std::string b = "______________________________________";
   mzlib::copy(a.begin(), a.end(), b.begin(), b.end());
   ASSERT_EQ(a, b);
}

TEST(copy_iterators, source_larger) 
{
   std::string a = "Do You know Gods Of Death Love Apples?";
   std::string b = "________________";
   mzlib::copy(a.begin(), a.end(), b.begin(), b.end());
   ASSERT_EQ("Do You know Gods", b);
}

TEST(copy_iterators, destination_larger) 
{
   std::string a = "Gods Of Death Love Apples?";
   std::string b = "______________________________________";
   mzlib::copy(a.begin(), a.end(), b.begin(), b.end());
   ASSERT_EQ("Gods Of Death Love Apples?____________", b);
}

TEST(copy_iterators, copy_middle) 
{
   std::string a = "Do You know Gods Of Death Love Apples?";
   std::string b = "______________________________________";
   mzlib::copy(a.begin()+12, a.begin()+25, b.begin(), b.end());
   ASSERT_EQ("Gods Of Death_________________________", b);
}