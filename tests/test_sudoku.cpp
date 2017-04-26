//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/sudoku.h"
#include "gtest/gtest.h"

#include <vector>
#include <iostream>

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

TEST(sudoku, demo4) 
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

TEST(sudoku, demo5) 
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