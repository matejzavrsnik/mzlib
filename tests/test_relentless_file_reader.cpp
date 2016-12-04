//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/relentless_file_reader.h"
#include "gtest/gtest.h"

#include "../options.h"

class fixture_relentless_file_reader : public ::testing::Test 
{

protected:

   fixture_relentless_file_reader() 
   {
      m_test_dir = g_arguments["mzlib_testdir"] + "/filesystem";
   }
   virtual ~fixture_relentless_file_reader() {}
   
   virtual void SetUp() 
   {
      m_test_file = m_test_dir + "/temp_file";
      std::string sample_content = "I must not fear.";
      mzlib::save_file (m_test_file, sample_content);
   }
   virtual void TearDown() 
   {
      std::remove (m_test_file.c_str());
   }
   
   std::string m_test_dir;
   std::string m_test_file;
};

TEST_F(fixture_relentless_file_reader, basic_test)
{
   std::string file;
   std::string content;
   
   mzlib::relentless_file_reader reader(m_test_file);
   
   reader.callback = 
      [] (const std::string&, const std::string&) {
         FAIL(); // should not be called next
      };
   reader.anything_new_what_about_now();
   
   std::string additional_content = "Fear is the mind-killer.";
   mzlib::append_file (m_test_file, additional_content);
   reader.callback = 
      [this] (const std::string& addition, const std::string& file) {
         ASSERT_EQ("Fear is the mind-killer.", addition);
         ASSERT_EQ(m_test_file, file);
      };
   reader.anything_new_what_about_now();
   
   reader.callback = 
      [] (const std::string&, const std::string&) {
         FAIL(); // should not be called next
      };
   reader.anything_new_what_about_now();
}
