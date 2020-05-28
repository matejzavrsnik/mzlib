//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_GRAPH_EDGE_H
#define MZLIB_GRAPH_EDGE_H

#include "graph_vertex.h"

namespace mzlib {
namespace graph {
   
// edge stuff

enum class edge_direction
{
   undirected,
   directed
};
   
template<typename VertexKey>
struct edge
{
   VertexKey vertices[2];
   double cost = 1;
   edge_direction direction = edge_direction::undirected;
};

template<typename VertexKey>
bool operator==(const edge<VertexKey>& a, const edge<VertexKey>& b)
{
   // two directed edges with different cost can't be the same
   if(a.direction != b.direction &&
      a.direction == edge_direction::directed &&
      a.cost != b.cost)
      return false;

   // given they are not directed with different costs ...
   
   // two edges that are incident to the same two vertices are the same
   if(a.vertices[0] == b.vertices[0] && 
      a.vertices[1] == b.vertices[1])
      return true;
   
   // they are different otherwise
   return false;
}

template<typename VertexKey>
bool operator<(const edge<VertexKey>& a, const edge<VertexKey>& b)
{
   if (a.vertices[0] < b.vertices[0]) { return true; }
   else if (a.vertices[0] > b.vertices[0]) { return false; }
   else if (a.vertices[1] < b.vertices[1]) { return true; }
   else if (a.vertices[1] > b.vertices[1]) { return false; }
   else if (a.direction == edge_direction::directed) {
      if (a.cost < b.cost) { return true; }
      else if (a.cost < b.cost) { return false; }
   }
   else { return false; }
}

using sedge = edge<std::string>;
   
} // namespace graph
} // namespace mzlib

namespace std
{
   
   template<typename VertexKey> struct hash<mzlib::graph::edge<VertexKey>>
   {
      std::size_t operator()(const mzlib::graph::edge<VertexKey>& e) const noexcept
      {
         std::size_t h1 = std::hash<VertexKey>{}(e.vertices[0]);
         std::size_t h2 = std::hash<VertexKey>{}(e.vertices[1]);
         return h1 ^ (h2 << 1);
      }
   };
}

#endif // MZLIB_GRAPH_EDGE_H
