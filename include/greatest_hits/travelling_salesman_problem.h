//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_TRAVELLING_SALESMAN_PROBLEM_H
#define MZLIB_TRAVELLING_SALESMAN_PROBLEM_H


#include "graph.h"
#include "graph_operations.h"


#include "../iterators/nested_iteration.h"
#include "../iterators/transform_to_values.h"
#include "../lang/value_type.h"
#include "../lang/hashable_set.h"

#include <unordered_set>
#include <unordered_map>
#include <set>
#include <vector>

namespace mzlib 
{

template<typename VertexKey>
using tsp_subproblems = 
   std::unordered_map<
      std::set<VertexKey> /* already visited cities */, 
      std::unordered_map<
         VertexKey /* current city */, 
         double /* minimal cost to get from already visited cities to current city */>>;
   
// nested namespace because these are not really useful outside this particular problem
namespace internal 
{

// the uglier parts of the problem to aid readability


template<typename VertexKey>
std::set<VertexKey> get_cities(
   const graph::graph<VertexKey>& g)
{
   return graph::get_vertices_keys(g);
}

template<typename VertexKey, typename Iterator>
std::set<VertexKey> get_subset_cities(
   mzlib::nested_iteration<Iterator>& subset_iteration)
{
   std::vector<typename std::set<VertexKey>::const_iterator> subset_it = subset_iteration.get();
   std::set<VertexKey> subset;
   transform_to_values(subset_it.begin(), subset_it.end(), std::inserter(subset, subset.end()));
   return subset;
}

template<typename VertexKey>
std::set<VertexKey> remove_city(
   const std::set<VertexKey>& cities, 
   VertexKey city)
{
   std::set<VertexKey> removed = cities;
   removed.erase(city);
   return removed;
}

template<typename VertexKey>
std::set<VertexKey> get_unvisited(
   const std::set<VertexKey>& all_cities, 
   const std::set<VertexKey>& visited)
{
   std::set<VertexKey> unvisited;
   std::set_difference (
      all_cities.begin(), all_cities.end(), 
      visited.begin(), visited.end(),
      std::inserter(unvisited, unvisited.end()));
   return unvisited;
}

template<typename VertexKey>
void if_better_remember(
   tsp_subproblems<VertexKey>& subproblems,
   const std::set<VertexKey>& subset,
   const VertexKey& next_city,
   const double& next_cost)
{
   if (subproblems[subset].count(next_city) == 0 || subproblems[subset][next_city] > next_cost)
      subproblems[subset][next_city] = next_cost;
}

template<typename VertexKey>
VertexKey find_cheapest_hop_source(
   const graph::graph<VertexKey>& g,
   const tsp_subproblems<VertexKey>& subproblems,
   const VertexKey& start_city,
   const std::set<VertexKey>& via_subset,
   const VertexKey& end_city)
{
   VertexKey cheapest_hop_source;
   double cheapest_hop = std::numeric_limits<double>::infinity();
   for(const VertexKey& second_last : via_subset) // for each possible second last hop
      if(second_last != start_city)
      {  
         const std::set<VertexKey>& via_subset_without = internal::remove_city(via_subset, second_last);
         double source_cost = subproblems.at(via_subset_without).at(second_last);
         double hop_cost = source_cost + graph::get_cheapest_direct_path_cost(g, second_last, end_city);
         if(hop_cost < cheapest_hop)
         {  
            cheapest_hop = hop_cost;
            cheapest_hop_source = second_last;
         }
      }
   return cheapest_hop_source;
}

} // namespace internal

// dynamic programming algorithm for solving travelling salesman problem
template<typename VertexKey>
tsp_subproblems<VertexKey> bellman_held_karp(
   const graph::graph<VertexKey>& g,
   const VertexKey& start_city)
{
   tsp_subproblems<VertexKey> subproblems;
   
   const std::set<VertexKey>& cities = internal::get_cities(g);
   
   // fill in for problem size = 1
   for(const auto& city_from : cities)
      for(const auto& city_to : cities)
         subproblems[{city_from}][city_to] = graph::get_cheapest_direct_path_cost(g, city_from, city_to);
         
   // fill in for problem size >= 2
   for(int problem_size=2; problem_size<order(g); ++problem_size) // for each subproblem size,
   {
      // for each subset of cities of size problem size
      mzlib::nested_iteration subset_iteration{ cities.begin(), cities.end(), problem_size };
      while(!subset_iteration.end())
      {  
         const std::set<VertexKey>& subset = internal::get_subset_cities<VertexKey>(subset_iteration);
         if (subset.count(start_city) > 0) // ... and that contains home,
         {
            for(const auto& current_city : subset) // for each city in this set ...
               if (current_city != start_city) // .. that isn't home
               {
                  // what was the cost to get to current_city from smaller subproblem?
                  const std::set<VertexKey>& subset_before = internal::remove_city(subset, current_city);
                  double current_cost = subproblems[subset_before][current_city];

                  for(const auto& next_city : internal::get_unvisited(cities, subset))
                  {
                     double next_cost = current_cost + graph::get_cheapest_direct_path_cost(g, current_city, next_city);
                     internal::if_better_remember(subproblems, subset, next_city, next_cost);
                  }

               }
         }
         subset_iteration.next();
      }
   }
       
   return subproblems;
}

template<typename VertexKey>
std::vector<graph::edge<VertexKey>> recreate_path(
   const graph::graph<VertexKey>& g,
   const VertexKey& start_city,
   const tsp_subproblems<VertexKey>& subproblems)
{
   std::vector<graph::edge<VertexKey>> path;
   
   VertexKey end_city = start_city;
   
   std::set<VertexKey> via_subset = internal::get_cities(g);
   
   // keep finding cheapest ways to get to end_city via subset
   for(int problem_size=order(g)-1; problem_size>0; --problem_size)
   {
      VertexKey cheapest_hop_source = 
         internal::find_cheapest_hop_source(
            g, subproblems, start_city, via_subset, end_city);
      
      path.push_back(graph::get_cheapest_edge(g, cheapest_hop_source, end_city).value());
      end_city = cheapest_hop_source;
      via_subset = internal::remove_city(via_subset, end_city);
   }

   // connect start and end
   path.push_back(
      graph::get_cheapest_edge(g, 
         path[0].vertices[1], 
         path[path.size()-1].vertices[0]).value());
   
   // because I started from the end I need to reverse the order of edges now
   std::reverse(path.begin(), path.end());
   
   return path;
}

template<typename VertexKey>
std::vector<graph::edge<VertexKey>> travelling_salesman_dynamic (
   const graph::graph<VertexKey>& g)
{
   // largely arbitrary but there needs to be a starting city
   const std::set<VertexKey>& cities = internal::get_cities(g);
   const VertexKey& start_city = *cities.begin();
   
   // solve with dynamic algorithm
   tsp_subproblems<VertexKey> subproblems = 
      bellman_held_karp(g, start_city);

   std::vector<graph::edge<VertexKey>> path = 
      recreate_path(g, start_city, subproblems);

   return path;
}

} // namespace mzlib

#endif // MZLIB_TRAVELLING_SALESMAN_PROBLEM_H
