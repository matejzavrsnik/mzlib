//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_GRAPH_VERTEX_H
#define MZLIB_GRAPH_VERTEX_H

namespace mzlib {
namespace graph {
   
template<typename Key>
struct vertex
{
   Key key;
   // Decided to keep separate struct for vertex instead of just using whatever
   // key means in graphs so that I can add some kind of payload to vertexes
   // if I choose to.
};

template<typename Key>
bool operator==(const vertex<Key>& a, const vertex<Key>& b)
{
   return a.key == b.key;
}

template<typename Key>
bool operator<(const vertex<Key>& a, const vertex<Key>& b)
{
   return a.key < b.key;
}

using svertex = vertex<std::string>;

} // namespace graph
} // namespace mzlib

namespace std
{
   // make vertices hashable by key
   template<typename Key> 
   struct hash<mzlib::graph::vertex<Key>>
   {
      std::size_t operator()(const mzlib::graph::vertex<Key>& v) const noexcept
      {
         return std::hash<Key>{}(v.key);
      }
   };
}

#endif // MZLIB_GRAPH_VERTEX_H
