//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_SUDOKU_H
#define MZLIB_SUDOKU_H

#include "../tools/index_coordinate_conversions.h"

#include <vector>
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <array>

namespace mzlib {
   
class sudoku 
{
   
public:
   
   using puzzle = std::vector<short>;
   using cell_coordinates = std::array<unsigned int, 2>;
   const short has_no_value = 0;
    
   explicit sudoku(const std::initializer_list<short>& puzzle)
   {
      set_puzzle(puzzle);
   }

   sudoku() = default;
   sudoku(const sudoku& orig) = default;
   sudoku& operator=(const sudoku& orig) = default;
   virtual ~sudoku() = default;
    
   void set_puzzle(const std::initializer_list<short>& puzzle)
   {
      m_puzzle.assign(puzzle.begin(), puzzle.end());
   }
   
   void set_puzzle(const puzzle& puzzle)
   {
      m_puzzle.assign(puzzle.begin(), puzzle.end());
   }

   short get_cell(cell_coordinates coordinates) const
   {
      auto index = mzlib::get_index_from_coordinates(coordinates, 9);
      return m_puzzle[index];
   }

   void solve()
   {
      puzzle::iterator start = m_puzzle.begin();
      if(*start != has_no_value) {
         start = get_next_cell_without_value(m_puzzle.begin());
      }
      solve(start);
   }
   
private:

   puzzle m_puzzle;
   bool m_solved = false;
    
   void solve(puzzle::iterator curr)
   {
      if(curr == m_puzzle.end())
      {
         m_solved = true;
      }
      else
      {
         short number = 1;
         while(number <= 9 && !m_solved)
         {
            *curr = number;
            if(is_value_acceptable(curr))
            {
               //simple_out();
               auto next = get_next_cell_without_value(curr);
               solve(next);
            }
            ++number;
        }
        if(!m_solved) {
           *curr = 0;
        }
      }
   }
   
   void simple_out () const
   {
      for(unsigned int i=0; i<80; ++i) {
         if(m_puzzle[i] == 0) break;
         std::cout << m_puzzle[i];
         if((i+1)%3==0) std::cout << " ";
         if((i+1)%9==0) std::cout << " ";
      }
      std::cout << std::endl;
   }
   
   cell_coordinates get_coordinates_of_cell(puzzle::const_iterator it) const
   {
      int index = std::distance(m_puzzle.cbegin(), it);
      cell_coordinates coor = mzlib::get_coordinates_from_index(index, 9);
      return coor;
   }
   
   bool is_value_acceptable(puzzle::iterator current) const
   {
      cell_coordinates coor = get_coordinates_of_cell(current);
      
      if (is_number_repeated_in_row_or_column(coor)) {
         return false;
      }
      
      if (is_number_repeated_inside_square(coor)) {
         return false;
      }
      
      if (value_fails_additional_restrictions(coor)) {
         return false;
      }

      // if all checks passed, puzzle must be valid for this cell
      return true;
   }
   
   virtual bool value_fails_additional_restrictions(cell_coordinates) const
   {
      // an opportunity for extensions to implement additional restrictions
      return false;
   }
   
   bool is_number_repeated_in_row_or_column(cell_coordinates coordinates) const
   {
      unsigned int i = coordinates[0];
      unsigned int j = coordinates[1];
      for(unsigned int k=0; k<9; ++k)
      {
         if( ( k != i && get_cell({k,j}) == get_cell(coordinates) ) ||
             ( k != j && get_cell({i,k}) == get_cell(coordinates) ) ) 
         {
            return true;
         }
      }
      return false;
   }
   
   bool is_number_repeated_inside_square(cell_coordinates coordinates) const
   {
      unsigned int i = coordinates[0];
      unsigned int j = coordinates[1];
      // which square in sudoku do these coordinate fall into?
      int row = i / 3;
      int col = j / 3;
      // what are the edges of this square?
      unsigned int row_from, row_to, col_from, col_to;
      row_from = row*3;
      row_to = row_from + 3 - 1;
      col_from = col*3;
      col_to = col_from + 3 - 1;
      // is there a number repeated inside this square?
      for( unsigned int k = row_from; k <= row_to; k++ ) {
         for ( unsigned int l = col_from; l <= col_to; l++ ) {
            if( k != i && l != j && get_cell({k,l}) == get_cell(coordinates) ) {
               return true;
            }
         }
      }
      return false;
   }

   puzzle::iterator get_next_cell_without_value(puzzle::iterator curr)
   {
      return std::find(curr, m_puzzle.end(), has_no_value);
   }

};

} // namespaces

inline bool operator== (const mzlib::sudoku& puzzle1, const mzlib::sudoku& puzzle2)
{
   for(unsigned int j=0; j<9; ++j) {
      for(unsigned int i=0; i<9; ++i) {
         mzlib::sudoku::cell_coordinates coordinates{i,j};
         if(puzzle1.get_cell(coordinates) != puzzle2.get_cell(coordinates)) {
            return false;
         }
      }
   }
   return true;
}

inline bool operator!= (const mzlib::sudoku& puzzle1, const mzlib::sudoku& puzzle2)
{
   return !operator==(puzzle1, puzzle2);
}

inline std::ostream& operator<< (std::ostream& os, const mzlib::sudoku& puzzle)
{
   for(unsigned int j=0; j<9; ++j) {
      for(unsigned int i=0; i<9; ++i) {
         short val = puzzle.get_cell({i,j});
         if(i==0) {
            os << std::endl;
            if (j%3 == 0) os << std::endl;
            os << " ";
         }
         os << val;
         if((i+1)%3==0) os << " ";
      }
   }
   os << std::endl;
   return os;
}

#endif /* MZLIB_SUDOKU_H */
