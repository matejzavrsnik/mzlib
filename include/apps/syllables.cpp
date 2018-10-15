//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "syllables.h"

#include "gtest/gtest.h"

#include <vector>
#include <string>

class fixture_syllables : public ::testing::Test 
{

protected:

   fixture_syllables () :
      m_syllables(
         mzlib::syllables::from_collection(
            dictionary.begin(), dictionary.end(), '|')
      )
   {}
   
   virtual ~fixture_syllables () {}
   virtual void SetUp () {}
   virtual void TearDown () {}

   std::vector<std::string> dictionary = {
      "no", "ma|ma", "pa|pa", "whi|sky", "so|da"};
   
   mzlib::syllables m_syllables;
};

TEST_F(fixture_syllables, counts_syllables_in_word) 
{
   std::optional<int> count = m_syllables.count("mama");
   ASSERT_TRUE(count.has_value());
   ASSERT_EQ(2, *count);
}

TEST_F(fixture_syllables, counts_syllables_in_monosyllabic_word) 
{
   std::optional<int> count = m_syllables.count("no");
   ASSERT_TRUE(count.has_value());
   ASSERT_EQ(1, *count);
}

TEST_F(fixture_syllables, returns_empty_optional_when_not_found) 
{
   std::optional<int> count = m_syllables.count("empire");
   ASSERT_FALSE(count);
}

TEST_F(fixture_syllables, counts_syllables_if_word_with_punctiation) 
{
   std::optional<int> count = m_syllables.count(" papa,?");
   ASSERT_TRUE(count.has_value());
   ASSERT_EQ(2, *count);
}

TEST_F(fixture_syllables, counts_syllables_if_word_with_capitals) 
{
   std::optional<int> count = m_syllables.count("WhIskY");
   ASSERT_TRUE(count.has_value());
   ASSERT_EQ(2, *count);
}

TEST_F(fixture_syllables, counts_syllables_in_sentence_list) 
{
   std::list<std::string> sentence = {
      "no", "mama", "no", "papa", "no", "whisky", "soda"};
   std::optional<int> count = m_syllables.count(sentence);
   ASSERT_TRUE(count.has_value());
   ASSERT_EQ(11, *count);
}