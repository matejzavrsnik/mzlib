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