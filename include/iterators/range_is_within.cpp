//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "range_is_within.h"
#include "range.h"
#include "find.h"

#include "gtest/gtest.h"

#include <string>

class range_is_within : public ::testing::Test 
{

protected:

   std::string alphabet = "abcdefghi";
   std::string::const_iterator a,b,c,d,e,f,g,h;
   
   range_is_within () 
   {
      a = mzlib::find(alphabet, 'a');
      b = mzlib::find(alphabet, 'b');
      c = mzlib::find(alphabet, 'c');
      d = mzlib::find(alphabet, 'd');
      e = mzlib::find(alphabet, 'e');
      f = mzlib::find(alphabet, 'f');
      g = mzlib::find(alphabet, 'g');
      h = mzlib::find(alphabet, 'h');
   }
   
   virtual ~range_is_within () {}
   virtual void SetUp () {}
   virtual void TearDown () {}
};

TEST_F(range_is_within, set_find_overlaps_before)
{
   mzlib::range first(f, h);
   mzlib::range second(b, d);
   ASSERT_FALSE(mzlib::is_within(first, second));
}

TEST_F(range_is_within, set_find_overlaps_before_touches)
{
   mzlib::range first(e, g);
   mzlib::range second(b, d);
   ASSERT_FALSE(mzlib::is_within(first, second));
}

TEST_F(range_is_within, set_find_overlaps_before_overlaps)
{
   mzlib::range first(e, h);
   mzlib::range second(b, f);
   ASSERT_FALSE(mzlib::is_within(first, second));
}

TEST_F(range_is_within, set_find_overlaps_after)
{
   mzlib::range first(f, h);
   mzlib::range second(b, d);
   ASSERT_FALSE(mzlib::is_within(first, second));
}

TEST_F(range_is_within, set_find_overlaps_after_touches)
{
   mzlib::range first(e, g);
   mzlib::range second(b, d);
   ASSERT_FALSE(mzlib::is_within(first, second));
}

TEST_F(range_is_within, set_find_overlaps_after_overlaps)
{
   mzlib::range first(c, e);
   mzlib::range second(b, d);
   ASSERT_FALSE(mzlib::is_within(first, second));
}

TEST_F(range_is_within, set_find_overlaps_second_is_larger)
{
   mzlib::range first(c, e);
   mzlib::range second(b, f);
   ASSERT_FALSE(mzlib::is_within(first, second));
}

TEST_F(range_is_within, set_find_overlaps_is_in_exactly)
{
   mzlib::range first(b, f);
   mzlib::range second(b, f);
   ASSERT_TRUE(mzlib::is_within(first, second));
}

TEST_F(range_is_within, set_find_overlaps_is_in_where_start_touches)
{
   mzlib::range first(b, g);
   mzlib::range second(b, f);
   ASSERT_TRUE(mzlib::is_within(first, second));
}

TEST_F(range_is_within, set_find_overlaps_is_in_where_end_touches)
{
   mzlib::range first(b, f);
   mzlib::range second(c, f);
   ASSERT_TRUE(mzlib::is_within(first, second));
}

TEST_F(range_is_within, set_find_overlaps_is_in_none_touches)
{
   mzlib::range first(b, f);
   mzlib::range second(c, e);
   ASSERT_TRUE(mzlib::is_within(first, second));
}