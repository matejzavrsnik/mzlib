//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_PLOT_OPERATIONS_H
#define	MZLIB_PLOT_OPERATIONS_H

#include "../laws/linear_interpolation.h"
#include "../lang/exceptions.h"
#include "../tools/converters.h"

#include <map>

namespace mzlib {
   
// Will traverse a collection of plots and return all points' x-es.
inline std::vector<double> collect_all_x(
   const std::vector<std::map<double, double>>& all_plots_points)
{
   std::vector<double> all_x;
   for(const auto& plot_points : all_plots_points)
      for(const auto& point : plot_points)
         all_x.push_back(point.first);
   return all_x;
}

// Will get y at specific x from the plot
inline double get_y_from_plot(
   const double x, 
   const std::map<double, double>& plot_points)
{
   const auto point_it = plot_points.lower_bound(x);

   if(point_it == plot_points.end())
   {
      throw mzlib::exception::not_found();
   }

   const std::pair<double,double>& point = *point_it;

   if(point.first == x)
   {
      return point.second;
   }
   else if(point_it != plot_points.begin())
   {
      const std::pair<double,double>& prev_point = *std::prev(point_it);

      return mzlib::law::linear_interpolation(
         convert<mzlib::point2d>(prev_point), 
         convert<mzlib::point2d>(point),
         x);
   }
   else
   {
      throw mzlib::exception::not_found();
   }
}

// Will get all y-s at specific x from each of the plots in a collection
inline std::vector<double> get_y_from_plots(
   const double x, 
   const std::vector<std::map<double, double>>& all_plots_points)
{
   std::vector<double> all_y;
   for(const auto& plot_points : all_plots_points)
   {
      all_y.push_back(get_y_from_plot(x, plot_points));
   }
   return all_y;
}

} // namespace

#endif /* MZLIB_PLOT_OPERATIONS_H */
