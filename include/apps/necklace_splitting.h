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


#include <vector>
#include <optional>
#include <numeric>

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
   int cut = 0;
   for(auto it = begin; it != end; ++it)
   {
      if (it == cuts[cut])
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
try_combinatorial(Iterator begin, Iterator end, int num_cuts)
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

}

}

#endif // MZLIB_STOLEN_NECKLACE_H