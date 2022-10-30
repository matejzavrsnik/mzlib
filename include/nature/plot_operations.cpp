//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "plot_operations.h"

using namespace ::testing;

TEST(plot_operations_collect_all_x, basic) 
{
   std::vector<std::map<double, double>> all_plots_points =
      {
         {{0.1,0.2},{0.3,0.4},{0.5,0.6}},
         {{0.9,1.0},{1.2,1.3},{1.4,1.5}},
         {{1.8,1.9},{2.0,2.1},{2.2,2.3}}
      };
   
   auto all_x = mzlib::collect_all_x(all_plots_points);
   
   ASSERT_THAT(all_x, UnorderedElementsAre(0.1, 0.3, 0.5, 0.9, 1.2, 1.4, 1.8, 2.0, 2.2));
}

TEST(get_y_from_plot, three_points_x_between)
{
   std::map<double, double> plot = {{2.0,2.0},{3.0,3.0},{4.0,1.0}};
   
   ASSERT_DOUBLE_EQ(2.5, mzlib::get_y_from_plot(2.5, plot));
   ASSERT_DOUBLE_EQ(2.0, mzlib::get_y_from_plot(3.5, plot));
}

TEST(get_y_from_plot, three_points_x_exactly_last_point)
{
   std::map<double, double> plot = {{2.0,2.0},{3.0,3.0},{4.0,1.0}};
   
   ASSERT_DOUBLE_EQ(1.0, mzlib::get_y_from_plot(4.0, plot));
}

TEST(get_y_from_plot, three_points_x_exactly_first_point)
{
   std::map<double, double> plot = {{2.0,2.0},{3.0,3.0},{4.0,1.0}};
   
   ASSERT_DOUBLE_EQ(2.0, mzlib::get_y_from_plot(2.0, plot));
}

TEST(get_y_from_plot, three_points_x_before_first_point)
{
   std::map<double, double> plot = {{2.0,2.0},{3.0,3.0},{4.0,1.0}};
   
   ASSERT_THROW(mzlib::get_y_from_plot(1.0, plot), mzlib::exception::not_found);
}

TEST(get_y_from_plot, three_points_x_after_last_point)
{
   std::map<double, double> plot = {{2.0,2.0},{3.0,3.0},{4.0,1.0}};
   
   ASSERT_THROW(mzlib::get_y_from_plot(5.0, plot), mzlib::exception::not_found);
}

TEST(get_y_from_plots, basic)
{
   std::vector<std::map<double, double>> all_plots_points =
      {
         {{1.1,2.1},{3.1,4.1},{5.1,6.1}},
         {{1.2,2.4},{3.2,4.4},{5.2,6.4}},
         {{1.3,2.7},{3.3,4.7},{5.3,6.7}}
      };
   
   std::vector<double> points = mzlib::get_y_from_plots(2.0, all_plots_points);
   
   ASSERT_EQ(3, points.size());
   ASSERT_DOUBLE_EQ(3.0, points[0]);
   ASSERT_DOUBLE_EQ(3.2, points[1]);
   ASSERT_DOUBLE_EQ(3.4, points[2]);
}

TEST(get_y_from_plots, before_all_points)
{
   std::vector<std::map<double, double>> all_plots_points =
      {
         {{1.1,2.1},{3.1,4.1},{5.1,6.1}},
         {{1.2,2.4},{3.2,4.4},{5.2,6.4}},
         {{1.3,2.7},{3.3,4.7},{5.3,6.7}}
      };
   
   ASSERT_THROW(mzlib::get_y_from_plots(1.0, all_plots_points), 
      mzlib::exception::not_found);
}

TEST(get_y_from_plots, before_some_points)
{
   std::vector<std::map<double, double>> all_plots_points =
      {
         {{1.1,2.1},{3.1,4.1},{5.1,6.1}},
         {{1.2,2.4},{3.2,4.4},{5.2,6.4}},
         {{1.3,2.7},{3.3,4.7},{5.3,6.7}}
      };
   
   ASSERT_THROW(mzlib::get_y_from_plots(1.25, all_plots_points), 
      mzlib::exception::not_found);
}

TEST(get_y_from_plots, after_all_points)
{
   std::vector<std::map<double, double>> all_plots_points =
      {
         {{1.1,2.1},{3.1,4.1},{5.1,6.1}},
         {{1.2,2.4},{3.2,4.4},{5.2,6.4}},
         {{1.3,2.7},{3.3,4.7},{5.3,6.7}}
      };
   
   ASSERT_THROW(mzlib::get_y_from_plots(7.0, all_plots_points), 
      mzlib::exception::not_found);
}

TEST(get_y_from_plots, after_some_points)
{
   std::vector<std::map<double, double>> all_plots_points =
      {
         {{1.1,2.1},{3.1,4.1},{5.1,6.1}},
         {{1.2,2.4},{3.2,4.4},{5.2,6.4}},
         {{1.3,2.7},{3.3,4.7},{5.3,6.7}}
      };
   
   ASSERT_THROW(mzlib::get_y_from_plots(6.25, all_plots_points), 
      mzlib::exception::not_found);
}

