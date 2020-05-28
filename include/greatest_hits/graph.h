//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_GRAPH_H
#define MZLIB_GRAPH_H

#include "graph_vertex.h"
#include "graph_edge.h"

#include <unordered_map>
#include <unordered_set>

namespace mzlib {
namespace graph {
   
template<typename VertexKey>
struct graph
{
   std::unordered_map<VertexKey, vertex<VertexKey>> vertices;
   std::unordered_set<edge<VertexKey>> edges;
};

using sgraph = graph<std::string>;

} // namespace graph
} // namespace mzlib

#endif // MZLIB_GRAPH_H
