//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_GRAPH_OPERATIONS_H
#define MZLIB_GRAPH_OPERATIONS_H

#include "graph.h"
#include "../tools/extract_keys.h"

namespace mzlib {
namespace graph {

template<typename VertexKey>
void add (
   graph<VertexKey>& g,
   const vertex<VertexKey>& v)
{
   g.vertices[v.key] = v;
}

template<typename VertexKey>
void add (
   graph<VertexKey>& g,
   const edge<VertexKey> e)
{
   g.edges.insert(e);
}

template<typename VertexKey>
bool is_incident (
   const graph<VertexKey>& g, 
   const vertex<VertexKey>& v, 
   const edge<VertexKey>& e)
{
   return (e.vertices[0] == v || e.vertices[1] == v);
}

template<typename VertexKey>
bool is_outgoing (
   const graph<VertexKey>& g, 
   const vertex<VertexKey>& v, 
   const edge<VertexKey>& e)
{
   return (e.vertices[0] == v);
}

template<typename VertexKey>
bool is_incoming (
   const graph<VertexKey>& g, 
   const vertex<VertexKey>& v, 
   const edge<VertexKey>& e)
{
   return (e.vertices[1] == v);
}

template<typename VertexKey>
std::set<edge<VertexKey>> get_outgoing(
   const graph<VertexKey>& g, 
   const vertex<VertexKey>& v)
{
   std::set<edge<VertexKey>> outgoing;
   
   for(const edge<VertexKey>& e : v)
      if(e.direction == edge_direction::undirected && is_incident(g, v, e))
         outgoing.insert(v);
      else if (e.direction == edge_direction::directed && is_outgoing(g, v, e))
         outgoing.insert(v);
   
   return outgoing;
}

template<typename VertexKey>
std::set<edge<VertexKey>> get_incoming(
   const graph<VertexKey>& g, 
   const vertex<VertexKey>& v)
{
   std::set<edge<VertexKey>> incoming;
   
   for(const edge<VertexKey>& e : v)
      if(e.direction == edge_direction::undirected && is_incident(g, v, e))
         incoming.insert(v);
      else if (e.direction == edge_direction::directed && is_incoming(g, v, e))
         incoming.insert(v);
   
   return incoming;
}

template<typename VertexKey>
std::size_t size(
   const graph<VertexKey>& g)
{
   return g.edges.count();
}

template<typename VertexKey>
std::size_t order(
   const graph<VertexKey>& g)
{
   return g.vertices.size();
}

template<typename VertexKey>
bool exists_edge(
   const graph<VertexKey>& g, 
   const VertexKey& from, 
   const VertexKey& to)
{
   if (from == to) 
      return false;
   
   for(const auto& edge : g.edges)
      if(edge.vertices[0] == from && edge.vertices[1] == to)
         return true;
   
   return false;
}

template<typename VertexKey>
std::optional<edge<VertexKey>> get_cheapest_edge(
   const graph<VertexKey>& g, 
   const VertexKey& from, 
   const VertexKey& to)
{
   std::optional<edge<VertexKey>> cheapest_edge;
   
   for(const auto& edge : g.edges)
      if(edge.vertices[0] == from && edge.vertices[1] == to)
         if(!cheapest_edge || cheapest_edge->cost > edge.cost)
         cheapest_edge = edge;
   
   return cheapest_edge;
}

template<typename VertexKey>
double get_cheapest_direct_path_cost(
   const graph<VertexKey>& g, 
   const VertexKey& from, 
   const VertexKey& to)
{
   // this is why there's a path in the name. even if there is no such edge,
   // it costs 0 to arrive to same node. 
   if (from == to) return 0;
   
   std::optional<edge<VertexKey>> cheapest_edge =
      get_cheapest_edge(g, from, to);
   
   return (
      cheapest_edge ? 
         cheapest_edge->cost : 
         std::numeric_limits<double>::infinity());
}

template<typename VertexKey>
std::set<VertexKey> get_vertices_keys(
   const graph<VertexKey>& g)
{
   std::set<VertexKey> keys = extract_keys(g.vertices);
   return keys;
}

} // namespace graph
} // namespace mzlib

#endif // MZLIB_GRAPH_OPERATIONS_H
