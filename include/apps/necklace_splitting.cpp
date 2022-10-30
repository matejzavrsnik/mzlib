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

TEST(stolen_necklace, generate)
{
   std::vector<std::string> found_puzzles;
   
   mzlib::necklace::generate_puzzles(
      5,
      [&found_puzzles](std::string puzzle, const std::vector<size_t>& solution)
      {
         puzzle = mzlib::necklace::make_readable(puzzle, solution);
         found_puzzles.push_back(puzzle);
         return mzlib::option::stop::no;
      });
   
   ASSERT_THAT(found_puzzles, UnorderedElementsAre(
      "aa|aa",  "ba|ba",  "ba|ab", "ab|ab",
      "a|ab|b", "b|ba|a", "ab|ba"
      ));
}

TEST(stolen_necklace, DISABLED_solve_three_gems)
{
   std::string necklace = "rbrbrprppbbp" ; // rbr brpr ppb bp

   auto cuts = mzlib::necklace::solve(
      necklace.begin(), necklace.end());
   
   ASSERT_THAT(cuts, UnorderedElementsAre(
      necklace.begin()+3,
      necklace.begin()+7,
      necklace.begin()+10));
}