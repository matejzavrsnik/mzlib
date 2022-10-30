//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "find_eof_position.h"

#include "../../options.h"
#include "read_write_file.h"

class fixture_find_eof_position : public ::testing::Test 
{

protected:

   fixture_find_eof_position() 
   {
      if (g_arguments.find(g_test_dir_param) != g_arguments.end()) {
         m_test_dir = g_arguments[g_test_dir_param] + "/filesystem";
         m_should_test_filesystem = true;
      }
   }
   virtual ~fixture_find_eof_position() {}
   
   virtual void SetUp() {}
   virtual void TearDown() {}
   
   bool m_should_test_filesystem = false;
   std::string m_test_dir;
};

TEST_F(fixture_find_eof_position, find_eof_position)
{
   if(m_should_test_filesystem) {
      std::string temp_file = m_test_dir + "/temp_file";
      std::string sample_content = "I must not fear.";

      mzlib::save_file (temp_file, sample_content);
      std::streampos eof = mzlib::find_eof_position(temp_file);
      ASSERT_EQ(16, eof);

      std::remove (temp_file.c_str());
   }
   else {
      ASSERT_TRUE(true);
   }
}