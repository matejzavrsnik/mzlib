//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "rememberator.h"

#include "gtest/gtest.h"

TEST(rememberator, never_seen_cant_remember) 
{
   mzlib::rememberator<std::string> rememberator;
   ASSERT_FALSE(rememberator.can_recall("word"));
}

TEST(rememberator, seen_can_remember) 
{
   mzlib::rememberator<std::string> rememberator;
   rememberator.remember("word");
   ASSERT_TRUE(rememberator.can_recall("word"));
}

TEST(rememberator, never_seen_cant_recall_will_remember) 
{
   mzlib::rememberator<std::string> rememberator;
   ASSERT_FALSE(rememberator.recall_remember("word"));
   ASSERT_TRUE(rememberator.recall_remember("word"));
}

TEST(rememberator, seen_can_count) 
{
   mzlib::rememberator<std::string> rememberator;
   rememberator.remember("word");
   rememberator.remember("another");
   ASSERT_EQ(2, rememberator.count_seen());
}

TEST(rememberator, seen_doesnt_count_twice) 
{
   mzlib::rememberator<std::string> rememberator;
   rememberator.remember("word");
   rememberator.remember("another");
   rememberator.remember("word");
   ASSERT_EQ(2, rememberator.count_seen());
}