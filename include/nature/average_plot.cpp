//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "average_plot.h"

#include <vector>

TEST(average_plot, demo) 
{  
   std::vector<mzlib::point2d> ts1
      {{0,1},{1,2},{2,4},{3,8},{4,4},{5,2},{6,1}};
      
   std::vector<mzlib::point2d> ts2
      {{0,2},{1,3},{2,5},{3,9},{4,3},{5,1},{6,0}};
      
   std::vector<mzlib::point2d> ts3
      {{0,2},{1,2},{2,4},{3,9},{4,6},{5,2},{6,2}};

   using iterator = std::vector<mzlib::point2d>::iterator;
   mzlib::average_plot<iterator> avgplot;
      
   avgplot.add_plot(ts1.begin(), ts1.end());
   avgplot.add_plot(ts2.begin(), ts2.end());
   avgplot.add_plot(ts3.begin(), ts3.end());
      
   avgplot.calculate();
   
   const std::vector<mzlib::point2d>& average_plot = 
      avgplot.get();
   
   ASSERT_EQ(7, average_plot.size());
   ASSERT_DOUBLE_EQ(5.0 /3.0, average_plot[0][1]);
   ASSERT_DOUBLE_EQ(7.0 /3.0, average_plot[1][1]);
   ASSERT_DOUBLE_EQ(13.0/3.0, average_plot[2][1]);
   ASSERT_DOUBLE_EQ(26.0/3.0, average_plot[3][1]);
   ASSERT_DOUBLE_EQ(13.0/3.0, average_plot[4][1]);
   ASSERT_DOUBLE_EQ(5.0 /3.0, average_plot[5][1]);
   ASSERT_DOUBLE_EQ(3.0 /3.0, average_plot[6][1]);
   
   ASSERT_TRUE(true);
}

void assert_point2d_eq(mzlib::point2d p1, mzlib::point2d p2)
{
   ASSERT_DOUBLE_EQ(p1[0], p2[0]);
   ASSERT_DOUBLE_EQ(p1[1], p2[1]);
}

void assert_point2d_near(mzlib::point2d p1, mzlib::point2d p2, mzlib::point2d distance)
{
   ASSERT_NEAR(p1[0], p2[0], distance[0]);
   ASSERT_NEAR(p1[1], p2[1], distance[1]);
}

TEST(average_plot, x_axis_doesnt_exactly_match) 
{  
   std::vector<mzlib::point2d> ts1
      {{0.10,1},{1.10,2},{2.10,4},{3.10,8},{4.10,4},{5.10,2},{6.10,1}};
      
   std::vector<mzlib::point2d> ts2
      {{0.15,2},{1.15,3},{2.15,5},{3.00,9},{4.15,3},{5.15,1},{6.15,0}};
      
   std::vector<mzlib::point2d> ts3
      {{0.11,2},{0.98,2},{2.01,4},{3.12,9},{4.11,6},{4.97,2},{6.20,2}};

   using iterator = std::vector<mzlib::point2d>::iterator;
   mzlib::average_plot<iterator> avgplot;
      
   avgplot.add_plot(ts1.begin(), ts1.end());
   avgplot.add_plot(ts2.begin(), ts2.end());
   avgplot.add_plot(ts3.begin(), ts3.end());
      
   avgplot.calculate();
   
   const std::vector<mzlib::point2d>& average_plot = 
      avgplot.get();
   
   for(auto& dp : average_plot)
      std::cout << dp << std::endl;
   
   ASSERT_EQ(17, average_plot.size());
   assert_point2d_near( {0.15, 1.68333}, average_plot[0],  {0.01, 0.00001});
   assert_point2d_near( {0.98, 2.23667}, average_plot[1],  {0.01, 0.00001});
   assert_point2d_near( {1.10, 2.39434}, average_plot[2],  {0.01, 0.00001});
   assert_point2d_near( {1.15, 2.47670}, average_plot[3],  {0.01, 0.00001});
   assert_point2d_near( {2.01, 4.18000}, average_plot[4],  {0.01, 0.00001});
   assert_point2d_near( {2.10, 4.43514}, average_plot[5],  {0.01, 0.00001});
   assert_point2d_near( {2.15, 4.61021}, average_plot[6],  {0.01, 0.00001});
   assert_point2d_near( {3.00, 8.35315}, average_plot[7],  {0.01, 0.00001});
   assert_point2d_near( {3.10, 8.46272}, average_plot[8],  {0.01, 0.00001});
   assert_point2d_near( {3.12, 8.43130}, average_plot[9],  {0.01, 0.00001});
   assert_point2d_near( {4.10, 4.43039}, average_plot[10], {0.01, 0.00001});
   assert_point2d_near( {4.11, 4.39623}, average_plot[11], {0.01, 0.00001});
   assert_point2d_near( {4.15, 4.23798}, average_plot[12], {0.01, 0.00001});
   assert_point2d_near( {4.97, 1.87333}, average_plot[13], {0.01, 0.00001});
   assert_point2d_near( {5.10, 1.70000}, average_plot[14], {0.01, 0.00001});
   assert_point2d_near( {5.15, 1.65000}, average_plot[15], {0.01, 0.00001});
   assert_point2d_near( {6.10, 1.01667}, average_plot[16], {0.01, 0.00001});
}