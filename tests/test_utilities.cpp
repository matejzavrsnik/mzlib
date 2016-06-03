//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include <map>

#include "../include/utilities.h"
#include "gtest/gtest.h"

using namespace mzlib::util;
    
class fixture_utilities : public ::testing::Test 
{

protected:

   fixture_utilities() {}
   virtual ~fixture_utilities() {}
   virtual void SetUp() {}
   virtual void TearDown() {}
   
};

TEST_F(fixture_utilities, get_number_of_decimals) 
{
   double double_num = 0;
   ASSERT_EQ(0, get_number_of_decimals(double_num));
   double_num = 1;
   ASSERT_EQ(0, get_number_of_decimals(double_num));
   double_num = 0.111;
   ASSERT_EQ(3, get_number_of_decimals(double_num));
   double_num = 0.11100;
   ASSERT_EQ(3, get_number_of_decimals(double_num));
   double_num = 0.111001;
   ASSERT_EQ(6, get_number_of_decimals(double_num));
}

TEST_F(fixture_utilities, push_back_if_not_in_different_vectors) 
{
   std::vector<std::string> v_string;
   std::vector<int> v_int;
    
   push_back_unique(v_string, std::string("test"));
   ASSERT_EQ(1, v_string.size());
    
   push_back_unique(v_int, 123);
   ASSERT_EQ(1, v_int.size());
}

TEST_F(fixture_utilities, push_back_if_not_in) 
{
   std::vector<int> v;
   ASSERT_EQ(v.size(), 0);
   auto a = push_back_unique(v, 11);
   ASSERT_EQ(*a, 11);
   ASSERT_EQ(v.size(), 1);
   auto b = push_back_unique(v, 11);
   ASSERT_EQ(*b, 11);
   ASSERT_EQ(v.size(), 1);
   auto c = push_back_unique(v, 12);
   ASSERT_EQ(*c, 12);
   ASSERT_EQ(v.size(), 2);
   auto d = push_back_unique(v, 12);
   ASSERT_EQ(*d, 12);
   ASSERT_EQ(v.size(), 2);    
   auto e = push_back_unique(v, 13);
   ASSERT_EQ(*e, 13);
   ASSERT_EQ(v.size(), 3);
   auto f = push_back_unique(v, 12);
   ASSERT_EQ(*f, 12);
   ASSERT_EQ(v.size(), 3);
   auto g = push_back_unique(v, 11);
   ASSERT_EQ(*g, 11);
   ASSERT_EQ(v.size(), 3);
}

TEST_F(fixture_utilities, get_index) 
{
   std::vector<int> v;
   for(int i=0; i<10; i++) {
      v.push_back(i);
   }
   // first 
   auto it_0 = std::find(v.begin(), v.end(), 0);
   int index_0 = get_index(v, it_0);
   ASSERT_EQ(index_0, 0);
   // second
   auto it_1 = std::find(v.begin(), v.end(), 1);
   int index_1 = get_index(v, it_1);
   ASSERT_EQ(index_1, 1);
   // middle
   auto it_5 = std::find(v.begin(), v.end(), 5);
   int index_5 = get_index(v, it_5);
   ASSERT_EQ(index_5, 5);
   // last
   auto it_9 = std::find(v.begin(), v.end(), 9);
   int index_9 = get_index(v, it_9);
   ASSERT_EQ(index_9, 9);
}

TEST_F(fixture_utilities, sentence_assemblarator_basic_test) 
{
   std::vector<std::string> words = {"veni", ",", "vidi", ",","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = sentence_assemblarator([&](){return *(words_iterator++);});
   // starts sentence with uppercase
   // inserts spaces between words, but after commas
   // stops when encounters '.'
   ASSERT_EQ(sentence, "Veni, vidi, dormivi."); 
}

TEST_F(fixture_utilities, sentence_assemblarator_stops_on_exclamation_mark) 
{
   std::vector<std::string> words = {"veni", "!", "vidi", ",","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = sentence_assemblarator([&](){return *(words_iterator++);});
   ASSERT_EQ(sentence, "Veni!"); 
}

TEST_F(fixture_utilities, sentence_assemblarator_stops_on_question_mark) 
{
   std::vector<std::string> words = {"veni", "?", "vidi", ",","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = sentence_assemblarator([&](){return *(words_iterator++);});
   ASSERT_EQ(sentence, "Veni?"); 
}

TEST_F(fixture_utilities, sentence_assemblarator_spaces_around_quotes) 
{
   std::vector<std::string> words = {"veni", "\"", "vidi", "\"","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = sentence_assemblarator([&](){return *(words_iterator++);});
   // insert space before opening quote, but after closing quote
   ASSERT_EQ(sentence, "Veni \"vidi\" dormivi."); 
}

TEST_F(fixture_utilities, sentence_assemblarator_spaces_around_paretheses) 
{
   std::vector<std::string> words = {"veni", "(", "vidi", ")","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = sentence_assemblarator([&](){return *(words_iterator++);});
   // insert space before opening parentheses, but after closing parentheses
   ASSERT_EQ(sentence, "Veni (vidi) dormivi."); 
}

TEST_F(fixture_utilities, sentence_assemblarator_quote_handling) 
{
   std::vector<std::string> words = {"veni", "\"", "\"", "vidi","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = sentence_assemblarator([&](){return *(words_iterator++);});
   // will reject second quote in the row, but will close the quote before sentence ends
   ASSERT_EQ(sentence, "Veni \"vidi dormivi\"."); 
}

TEST_F(fixture_utilities, sentence_assemblarator_paretheses_handling) 
{
   std::vector<std::string> words = {"veni", "(", "(", "vidi","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = sentence_assemblarator([&](){return *(words_iterator++);});
   // will reject second opening paretheses in the row, but will close it before sentence ends
   ASSERT_EQ(sentence, "Veni (vidi dormivi)."); 
}
