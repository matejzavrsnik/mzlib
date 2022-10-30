//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "travelling_salesman_problem.h"

using namespace mzlib::graph;

TEST(travelling_salesman_problem, example_1) 
{
   sgraph g;
   g.add( svertex{ "1" } );
   g.add( sedge{ {"1", "2"}, 10, edge_direction::directed } );
   g.add( sedge{ {"1", "3"}, 15, edge_direction::directed } );
   g.add( sedge{ {"1", "4"}, 20, edge_direction::directed } );

   g.add( svertex{ "2" } );
   g.add( sedge{ {"2", "1"}, 5, edge_direction::directed } );
   g.add( sedge{ {"2", "3"}, 9, edge_direction::directed } );
   g.add( sedge{ {"2", "4"}, 10, edge_direction::directed } );

   g.add( svertex{ "3" } );
   g.add( sedge{ {"3", "1"}, 6, edge_direction::directed } );
   g.add( sedge{ {"3", "2"}, 13, edge_direction::directed } );
   g.add( sedge{ {"3", "4"}, 12, edge_direction::directed } );

   g.add( svertex{ "4" } );
   g.add( sedge{ {"4", "1"}, 8, edge_direction::directed } );
   g.add( sedge{ {"4", "2"}, 8, edge_direction::directed } );
   g.add( sedge{ {"4", "3"}, 9, edge_direction::directed } );

      
   std::vector<sedge> path = 
      mzlib::travelling_salesman_dynamic<std::string>(g);
   
   ASSERT_EQ(4, path.size());
   
   ASSERT_EQ("1", path[0].vertices[0]);
   ASSERT_EQ("2", path[0].vertices[1]);
   
   ASSERT_EQ("2", path[1].vertices[0]);
   ASSERT_EQ("4", path[1].vertices[1]);
   
   ASSERT_EQ("4", path[2].vertices[0]);
   ASSERT_EQ("3", path[2].vertices[1]);
   
   ASSERT_EQ("3", path[3].vertices[0]);
   ASSERT_EQ("1", path[3].vertices[1]);
  
}