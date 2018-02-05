//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "killer_sudoku.h"

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