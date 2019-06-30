//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_AVERAGE_PLOT_H
#define MZLIB_AVERAGE_PLOT_H

#include "vector.h"
#include "plot_operations.h"
#include "../iterators/average.h"

#include <vector>
#include <map>

namespace mzlib
{
   
template<typename Iterator>
class average_plot
{
   std::vector<std::map<double, double>> m_all_plots_points;
   std::vector<mzlib::point2d> m_average_plot;
   
public:
   
   void add_plot(Iterator plot_begin, Iterator plot_end)
   {
      Iterator data_point = plot_begin;
      std::map<double, double> plot_points;
      while(data_point != plot_end)
      {
         const auto& x = (*data_point)[0];
         const auto& y = (*data_point)[1];
         plot_points[x] = y;
         ++data_point;
      }
      m_all_plots_points.push_back(plot_points);
   }
   
   void calculate()
   {      
      std::map<double, double> points = average_points(m_all_plots_points);      
      
      create_plot(points);
   }
   
   const std::vector<mzlib::point2d>& get() const
   {
      return m_average_plot;
   }
   
private:
   
   std::map<double, double> average_points(
      const std::vector<std::map<double, double>>& all_plots_points)
   {
      const std::vector<double> all_x = collect_all_x(all_plots_points);

      std::map<double, double> avg_points;
      for(const double& x : all_x) 
      {
         try 
         {
            const std::vector<double> all_y = get_y_from_plots(x, all_plots_points);
            const double avg_y = mzlib::average(all_y.begin(), all_y.end());
            avg_points[x] = avg_y;
            // I am aware of the possibility that the exact x will already exist, 
            // but I think occasional superfluous calculation of average will 
            // have lesser performance penalty than checking for existing x.
         }
         catch(mzlib::exception::not_found&) 
         {
            // nothing to worry about; simply means that on this plot there is
            // no y at this x for some reason
         }
      }
      return avg_points;
   }
   
   void create_plot(
      const std::map<double, double>& average_points)
   {
      for(const std::pair<double,double>& average_point : average_points)
      {
         m_average_plot.push_back(convert<mzlib::point2d>(average_point));
      }
   }
   

};

} // namespace

#endif // MZLIB_AVERAGE_PLOT_H

