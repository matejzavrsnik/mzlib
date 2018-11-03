//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "necklace_splitting.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <vector>

using namespace ::testing;

TEST(stolen_necklace, evaluate_solution_is)
{
   std::string necklace = "aaabaaabaabbbb" ; // aaaba aabaabb bb
   
   std::vector<std::string::iterator> solution_candidate{
      necklace.begin()+5,
      necklace.begin()+12};
   
   bool solution = mzlib::necklace::evaluate_solution(
      necklace.begin(), 
      necklace.end(),
      solution_candidate);
   
   ASSERT_TRUE(solution);
}

TEST(stolen_necklace, evaluate_solution_isnt)
{
   std::string necklace = "aaabaaabaabbbb" ; // aaaba aabaabb bb
   
   std::vector<std::string::iterator> solution_candidate{
      necklace.begin()+6,
      necklace.begin()+12};
   
   bool solution = mzlib::necklace::evaluate_solution(
      necklace.begin(), 
      necklace.end(),
      solution_candidate);
   
   ASSERT_FALSE(solution);
}

TEST(stolen_necklace, solve)
{
   std::vector<int> necklace = {1,1,2,2,2,2,1,1};
   
   auto cuts = mzlib::necklace::solve(
      necklace.begin(), necklace.end());
   
   ASSERT_THAT(cuts, UnorderedElementsAre(
      necklace.begin()+4));
}

TEST(stolen_necklace, solve_string_with_letters)
{
   std::string necklace = "aaabaaabaabbbb"; // aaaba aabaabb bb

   auto cuts = mzlib::necklace::solve(
      necklace.begin(), necklace.end());
   
   ASSERT_THAT(cuts, UnorderedElementsAre(
      necklace.begin()+5,
      necklace.begin()+12));
}

TEST(stolen_necklace, solve_has_no_solution)
{
   std::string necklace = "aaabaaabaabbb";

   auto cuts = mzlib::necklace::solve(
      necklace.begin(), necklace.end());
   
   ASSERT_TRUE(cuts.empty());
}