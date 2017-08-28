//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_SUDOKU_H
#define MZLIB_SUDOKU_H

#include "tools/index_iterator_conversions.h"

#include <vector>
#include <iostream>
#include <initializer_list>
#include <algorithm>

namespace mzlib {
   
class sudoku 
{
   
public:
   
   using puzzle = std::vector<short>;
   using cell_coordinates = std::array<uint, 2>;
   const short has_no_value = 0;
    
   sudoku(const std::initializer_list<short>& puzzle)
   {
      set_puzzle(puzzle);
   }

   sudoku() = default;
   sudoku(const sudoku& orig) = default;
   sudoku& operator=(const sudoku& orig) = default;
   ~sudoku() = default;
    
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
      short number = 1;
      if(curr == m_puzzle.end())
      {
         m_solved = true;
      }
      else
      {
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
   
   void simple_out ()
   {
      for(uint i=0; i<80; ++i) {
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
      uint i = coordinates[0];
      uint j = coordinates[1];
      for(uint k=0; k<9; ++k)
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
      uint i = coordinates[0];
      uint j = coordinates[1];
      // which square in sudoku do these coordinate fall into?
      int row = i / 3;
      int col = j / 3;
      // what are the edges of this square?
      uint row_from, row_to, col_from, col_to;
      row_from = row*3;
      row_to = row_from + 3 - 1;
      col_from = col*3;
      col_to = col_from + 3 - 1;
      // is there a number repeated inside this square?
      for( uint k = row_from; k <= row_to; k++ ) {
         for ( uint l = col_from; l <= col_to; l++ ) {
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

bool operator== (const mzlib::sudoku& puzzle1, const mzlib::sudoku& puzzle2)
{
   for(uint j=0; j<9; ++j) {
      for(uint i=0; i<9; ++i) {
         mzlib::sudoku::cell_coordinates coordinates{i,j};
         if(puzzle1.get_cell(coordinates) != puzzle2.get_cell(coordinates)) {
            return false;
         }
      }
   }
   return true;
}

bool operator!= (const mzlib::sudoku& puzzle1, const mzlib::sudoku& puzzle2)
{
   return !operator==(puzzle1, puzzle2);
}

std::ostream& operator<< (std::ostream& os, const mzlib::sudoku& puzzle)
{
   for(uint j=0; j<9; ++j) {
      for(uint i=0; i<9; ++i) {
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

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_SUDOKU_TESTS_H
#define MZLIB_SUDOKU_TESTS_H

TEST(sudoku, demo1) 
{
   mzlib::sudoku original {
      0,5,9, 0,2,0, 4,6,0, 
      1,0,0, 4,0,3, 0,0,8,
      3,0,0, 0,7,0, 0,0,2,

      0,3,0, 8,0,9, 0,2,0,
      6,0,5, 0,0,0, 3,0,7,
      0,1,0, 7,0,6, 0,4,0,

      2,0,0, 0,1,0, 0,0,4,
      9,0,0, 3,0,2, 0,0,5,
      0,7,8, 0,6,0, 2,3,0
   };

   mzlib::sudoku solution {
      7,5,9, 1,2,8, 4,6,3, 
      1,2,6, 4,9,3, 7,5,8, 
      3,8,4, 6,7,5, 9,1,2, 

      4,3,7, 8,5,9, 1,2,6, 
      6,9,5, 2,4,1, 3,8,7, 
      8,1,2, 7,3,6, 5,4,9, 

      2,6,3, 5,1,7, 8,9,4, 
      9,4,1, 3,8,2, 6,7,5, 
      5,7,8, 9,6,4, 2,3,1
   };

   mzlib::sudoku solved = original;
   solved.solve();
   ASSERT_TRUE(solution == solved);
   
   //std::cout << original << std::endl;
   //std::cout << solved << std::endl;
}

TEST(sudoku, demo2) 
{
   mzlib::sudoku original {
      0,0,0, 0,0,0, 6,8,0, 
      0,0,0, 0,7,3, 0,0,9,
      3,0,9, 0,0,0, 0,4,5,

      4,9,0, 0,0,0, 0,0,0,
      8,0,3, 0,5,0, 9,0,2,
      0,0,0, 0,0,0, 0,3,6,

      9,6,0, 0,0,0, 3,0,8,
      7,0,0, 6,8,0, 0,0,0,
      0,2,8, 0,0,0, 0,0,0
   };

   mzlib::sudoku solution {
      1,7,2, 5,4,9, 6,8,3, 
      6,4,5, 8,7,3, 2,1,9, 
      3,8,9, 2,6,1, 7,4,5, 

      4,9,6, 3,2,7, 8,5,1, 
      8,1,3, 4,5,6, 9,7,2, 
      2,5,7, 1,9,8, 4,3,6, 

      9,6,4, 7,1,5, 3,2,8, 
      7,3,1, 6,8,2, 5,9,4, 
      5,2,8, 9,3,4, 1,6,7 
   };

   mzlib::sudoku solved = original;
   solved.solve();
   ASSERT_TRUE(solution == solved);
   
   //std::cout << original << std::endl;
   //std::cout << solved << std::endl;
}

TEST(sudoku, demo3) 
{
   mzlib::sudoku original {
      0,0,0, 2,0,0, 0,6,3, 
      3,0,0, 0,0,5, 4,0,1,
      0,0,1, 0,0,3, 9,8,0,

      0,0,0, 0,0,0, 0,9,0,
      0,0,0, 5,3,8, 0,0,0,
      0,3,0, 0,0,0, 0,0,0,

      0,2,6, 3,0,0, 5,0,0,
      5,0,3, 7,0,0, 0,0,8,
      4,7,0, 0,0,1, 0,0,0
   };

   mzlib::sudoku solution {
      8,5,4, 2,1,9, 7,6,3,
      3,9,7, 8,6,5, 4,2,1,
      2,6,1, 4,7,3, 9,8,5,

      7,8,5, 1,2,6, 3,9,4,
      6,4,9, 5,3,8, 1,7,2,
      1,3,2, 9,4,7, 8,5,6,

      9,2,6, 3,8,4, 5,1,7,
      5,1,3, 7,9,2, 6,4,8,
      4,7,8, 6,5,1, 2,3,9
   };

   mzlib::sudoku solved = original;
   solved.solve();
   ASSERT_TRUE(solution == solved);
   
   //std::cout << original << std::endl;
   //std::cout << solved << std::endl;
}

TEST(sudoku, long_demo4) 
{
   mzlib::sudoku original {
      0,1,0, 0,0,4, 0,0,0, 
      0,0,6, 8,0,5, 0,0,1,
      5,0,3, 7,0,1, 9,0,0,

      8,0,4, 0,0,7, 0,0,0,
      0,0,0, 0,0,0, 0,0,0,
      0,0,0, 3,0,0, 6,0,9,

      0,0,1, 5,0,8, 2,0,4,
      6,0,0, 4,0,3, 1,0,0,
      0,0,0, 2,0,0, 0,5,0
   };

   mzlib::sudoku solution {
      2,1,8, 9,6,4, 5,3,7,
      9,7,6, 8,3,5, 4,2,1,
      5,4,3, 7,2,1, 9,8,6,

      8,9,4, 6,5,7, 3,1,2,
      3,6,2, 1,4,9, 8,7,5,
      1,5,7, 3,8,2, 6,4,9,

      7,3,1, 5,9,8, 2,6,4,
      6,2,5, 4,7,3, 1,9,8,
      4,8,9, 2,1,6, 7,5,3
   };

   mzlib::sudoku solved = original;
   solved.solve();
   ASSERT_TRUE(solution == solved);
   
   //std::cout << original << std::endl;
   //std::cout << solved << std::endl;
}

TEST(sudoku, long_demo5) 
{
   mzlib::sudoku original {
      1,3,0, 0,0,0, 0,0,0, 
      0,0,2, 0,5,0, 0,3,0,
      0,0,9, 0,0,2, 0,8,0,

      5,0,0, 3,0,0, 0,1,0,
      0,0,0, 1,0,6, 0,0,0,
      0,1,0, 0,0,5, 0,0,7,

      0,9,0, 4,0,0, 3,0,0,
      0,8,0, 0,2,0, 5,0,0,
      0,0,0, 0,0,0, 0,6,4
   };

   mzlib::sudoku solution {
      1,3,8, 9,6,4, 7,2,5,
      7,6,2, 8,5,1, 4,3,9,
      4,5,9, 7,3,2, 1,8,6,

      5,4,6, 3,7,9, 2,1,8,
      8,2,7, 1,4,6, 9,5,3,
      9,1,3, 2,8,5, 6,4,7,

      6,9,5, 4,1,8, 3,7,2,
      3,8,4, 6,2,7, 5,9,1,
      2,7,1, 5,9,3, 8,6,4
   };

   mzlib::sudoku solved = original;
   solved.solve();
   ASSERT_TRUE(solution == solved);
   
   //std::cout << original << std::endl;
   //std::cout << solved << std::endl;
}

#endif // MZLIB_SUDOKU_TESTS_H

#endif // MZLIB_BUILDING_TESTS
