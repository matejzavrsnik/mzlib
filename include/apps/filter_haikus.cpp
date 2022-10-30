//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "filter_haikus.h"

class fixture_filter_haikus : public ::testing::Test 
{

protected:

   fixture_filter_haikus () :
      m_syllables(
         mzlib::syllables::from_collection(
            dictionary.begin(), dictionary.end(), '|')
      )
   {}
   
   virtual ~fixture_filter_haikus () {}
   virtual void SetUp () {}
   virtual void TearDown () {}

   std::vector<std::string> dictionary = {
      "all", "she", "did", "was", "a|po|lo|gise", "and", "say", "thank", 
      "you", "then", "the", "call", "dis|conn|ect|ed", "told"};
   
   mzlib::syllables m_syllables;
};

TEST_F(fixture_filter_haikus, finds_haiku_in_stream) 
{
      std::stringstream source(
         "all she did was apologise and say thank you, "
         "and the call was disconnected,\" Ms Montgomery "
         "told El Nuevo Herald.");
      
      std::stringstream target;
      mzlib::filter_haikus(source, target, m_syllables);
      
      std::string expected = 
         "was apologise\n"
         "and say thank you, and the call\n"
         "was disconnected,\"\n\n";
      
      ASSERT_EQ(expected, target.str());
}

TEST_F(fixture_filter_haikus, doesnt_repeat_if_same_seen_again) 
{
      std::stringstream source(
         "all she did was apologise and say thank you, "
         "and the call was disconnected,\" Ms Montgomery "
         "told El Nuevo Herald."
         "all she did was apologise and say thank you, "
         "and the call was disconnected,\" Ms Montgomery "
         "told El Nuevo Herald.");
      
      std::stringstream target;
      mzlib::filter_haikus(source, target, m_syllables);
      
      std::string expected = 
         "was apologise\n"
         "and say thank you, and the call\n"
         "was disconnected,\"\n\n";
      
      ASSERT_EQ(expected, target.str());
}