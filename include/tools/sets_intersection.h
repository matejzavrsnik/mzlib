//
// Copyright (c) 2023 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#pragma once

#include "../lang/concepts.h"
#include <algorithm>
#include <iterator>

namespace mzlib
{

template <class T> concept back_insertable =
requires (T a) {
   a.push_back(*a.begin());
};

template <back_insertable Container>
Container
sets_intersection (
   const Container& intersection,
   const Container& container
)
{
   Container new_intersection;
   std::set_intersection(
      container.begin(), container.end(), intersection.begin(), intersection.end(), std::back_inserter(new_intersection)
   );
   return new_intersection;
}

template <back_insertable Container, back_insertable... Containers>
Container
sets_intersection (
   const Container& intersection,
   const Container& container,
   const Containers& ... additional
)
{
   Container new_intersection;
   std::set_intersection(
      container.begin(), container.end(), intersection.begin(), intersection.end(), std::back_inserter(new_intersection)
   );
   return sets_intersection(new_intersection, additional...);
}

template <class Container>
Container
sets_intersection (
   const Container& intersection,
   const Container& container
)
{
   Container new_intersection;
   std::set_intersection(
      container.begin(), container.end(), intersection.begin(), intersection.end(),
      std::inserter(new_intersection, new_intersection.end())
   );
   return new_intersection;
}

template <class Container, class... Containers>
Container
sets_intersection (
   const Container& intersection,
   const Container& container,
   const Containers& ... additional
)
{
   Container new_intersection;
   std::set_intersection(
      container.begin(), container.end(), intersection.begin(), intersection.end(),
      std::inserter(new_intersection, new_intersection.end())
   );
   return sets_intersection(new_intersection, additional...);
}

}
