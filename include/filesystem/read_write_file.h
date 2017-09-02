//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_READ_WRITE_FILE_H
#define MZLIB_READ_WRITE_FILE_H

#include <string>

namespace mzlib {

// Read file contents and return it in a string
inline std::string read_file (const std::string& filename) 
{
   std::ifstream filestream(filename);
   std::stringstream buffer;
   buffer << filestream.rdbuf();
   return buffer.str();
}

inline std::string read_file (
   const std::string&   filename, 
   const std::streampos read_from, 
   const std::streampos read_to)
{
   if (read_to <= read_from) return std::string();
   std::ifstream filestream(filename);
   filestream.seekg (read_from);
   const unsigned int chars_to_read = read_to - read_from;
   std::vector<char> vec_content(chars_to_read);
   filestream.read(&vec_content[0], chars_to_read);
   std::string str_content(vec_content.begin(), vec_content.end());
   return str_content;
}

// Save string contents into a file
inline void save_file (const std::string& filename, const std::string& content)
{
   std::ofstream out(filename);
   out << content;
   out.close();
}

// Append string contents to a file
inline void append_file (const std::string& filename, const std::string& content)
{
   std::ofstream out(filename, std::ios::app);
   out << content;
   out.close();
}

} // namespace

#endif // MZLIB_READ_WRITE_FILE_H

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_READ_WRITE_FILE_TESTS_H
#define MZLIB_READ_WRITE_FILE_TESTS_H

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


#endif // MZLIB_READ_WRITE_FILE_TESTS_H

#endif // MZLIB_BUILDING_TESTS

