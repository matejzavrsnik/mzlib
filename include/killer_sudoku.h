//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_KILLER_SUDOKU_H
#define MZLIB_KILLER_SUDOKU_H

#include "sudoku.h"

namespace mzlib {
   
class killer_sudoku : public sudoku 
{

public:
   
   struct region_sum
   {
      short region;
      int sum;
   };
   
   using regions = std::vector<short>;
   using region_sums = std::vector<region_sum>;
   
   killer_sudoku(
      const puzzle& puzzle,
      const regions& regions,
      const region_sums& region_sums)
   {
      set_puzzle(puzzle);
      set_regions(regions);
      set_region_sums(region_sums);
   }

   killer_sudoku() = default;
   killer_sudoku(const killer_sudoku& orig) = default;
   killer_sudoku& operator=(const killer_sudoku& orig) = default;
   ~killer_sudoku() = default;
   
   void set_regions(const regions& regions)
   {
      m_regions.assign(regions.begin(), regions.end());
   }
   
   void set_region_sums(const region_sums& region_sums)
   {
      m_region_sums.assign(region_sums.begin(), region_sums.end());
   }
      
private:
   
   bool value_fails_additional_restrictions(cell_coordinates coordinates) const override
   {
      if (number_exceeds_sum_in_region(coordinates)) {
         return true;
      }
      return false;
   }
   
   bool number_exceeds_sum_in_region(cell_coordinates coordinates) const
   {
      short region = get_region(coordinates);
      int sum_in_region = get_sum_of_region(region);

      int partial_sum = 0;
      auto region_it = m_regions.begin(); 
      while((region_it = std::find(region_it, m_regions.end(), region)) != m_regions.end())
      {
         auto coor = get_coordinates_of_region(region_it);
         partial_sum += get_cell(coor);
         if(partial_sum > sum_in_region) {
            return true;
         }
         ++region_it;
      };
      
      return false;
   }
   
   short get_region(cell_coordinates coordinates) const
   {
      auto index = mzlib::get_index_from_coordinates(coordinates, 9);
      return m_regions[index];
   }
   
   int get_sum_of_region(short region) const
   {
      auto region_sum_it = std::find_if(m_region_sums.begin(), m_region_sums.end(), 
         [&region](const region_sum& s) {
            return s.region == region;
         });
      if (region_sum_it == m_region_sums.end()) {
         return 0;
      }
      return region_sum_it->sum;
   }
   
   cell_coordinates get_coordinates_of_region(regions::const_iterator it) const
   {
      int index = std::distance(m_regions.cbegin(), it);
      cell_coordinates coor = mzlib::get_coordinates_from_index(index, 9);
      return coor;
   }
   
   regions m_regions;
   region_sums m_region_sums;
};

} // namespaces

#endif // MZLIB_KILLER_SUDOKU_H

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_KILLER_SUDOKU_TESTS_H
#define MZLIB_KILLER_SUDOKU_TESTS_H

// It appears to be converging towards solution, but the last time I ran this it
// took 15h and it didn't solve yet. I gave up. Obviously, backtracking is wrong
// tool for the job, even though it worked surprisingly well for normal sudokus.
TEST(killer_sudoku, DISABLED_demo1) 
{
   mzlib::killer_sudoku::puzzle puzzle {
      0,0,0, 0,0,0, 0,0,0, 
      0,0,0, 0,0,0, 0,0,0,
      0,0,0, 0,0,0, 0,0,0,

      0,0,0, 0,0,0, 0,0,0,
      0,0,0, 0,0,0, 0,0,0,
      0,0,0, 0,0,0, 0,0,0,

      0,0,0, 0,0,0, 0,0,0,
      0,0,0, 0,0,0, 0,0,0,
      0,0,0, 0,0,0, 0,0,0
   };

   mzlib::killer_sudoku::regions regions {
      1 ,2 ,3  ,3 ,5 ,5  ,5 ,5 ,5 , 
      1 ,2 ,4  ,4 ,6 ,6  ,6 ,7 ,7 ,
      1 ,2 ,4  ,4 ,8 ,9  ,9 ,9 ,10,

      11,2 ,12 ,13,8 ,8  ,14,9 ,10,
      11,11,12 ,13,13,13 ,14,15,15,
      16,17,12 ,18,18,13 ,14,20,15,

      16,17,17 ,17,18,19 ,19,20,21,
      22,22,23 ,23,23,19 ,19,20,21,
      24,24,24 ,24,24,25 ,25,20,21
   };
   
   mzlib::killer_sudoku::region_sums region_sums {
      {1 ,18}, {2 ,22}, {3 ,5 }, {4 ,18}, {5 ,35},
      {6 ,15}, {7 ,9 }, {8 ,10}, {9 ,16}, {10,13},
      {11,7 }, {12,20}, {13,23}, {14,16}, {15,15},
      {16,13}, {17,23}, {18,18}, {19,20}, {20,16},
      {21,13}, {22,17}, {23,12}, {24,19}, {25,12}
   };
   std::cout << "correct";
   mzlib::killer_sudoku original(puzzle, regions, region_sums);
   original.solve();
   
   //std::cout << original << std::endl;
   //std::cout << solved << std::endl;
}

#endif // MZLIB_KILLER_SUDOKU_TESTS_H

#endif // MZLIB_BUILDING_TESTS