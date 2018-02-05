//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "wagner_fischer_distance.h"

TEST(wagner_fischer_distance, demo) 
{
   std::string str1 = "matej";
   std::string str2 = "mtey";
   
   int result = mzlib::wagner_fischer_distance(str1, str2);
   
   // 1 omitted a, 1 substituted y : edit distance = 2
   ASSERT_EQ(2, result);
}

TEST(wagner_fischer_distance, works_on_vector) 
{
   std::vector<int> v1 = {1,2,3,4,5,6,7,8,9,10};
   std::vector<int> v2 = {1,  3,4,6,6,7,8,9,10,11};
   //                       o       s          a
   // o - omitted, s - substituted, a - added : distance == 3
  
   int result = mzlib::wagner_fischer_distance(v1, v2);
   ASSERT_EQ(3, result);
}

TEST(wagner_fischer_distance, distance_equal) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   
   int result = mzlib::wagner_fischer_distance(str1, str2);
   
   // it's the same
   ASSERT_EQ(0, result);
}

TEST(wagner_fischer_distance, a_complicated_one) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 = "mate zavrsnick lykes startrek but and very much the original series because it is too naive.";
   //                     d        a   s        d        sss ssaa   -> 11 changes
   // d: deletion, a: addition, s: substitution
   int result = mzlib::wagner_fischer_distance(str1, str2);
   
   // a bunch of edits
   ASSERT_EQ(11, result);
}

TEST(wagner_fischer_distance, substition_first) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 = "natej zavrsnik likes star trek but not so much the original series because it is too naive.";
   
   int result = mzlib::wagner_fischer_distance(str1, str2);
   
   // 1 substitution
   ASSERT_EQ(1, result);
}

TEST(wagner_fischer_distance, substition_last) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 = "matej zavrsnik likes star trek but not so much the original series because it is too naive!";
   
   int result = mzlib::wagner_fischer_distance(str1, str2);
   
   // 1 substitution
   ASSERT_EQ(1, result);
}

TEST(wagner_fischer_distance, substition_middle) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 = "matej zavrsnik likes star trek but not so much theAoriginal series because it is too naive.";
   
   int result = mzlib::wagner_fischer_distance(str1, str2);
   
   // 1 substitution
   ASSERT_EQ(1, result);
}

TEST(wagner_fischer_distance, deletion_first) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 =  "atej zavrsnik likes star trek but not so much the original series because it is too naive.";
   
   int result = mzlib::wagner_fischer_distance(str1, str2);
   
   // 1 deletion
   ASSERT_EQ(1, result);
}

TEST(wagner_fischer_distance, deletion_last) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 = "matej zavrsnik likes star trek but not so much the original series because it is too naive";
   
   int result = mzlib::wagner_fischer_distance(str1, str2);
   
   // 1 deletion
   ASSERT_EQ(1, result);
}

TEST(wagner_fischer_distance, deletion_middle) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 = "matej zavrsnik likes star trek but not so much the original eries because it is too naive.";
   
   int result = mzlib::wagner_fischer_distance(str1, str2);
   
   // 1 deletion
   ASSERT_EQ(1, result);
}

TEST(wagner_fischer_distance, insertion_first) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 = "Qmatej zavrsnik likes star trek but not so much the original series because it is too naive.";
   
   int result = mzlib::wagner_fischer_distance(str1, str2);
   
   // 1 insertion
   ASSERT_EQ(1, result);
}

TEST(wagner_fischer_distance, insertion_last) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.Q";
   
   int result = mzlib::wagner_fischer_distance(str1, str2);
   
   // 1 insertion
   ASSERT_EQ(1, result);
}

TEST(wagner_fischer_distance, insertion_middle) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 = "matej zavrsnik likes star trek but not so much the original Qseries because it is too naive.";
   
   int result = mzlib::wagner_fischer_distance(str1, str2);
   
   // 1 insertion
   ASSERT_EQ(1, result);
}
