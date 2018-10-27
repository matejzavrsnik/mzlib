//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "random_with_parity.h"

#include "gtest/gtest.h"

#include <limits>

namespace
{
   template<typename RandomGenerator>
   std::vector<int> generate_events(
      RandomGenerator random_generator,
      int repetitions, int buckets)
   {
      std::vector<int> event_occurences(buckets, 0);
      for(int i=0; i<repetitions; ++i) 
      {
         int bucket = random_generator();
         event_occurences[bucket]++;
      }
      return event_occurences;
   }
   
   template<typename RandomGenerator>
   std::vector<int> generate_events_between(
      RandomGenerator random_generator,
      int repetitions, int buckets,
      int from, int to)
   {
      std::vector<int> event_occurences(buckets, 0);
      for(int i=0; i<repetitions; ++i) 
      {
         int bucket = random_generator(from, to);
         event_occurences[bucket]++;
      }
      return event_occurences;
   }
   
   template<typename ParityDeterminer>
   void assert_distribution(
      ParityDeterminer parity_determiner,
      const std::vector<int>& event_occurences,
      int repetitions, int buckets,
      int from, int to)
   {
      const int evenodd_buckets = buckets / 2;
      const int expected_events_in_bucket = repetitions / evenodd_buckets;
      const double acceptable_error = repetitions * 0.002;

      for(int i=0; i<event_occurences.size(); ++i)
         if (i >= from && i <= to && parity_determiner(i))
         {
            ASSERT_NEAR(event_occurences[i], expected_events_in_bucket, acceptable_error)
               << "event i=" << i << " frequency was not as expected.";
         }
         else
         {
            ASSERT_EQ(0, event_occurences[i])
               << "event i=" << i << " was not expected to occur.";
         }
   }
}

TEST(get_random_even, distribution_test) 
{
   const int buckets = std::numeric_limits<unsigned char>::max();
   const int repetitions = buckets * 1000;
   
   std::vector<int> event_occurences = generate_events(
      mzlib::get_random_even<unsigned char>,
      repetitions, buckets);

   assert_distribution(
      mzlib::is_even<unsigned char>,
      event_occurences,
      repetitions, buckets, 
      0, buckets);
}

TEST(get_random_odd, distribution_test) 
{
   const int buckets = std::numeric_limits<unsigned char>::max();
   const int repetitions = buckets * 1000;
   
   std::vector<int> event_occurences = generate_events(
      mzlib::get_random_odd<unsigned char>,
      repetitions, buckets);

   assert_distribution(
      mzlib::is_odd<unsigned char>,
      event_occurences,
      repetitions, buckets, 
      0, buckets);
}

TEST(get_random_even_between, distribution_test_from_even_to_even) 
{
   const int repetitions = 100000;
   const int buckets = 100;
   const int from = 0;
   const int to = buckets;
   
   std::vector<int> event_occurences = generate_events_between(
      mzlib::get_random_even_between<int>,
      repetitions, buckets, 
      from, to);

   assert_distribution(
      mzlib::is_even<int>,
      event_occurences,
      repetitions, buckets, 
      from, to);
}

TEST(get_random_even_between, distribution_test_from_odd_to_even) 
{
   const int repetitions = 100000;
   const int buckets = 100;
   const int from = 1;
   const int to = buckets;
   
   std::vector<int> event_occurences = generate_events_between(
      mzlib::get_random_even_between<int>,
      repetitions, buckets, 
      from, to);

   assert_distribution(
      mzlib::is_even<int>,
      event_occurences,
      repetitions, buckets, 
      from, to);
}

TEST(get_random_even_between, distribution_test_from_even_to_odd) 
{
   const int repetitions = 100000;
   const int buckets = 100;
   const int from = 0;
   const int to = 97;
   
   std::vector<int> event_occurences = generate_events_between(
      mzlib::get_random_even_between<int>,
      repetitions, buckets, 
      from, to);
   
   assert_distribution(
      mzlib::is_even<int>,
      event_occurences,
      repetitions, buckets, 
      from, to);
}

TEST(get_random_even_between, distribution_test_from_odd_to_odd) 
{
   const int repetitions = 100000;
   const int buckets = 100;
   const int from = 1;
   const int to = 97;
   
   std::vector<int> event_occurences = generate_events_between(
      mzlib::get_random_even_between<int>,
      repetitions, buckets, 
      from, to);
   
   assert_distribution(
      mzlib::is_even<int>,
      event_occurences,
      repetitions, buckets, 
      from, to);
}

TEST(get_random_odd_between, distribution_test_from_even_to_even) 
{
   const int repetitions = 100000;
   const int buckets = 100;
   const int from = 0;
   const int to = buckets;
   
   std::vector<int> event_occurences = generate_events_between(
      mzlib::get_random_odd_between<int>,
      repetitions, buckets, 
      from, to);

   assert_distribution(
      mzlib::is_odd<int>,
      event_occurences,
      repetitions, buckets, 
      from, to);
}

TEST(get_random_odd_between, distribution_test_from_odd_to_even) 
{
   const int repetitions = 100000;
   const int buckets = 100;
   const int from = 1;
   const int to = buckets;
   
   std::vector<int> event_occurences = generate_events_between(
      mzlib::get_random_odd_between<int>,
      repetitions, buckets, 
      from, to);

   assert_distribution(
      mzlib::is_odd<int>,
      event_occurences,
      repetitions, buckets, 
      from, to);
}

TEST(get_random_odd_between, distribution_test_from_even_to_odd) 
{
   const int repetitions = 100000;
   const int buckets = 100;
   const int from = 0;
   const int to = 97;
   
   std::vector<int> event_occurences = generate_events_between(
      mzlib::get_random_odd_between<int>,
      repetitions, buckets, 
      from, to);
   
   assert_distribution(
      mzlib::is_odd<int>,
      event_occurences,
      repetitions, buckets, 
      from, to);
}

TEST(get_random_odd_between, distribution_test_from_odd_to_odd) 
{
   const int repetitions = 100000;
   const int buckets = 100;
   const int from = 1;
   const int to = 97;
   
   std::vector<int> event_occurences = generate_events_between(
      mzlib::get_random_odd_between<int>,
      repetitions, buckets, 
      from, to);
   
   assert_distribution(
      mzlib::is_odd<int>,
      event_occurences,
      repetitions, buckets, 
      from, to);
}
