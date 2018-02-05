//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "read_write_file.h"

#include "../../options.h"

class fixture_read_write_files : public ::testing::Test 
{

protected:

   fixture_read_write_files() 
   {
      if (g_arguments.find(g_test_dir_param) != g_arguments.end()) {
         m_test_dir = g_arguments[g_test_dir_param] + "/filesystem";
         m_should_test_filesystem = true;
      }
   }
   virtual ~fixture_read_write_files() {}
   
   virtual void SetUp() {}
   virtual void TearDown() {}
   
   bool m_should_test_filesystem = false;
   std::string m_test_dir;
};

TEST_F(fixture_read_write_files, write_append_read_file)
{
   if(m_should_test_filesystem) {
      std::string temp_file = m_test_dir + "/temp_file";
      std::string sample_content = "I must not fear.";

      mzlib::save_file (temp_file, sample_content);
      std::string temp_file_content = mzlib::read_file(temp_file);
      ASSERT_EQ(sample_content, temp_file_content);

      std::string additional_content = "Fear is the mind-killer.";
      mzlib::append_file (temp_file, additional_content);
      temp_file_content = mzlib::read_file(temp_file);
      ASSERT_EQ(sample_content + additional_content, temp_file_content);

      std::remove (temp_file.c_str());
   }
   else {
      ASSERT_TRUE(true);
   }
}

TEST_F(fixture_read_write_files, read_file_from_to)
{
   if(m_should_test_filesystem) {
      std::string temp_file = m_test_dir + "/temp_file";
      std::string sample_content = "I must not fear.";

      mzlib::save_file (temp_file, sample_content);
      std::string temp_file_content = mzlib::read_file(temp_file, std::streampos(11), std::streampos(15));
      ASSERT_EQ("fear", temp_file_content);

      std::remove (temp_file.c_str());
   }
   else {
      ASSERT_TRUE(true);
   }
}