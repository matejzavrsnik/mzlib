//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "nested_iteration.h"

#include "gtest/gtest.h"

TEST(nested_iteration, correctly_initialises_first_state)
{
   std::vector<int> v{1,2,3,4,5};
   
   auto niter = mzlib::nested_iteration(v.begin(), v.end(), 3);
   auto iters = niter.get();
      
   ASSERT_FALSE(niter.end());
   ASSERT_EQ(3, iters.size());
   ASSERT_EQ(1, *iters[0]);
   ASSERT_EQ(2, *iters[1]);
   ASSERT_EQ(3, *iters[2]);
}

TEST(nested_iteration, correctly_initialises_not_enough_elements)
{
   std::vector<int> v{1,2,3};
   
   auto niter = mzlib::nested_iteration(v.begin(), v.end(), 5);
   auto iters = niter.get();
      
   ASSERT_TRUE(niter.end());
}

TEST(nested_iteration, first_increment)
{
   std::vector<int> v{1,2,3,4,5};
   
   auto niter = mzlib::nested_iteration(v.begin(), v.end(), 3);
   niter.next(); // 1 2 4
   auto iters = niter.get();
      
   ASSERT_FALSE(niter.end());
   ASSERT_EQ(3, iters.size());
   ASSERT_EQ(1, *iters[0]);
   ASSERT_EQ(2, *iters[1]);
   ASSERT_EQ(4, *iters[2]);
}

TEST(nested_iteration, last_iterator_reaches_last_place)
{
   std::vector<int> v{1,2,3,4,5};
   
   auto niter = mzlib::nested_iteration(v.begin(), v.end(), 3);
   niter.next(); // 1 2 4
   niter.next(); // 1 2 5
   auto iters = niter.get();
      
   ASSERT_FALSE(niter.end());
   ASSERT_EQ(3, iters.size());
   ASSERT_EQ(1, *iters[0]);
   ASSERT_EQ(2, *iters[1]);
   ASSERT_EQ(5, *iters[2]);
}

TEST(nested_iteration, last_iterator_wraps_around)
{
   std::vector<int> v{1,2,3,4,5};
   
   auto niter = mzlib::nested_iteration(v.begin(), v.end(), 3);
   niter.next(); // 1 2 4
   niter.next(); // 1 2 5
   niter.next(); // 1 2 {6} -> 1 3 4
   auto iters = niter.get();
      
   ASSERT_FALSE(niter.end());
   ASSERT_EQ(3, iters.size());
   ASSERT_EQ(1, *iters[0]);
   ASSERT_EQ(3, *iters[1]);
   ASSERT_EQ(4, *iters[2]);
}

TEST(nested_iteration, last_iterator_reaches_last_space_after_wraparound)
{
   std::vector<int> v{1,2,3,4,5};
   
   auto niter = mzlib::nested_iteration(v.begin(), v.end(), 3);
   niter.next(); // 1 2 4
   niter.next(); // 1 2 5
   niter.next(); // 1 2 {6} -> 1 3 4
   niter.next(); // 1 3 5
   auto iters = niter.get();
      
   ASSERT_FALSE(niter.end());
   ASSERT_EQ(3, iters.size());
   ASSERT_EQ(1, *iters[0]);
   ASSERT_EQ(3, *iters[1]);
   ASSERT_EQ(5, *iters[2]);
}

TEST(nested_iteration, second_last_iterator_reaches_last_space)
{
   std::vector<int> v{1,2,3,4,5};
   
   auto niter = mzlib::nested_iteration(v.begin(), v.end(), 3);
   niter.next(); // 1 2 4
   niter.next(); // 1 2 5
   niter.next(); // 1 2 {6} -> 1 3 4
   niter.next(); // 1 3 5
   niter.next(); // 1 3 {6} -> 1 4 5
   auto iters = niter.get();
      
   ASSERT_FALSE(niter.end());
   ASSERT_EQ(3, iters.size());
   ASSERT_EQ(1, *iters[0]);
   ASSERT_EQ(4, *iters[1]);
   ASSERT_EQ(5, *iters[2]);
}

TEST(nested_iteration, second_last_iterator_wraps_around)
{
   std::vector<int> v{1,2,3,4,5};
   
   auto niter = mzlib::nested_iteration(v.begin(), v.end(), 3);
   niter.next(); // 1 2 4
   niter.next(); // 1 2 5
   niter.next(); // 1 2 {6} -> 1 3 4
   niter.next(); // 1 3 5
   niter.next(); // 1 3 {6} -> 1 4 5
   niter.next(); // 1 4 5 -> 1 4 {6} -> 1 {5} - -> 2 3 4
   auto iters = niter.get();
      
   ASSERT_FALSE(niter.end());
   ASSERT_EQ(3, iters.size());
   ASSERT_EQ(2, *iters[0]);
   ASSERT_EQ(3, *iters[1]);
   ASSERT_EQ(4, *iters[2]);
}

TEST(nested_iteration, correctly_arrives_to_the_last_state)
{
   std::vector<int> v{1,2,3,4,5};
   
   auto niter = mzlib::nested_iteration(v.begin(), v.end(), 3);
   niter.next(); // 1 2 4
   niter.next(); // 1 2 5
   niter.next(); // 1 2 {6} -> 1 3 4
   niter.next(); // 1 3 5
   niter.next(); // 1 3 {6} -> 1 4 5
   niter.next(); // 1 4 5 -> 1 4 {6} -> 1 {5} -> 2 3 4
   niter.next(); // 2 3 5
   niter.next(); // 2 4 5
   niter.next(); // 3 4 5
   auto iters = niter.get();
      
   ASSERT_FALSE(niter.end());
   ASSERT_EQ(3, iters.size());
   ASSERT_EQ(3, *iters[0]);
   ASSERT_EQ(4, *iters[1]);
   ASSERT_EQ(5, *iters[2]);
}

TEST(nested_iteration, correctly_determines_the_end)
{
   std::vector<int> v{1,2,3,4,5};
   
   auto niter = mzlib::nested_iteration(v.begin(), v.end(), 3);
   niter.next(); // 1 2 4
   niter.next(); // 1 2 5
   niter.next(); // 1 2 {6} -> 1 3 4
   niter.next(); // 1 3 5
   niter.next(); // 1 3 {6} -> 1 4 5
   niter.next(); // 1 4 5 -> 1 4 {6} -> 1 {5} -> 2 3 4
   niter.next(); // 2 3 5
   niter.next(); // 2 4 5
   niter.next(); // 3 4 5
   niter.next(); // end
   
   ASSERT_TRUE(niter.end());
}