//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_NECKLACE_SPLITTING_H
#define MZLIB_NECKLACE_SPLITTING_H

#include "../tools/find_index_insert.h"
#include "../iterators/nested_iteration.h"
#include "../lang/value_type.h"

#include "../tools/random_with_parity.h"
#include "../tools/random.h"
#include "../lang/binary_options.h"
#include "../tools/rememberator.h"
#include "../iterators/index_conversion.h"
#include "../iterators/copy_modify.h"

#include <vector>
#include <optional>
#include <numeric>

#include <algorithm>
#include <functional>

namespace mzlib {

namespace necklace {

void switch_thief(int& thief)
{
   thief = thief == 0 ? 1 : 0;
}

// given solution candidate, confirm if solution or not
template<typename Iterator>
bool evaluate_solution(
   Iterator begin, 
   Iterator end, 
   const std::vector<Iterator>& cuts)
{
   using gem_type = mzlib::value_type<Iterator>;
   std::vector<gem_type> gems_cache;
   
   std::vector<std::vector<int>> loot = {{0,0},{0,0}};
   int thief = 0;
   auto cut = cuts.begin();
   for(auto it = begin; it != end; ++it)
   {
      // if crossing a cut
      if (cut != cuts.end() && it == *cut)
      {
         switch_thief(thief); // other thiefs loot from this point on
         ++cut; // wait for next suggested cut to come along
      }
      const auto gem = find_index_insert(gems_cache, *it);
      loot[thief][gem] += 1;
   }
   
   bool fair_split = 
      loot[0][0] == loot[1][0] &&
      loot[0][1] == loot[1][1];
   
   return fair_split;
}

// given number of cuts, try out all candidate solutions
template<typename Iterator>
std::optional<std::vector<Iterator>>
try_combinatorial(Iterator begin, Iterator end, size_t num_cuts)
{  
   mzlib::nested_iteration niter{begin, end, num_cuts};
   for(; !niter.end(); niter.next())
   {
      const auto candidate = niter.get();
      if(evaluate_solution(begin, end, candidate))
         return niter.get();
   }
   
   return std::nullopt;
}

// find minimum number of cuts needed to solve
// stolen necklace problem
template<typename Iterator>
std::vector<Iterator> 
solve(Iterator begin, Iterator end)
{
   auto size = std::distance(begin, end);
   for(int num_cuts = 1; num_cuts < size; ++num_cuts)
   {
      std::optional<std::vector<Iterator>> solution =
         try_combinatorial(begin, end, num_cuts);
      
      if(solution)
         return solution.value();
   }
   
   // empty vector if no solution
   return std::vector<Iterator>(); 
}

std::string make_readable(
   std::string puzzle, 
   const std::vector<size_t>& solution)
{
   for(auto vec_it = solution.rbegin(); 
      vec_it != solution.rend(); 
      ++vec_it)
   {
      const int cut_position = *vec_it;
      puzzle.insert(cut_position, 1, '|');
   }
   return puzzle;
}

std::string generate_foundation_necklace(int size)
{
   int count_a = mzlib::get_random_even_between(1, size);
   int count_b = size - count_a;
   
   std::string necklace = 
      std::string(count_a, 'a') + 
      std::string(count_b, 'b');
   
   return necklace;
}

std::optional<std::string> generate_random_necklace(
   int size,
   mzlib::rememberator<std::string>& already_done)
{
   int attempts = 0;
   const int max_attempts = 100;
   std::string necklace;
   
   do
   {
      // generate an appropriate number of each type of gems,
      // in this case letters a and b ...
      necklace = generate_foundation_necklace(size);
      // ... and then reshuffle
      std::shuffle(
         necklace.begin(), necklace.end(),
         mzlib::get_generator());

      ++attempts;
   }
   while(
      already_done.can_recall(necklace) 
      && attempts < max_attempts);

   // if you had to try many times it means probability to generate
   // new necklaces is below meaningful percent; let's just throw in the towel
   if (attempts >= max_attempts) 
      return std::nullopt;

   // don't do this one again
   already_done.remember(necklace);
   
   return necklace;
}

template<typename HandlerFunction>
void generate_puzzles(
   int size, 
   HandlerFunction handler_fun)
{
   if (size % 2 != 0) --size;
   if (size < 4) return;
   
   mzlib::option::stop stop;
   mzlib::rememberator<std::string> already_done;
   
   do
   {
      std::optional<std::string> necklace = 
         generate_random_necklace(size, already_done);
      
      // Can't find anymore? Give up.
      if (!necklace) return;
      
      std::vector<std::string::iterator> iter_cuts = solve(
         necklace->begin(), 
         necklace->end());
      
      if (!iter_cuts.empty())
      {
         std::vector<size_t> int_cuts;

         auto to_index_in_necklace =
            std::bind(
               get_index<std::string::iterator>,
                  necklace->begin(),
                  std::placeholders::_1);
         
         copy_modify(iter_cuts, int_cuts, to_index_in_necklace);
      
         stop = handler_fun(necklace.value(), int_cuts);
      }
   }
   while(!stop);
}

}

}

#endif // MZLIB_NECKLACE_SPLITTING_H