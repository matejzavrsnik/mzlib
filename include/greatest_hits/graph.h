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
class graph
{
   
private:
   
   std::unordered_map<VertexKey, vertex<VertexKey>> m_vertices;
   std::unordered_set<edge<VertexKey>> m_edges;
   
public:
   
   const std::unordered_map<VertexKey, vertex<VertexKey>>& vertices() const
   {
      return m_vertices;
   }
   
   const std::unordered_set<edge<VertexKey>>& edges() const
   {
      return m_edges;
   }
   
   void add (const vertex<VertexKey>& v)
   {
      m_vertices[v.key] = v;
   }
   
   void add (const edge<VertexKey>& e)
   {
      for(const auto& v : e.vertices)
         if (m_vertices.count(v) == 0)
            add(vertex<VertexKey>{v});
      
      m_edges.insert(e);
   }
   
};

using sgraph = graph<std::string>;

} // namespace graph
} // namespace mzlib

#endif // MZLIB_GRAPH_H
