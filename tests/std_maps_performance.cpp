//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/lang/measure_operation.h"

#include <map>
#include <unordered_map>
#include <string>

#include "gtest/gtest.h"


TEST(maps_performance, DISABLED_test)
{
   const int top_level = 1100000;
   const int repetitions = 100000;

   std::map<std::string, std::string> justmap;
   std::unordered_map<std::string, std::string> unordered;

   std::cout << "map size,find plain,find unordered,ins+rem plain,ins+rem unordered" << std::endl;
   for(int i=1; i<top_level; i*=2)
   {
      std::cout << i << ",";
      
      // fill maps
      for (int j = 1; j < i; ++j)
      {
         std::string str = std::to_string(j) + "AnnSummersPasta";
         justmap[str] = str + "NotTried";
         unordered[str] = str + "NotTried";
      }

      
      double ms;
      ms = mzlib::get_average_operation_time(
         [&](){
            return justmap["WorstCase"];
         },
         repetitions
      );
      std::cout << ms << ",";

      
      ms = mzlib::get_average_operation_time(
         [&](){
            return unordered["WorstCase"];
         },
         repetitions
      );
      std::cout << ms << ",";


      ms = mzlib::get_average_operation_time(
         [&](){
            justmap["WorstCaseKey"] = "WorstCase";
            justmap.erase("WorstCaseKey");
         },
         repetitions
      );
      std::cout << ms << ",";

      
      ms = mzlib::get_average_operation_time(
         [&](){
            unordered["WorstCaseKey"] = "WorstCase";
            unordered.erase("WorstCaseKey");
         },
         repetitions
      );
      std::cout << ms << std::endl;


      // clear maps
      justmap.clear();
      unordered.clear();
   }
   
   ASSERT_TRUE(true);
}
