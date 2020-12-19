//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "remove_element.h"

#include <vector>

using namespace ::testing;

TEST(remove_element, demo) 
{  
   std::vector<std::unique_ptr<std::string>> collection;
   collection.emplace_back(std::make_unique<std::string>("abcd"));
   collection.emplace_back(std::make_unique<std::string>("efgh"));
   collection.emplace_back(std::make_unique<std::string>("ijkl"));
   
   std::string* abcd = collection[0].get();
   std::string* efgh = collection[1].get();
   std::string* ijkl = collection[2].get();
   
   mzlib::remove_element_ptr(collection, efgh);
   
   ASSERT_EQ(2, collection.size());
   ASSERT_EQ(collection[0].get(), abcd);
   ASSERT_EQ(collection[1].get(), ijkl);
}

