//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include "get_neighbour_cells.h"
#include "get_all_cells.h"
#include "../tools/sets_intersection.h"
#include "../tools/to.h"
#include <set>

namespace mzlib::grid {

template <typename T>
bool
all_cells_allowed (
   const type<T>& grid,
   const cell& from,
   const cell& to
)
{
   return true;
}

template <typename T> using allowed_transition_fun_t = decltype(all_cells_allowed<T>);

template <typename T>
bool
destination_at_most_one_larger (
   const type<T>& grid,
   const cell& from,
   const cell& to
)
{
   return access(grid, to) - 1 <= access(grid, from);
}

namespace internal
{

template <typename T>
std::vector<cell>
allowed_transition_to (
   const type<T>& grid,
   const std::set<cell>& candidate_destinations,
   const cell& from,
   allowed_transition_fun_t<T> allowed_transition
)
{
   std::vector<cell> allowed;
   for (auto to: candidate_destinations)
      if (allowed_transition(grid, from, to))
         allowed.push_back(to);
   return allowed;
}

template <typename T>
std::vector<cell>
allowed_transition_from (
   const type<T>& grid,
   const std::set<cell>& candidate_sources,
   const cell& to,
   allowed_transition_fun_t<T> allowed_transition
)
{
   std::vector<cell> allowed;
   for (auto from: candidate_sources)
      if (allowed_transition(grid, from, to))
         allowed.push_back(from);
   return allowed;
}

}

template <typename T>
type<long>
single_source_shortest_path_bfs (
   const type<T>& grid,
   const cell& start,
   allowed_transition_fun_t<T> allowed_transition
)
{
   type<long> steps = construct<long>(
      size(grid), std::numeric_limits<long>::max()
   );

   std::set<cell> discovered;
   std::set<cell> undiscovered = to<std::set>(get_all_cells(grid));
   std::set<cell> frontier;

   frontier.insert(start);
   undiscovered.erase(start);

   bool problem_shrank = false;
   while (!undiscovered.empty() || !frontier.empty())
   {
      std::set<cell> next_frontier;
      problem_shrank = false;
      for (auto frontier_cell: frontier)
      {
         auto neighbours = to<std::set>(get_neighbouring_cells(grid, frontier_cell));

         auto discovered_neigbours = sets_intersection(neighbours, discovered);
         auto possible_sources = internal::allowed_transition_from(
            grid, discovered_neigbours, frontier_cell, allowed_transition
         );

         if (possible_sources.size() > 0)
         {
            // doesn't matter which, because in this algo all transitions cost 1
            auto source_cell = *possible_sources.begin();
            auto steps_to_get_this_far = access(steps, source_cell);
            access(steps, frontier_cell) = steps_to_get_this_far + 1;
         }
         else
         {
            access(steps, frontier_cell) = 0;
         }

         // this frontier_cell is now discovered
         discovered.insert(frontier_cell);

         auto undiscovered_neighbours = sets_intersection(neighbours, undiscovered);
         auto possible_destinations = internal::allowed_transition_to(
            grid, undiscovered_neighbours, frontier_cell, allowed_transition
         );

         for (auto possible_destination: possible_destinations)
         {
            next_frontier.insert(possible_destination);
            undiscovered.erase(possible_destination);
            problem_shrank = true;
         }
      }

      if (!problem_shrank)
         break; // none of the frontier cell_set were successful in progressing

      frontier = next_frontier;
   }

   return steps;
}

}
