//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_IS_META_DIRECTORY_H
#define MZLIB_IS_META_DIRECTORY_H

namespace mzlib {

// is one of those . or .. "meta-directories"?
inline bool is_meta_directory(const char* directory_name)
{
   // to exercise my C muscles a bit
   int len_of_string = (int)strlen (directory_name);
   const char* last_dot_pos = strrchr (directory_name, '.');
   int len_to_last_dot = last_dot_pos - directory_name;
   return len_of_string == (len_to_last_dot + 1);
}

} // namespace

#endif // MZLIB_IS_META_DIRECTORY_H

#ifdef MZLIB_IS_META_DIRECTORY_TESTS_H
#undef MZLIB_IS_META_DIRECTORY_TESTS_H

#include "../../options.h"

class fixture_is_meta_directory : public ::testing::Test 
{

protected:

   fixture_is_meta_directory() 
   {
      if (g_arguments.find(g_test_dir_param) != g_arguments.end()) {
         m_test_dir = g_arguments[g_test_dir_param] + "/filesystem";
         m_should_test_filesystem = true;
      }
   }
   virtual ~fixture_is_meta_directory() {}
   
   virtual void SetUp() {}
   virtual void TearDown() {}
   
   bool m_should_test_filesystem = false;
   std::string m_test_dir;
};


TEST_F(fixture_is_meta_directory, is_meta_directory)
{
   if(m_should_test_filesystem) {
      ASSERT_TRUE (mzlib::is_meta_directory("."));
      ASSERT_TRUE (mzlib::is_meta_directory(".."));
      ASSERT_TRUE (mzlib::is_meta_directory("avengers/."));
      ASSERT_TRUE (mzlib::is_meta_directory("avengers/.."));
      ASSERT_FALSE(mzlib::is_meta_directory("avengers/ironman"));
   }
   else {
      ASSERT_TRUE(true);
   }
}

#endif // MZLIB_IS_META_DIRECTORY_TESTS_H
