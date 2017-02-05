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
      if (g_arguments.find(g_test_dir_param) != g_arguments.end()) {
         m_test_dir = g_arguments[g_test_dir_param] + "/filesystem";
         m_should_test_filesystem = true;
      }
   }
   virtual ~fixture_relentless_file_reader() {}
   
   virtual void SetUp() 
   {
      m_test_file1 = m_test_dir + "/temp_file1";
      std::string sample_content = "I must not fear.";
      mzlib::save_file (m_test_file1, sample_content);
      
      m_test_file2 = m_test_dir + "/temp_file2";
      sample_content = "Fear is the little-death that brings total obliteration.";
      mzlib::save_file (m_test_file2, sample_content);
   }
   virtual void TearDown() 
   {
      std::remove (m_test_file1.c_str());
      std::remove (m_test_file2.c_str());
   }
   
   bool m_should_test_filesystem = false;
   std::string m_test_dir;
   std::string m_test_file1;
   std::string m_test_file2;
};

TEST_F(fixture_relentless_file_reader, basic_test)
{
   if (m_should_test_filesystem) {
      std::string file;
      std::string content;
      bool was_called;

      mzlib::relentless_file_reader reader(m_test_file1);

      was_called = false;
      reader.set_callback( 
         [&was_called] (const std::string&, const std::string&) {
            was_called = true;
         });
      reader.anything_new_what_about_now();
      ASSERT_FALSE(was_called); // should not be called

      std::string additional_content = "Fear is the mind-killer.";
      mzlib::append_file (m_test_file1, additional_content);
      reader.set_callback( 
         [&content, &file] (const std::string& c, const std::string& f) {
            content = c;
            file = f;
         });
      reader.anything_new_what_about_now();
      ASSERT_EQ("Fear is the mind-killer.", content);
      ASSERT_EQ(m_test_file1, file);

      was_called = false;   
      reader.set_callback( 
         [&was_called] (const std::string&, const std::string&) {
            was_called = true;
         });
      reader.anything_new_what_about_now();
      ASSERT_FALSE(was_called); // should not be called
   }
   else {
      ASSERT_TRUE(true);
   }
}

TEST_F(fixture_relentless_file_reader, aggregated_file_monitor_basic_test)
{
   if (m_should_test_filesystem) {
      std::vector<std::string> files;
      files.push_back(m_test_file1);
      files.push_back(m_test_file2);

      struct treturns {
         std::string file;
         std::string content;
      };
      std::vector<treturns> returns;
      bool was_called;

      mzlib::aggregated_file_monitor monitor(files, nullptr);

      was_called = false;
      monitor.set_callback( 
         [&was_called] (const std::string&, const std::string&) {
            was_called = true;
         });
      monitor.inspect_all();
      ASSERT_FALSE(was_called); // should not be called

      std::string additional_content = "Fear is the mind-killer.";
      mzlib::append_file (m_test_file1, additional_content);
      additional_content = "I will face my fear.";
      mzlib::append_file (m_test_file2, additional_content);
      monitor.set_callback( 
         [&returns] (const std::string& c, const std::string& f) {
            returns.push_back(treturns{f,c});
         });
      monitor.inspect_all();
      ASSERT_EQ(2, returns.size());
      ASSERT_EQ(m_test_file1, returns[0].file);
      ASSERT_EQ("Fear is the mind-killer.", returns[0].content);
      ASSERT_EQ(m_test_file2, returns[1].file);
      ASSERT_EQ("I will face my fear.", returns[1].content);

      was_called = false;   
      monitor.set_callback( 
         [&was_called] (const std::string&, const std::string&) {
            was_called = true;
         });
      monitor.inspect_all();
      ASSERT_FALSE(was_called); // should not be called
   }
   else {
      ASSERT_TRUE(true);
   }
}