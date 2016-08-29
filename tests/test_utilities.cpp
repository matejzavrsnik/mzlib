//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include <map>

#include "../include/utilities.h"
#include "gtest/gtest.h"
    
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
   ASSERT_EQ(0, mzlib::util::get_number_of_decimals(double_num));
   double_num = 1;
   ASSERT_EQ(0, mzlib::util::get_number_of_decimals(double_num));
   double_num = 0.111;
   ASSERT_EQ(3, mzlib::util::get_number_of_decimals(double_num));
   double_num = 0.11100;
   ASSERT_EQ(3, mzlib::util::get_number_of_decimals(double_num));
   double_num = 0.111001;
   ASSERT_EQ(6, mzlib::util::get_number_of_decimals(double_num));
}

TEST_F(fixture_utilities, push_back_if_not_in_different_vectors) 
{
   std::vector<std::string> v_string;
   std::vector<int> v_int;
    
   mzlib::util::push_back_unique(v_string, std::string("test"));
   ASSERT_EQ(1, v_string.size());
    
   mzlib::util::push_back_unique(v_int, 123);
   ASSERT_EQ(1, v_int.size());
}

TEST_F(fixture_utilities, push_back_if_not_in) 
{
   std::vector<int> v;
   ASSERT_EQ(v.size(), 0);
   auto a = mzlib::util::push_back_unique(v, 11);
   ASSERT_EQ(*a, 11);
   ASSERT_EQ(v.size(), 1);
   auto b = mzlib::util::push_back_unique(v, 11);
   ASSERT_EQ(*b, 11);
   ASSERT_EQ(v.size(), 1);
   auto c = mzlib::util::push_back_unique(v, 12);
   ASSERT_EQ(*c, 12);
   ASSERT_EQ(v.size(), 2);
   auto d = mzlib::util::push_back_unique(v, 12);
   ASSERT_EQ(*d, 12);
   ASSERT_EQ(v.size(), 2);    
   auto e = mzlib::util::push_back_unique(v, 13);
   ASSERT_EQ(*e, 13);
   ASSERT_EQ(v.size(), 3);
   auto f = mzlib::util::push_back_unique(v, 12);
   ASSERT_EQ(*f, 12);
   ASSERT_EQ(v.size(), 3);
   auto g = mzlib::util::push_back_unique(v, 11);
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
   int index_0 = mzlib::util::get_index(v, it_0);
   ASSERT_EQ(index_0, 0);
   // second
   auto it_1 = std::find(v.begin(), v.end(), 1);
   int index_1 = mzlib::util::get_index(v, it_1);
   ASSERT_EQ(index_1, 1);
   // middle
   auto it_5 = std::find(v.begin(), v.end(), 5);
   int index_5 = mzlib::util::get_index(v, it_5);
   ASSERT_EQ(index_5, 5);
   // last
   auto it_9 = std::find(v.begin(), v.end(), 9);
   int index_9 = mzlib::util::get_index(v, it_9);
   ASSERT_EQ(index_9, 9);
}

TEST_F(fixture_utilities, create_matrix_basic) 
{
   auto matrix = mzlib::util::create_matrix(2,3,0);
   
   ASSERT_EQ(2, matrix.size());
   ASSERT_EQ(3, matrix[0].size());
   ASSERT_EQ(3, matrix[1].size());
   
   ASSERT_EQ(0, matrix[0][0]);
   ASSERT_EQ(0, matrix[1][2]);
}

TEST_F(fixture_utilities, copy_first_n_over_rest_basic) 
{
   std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};
   
   mzlib::util::copy_first_n_over_rest(v, 3);
   ASSERT_EQ(1, v[0]); ASSERT_EQ(2, v[1]); ASSERT_EQ(3, v[2]);
   ASSERT_EQ(1, v[3]); ASSERT_EQ(2, v[4]); ASSERT_EQ(3, v[5]);
   ASSERT_EQ(1, v[6]); ASSERT_EQ(2, v[7]); ASSERT_EQ(3, v[8]);
   ASSERT_EQ(1, v[9]);
}

TEST_F(fixture_utilities, sentence_assemblarator_basic_test) 
{
   std::vector<std::string> words = {"veni", ",", "vidi", ",","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = mzlib::util::sentence_assemblarator([&](){return *(words_iterator++);});
   // starts sentence with uppercase
   // inserts spaces between words, but after commas
   // stops when encounters '.'
   ASSERT_EQ(sentence, "Veni, vidi, dormivi."); 
}

TEST_F(fixture_utilities, sentence_assemblarator_stops_on_exclamation_mark) 
{
   std::vector<std::string> words = {"veni", "!", "vidi", ",","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = mzlib::util::sentence_assemblarator([&](){return *(words_iterator++);});
   ASSERT_EQ(sentence, "Veni!"); 
}

TEST_F(fixture_utilities, sentence_assemblarator_stops_on_question_mark) 
{
   std::vector<std::string> words = {"veni", "?", "vidi", ",","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = mzlib::util::sentence_assemblarator([&](){return *(words_iterator++);});
   ASSERT_EQ(sentence, "Veni?"); 
}

TEST_F(fixture_utilities, sentence_assemblarator_spaces_around_quotes) 
{
   std::vector<std::string> words = {"veni", "\"", "vidi", "\"","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = mzlib::util::sentence_assemblarator([&](){return *(words_iterator++);});
   // insert space before opening quote, but after closing quote
   ASSERT_EQ(sentence, "Veni \"vidi\" dormivi."); 
}

TEST_F(fixture_utilities, sentence_assemblarator_spaces_around_paretheses) 
{
   std::vector<std::string> words = {"veni", "(", "vidi", ")","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = mzlib::util::sentence_assemblarator([&](){return *(words_iterator++);});
   // insert space before opening parentheses, but after closing parentheses
   ASSERT_EQ(sentence, "Veni (vidi) dormivi."); 
}

TEST_F(fixture_utilities, sentence_assemblarator_quote_handling) 
{
   std::vector<std::string> words = {"veni", "\"", "\"", "vidi","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = mzlib::util::sentence_assemblarator([&](){return *(words_iterator++);});
   // will reject second quote in the row, but will close the quote before sentence ends
   ASSERT_EQ(sentence, "Veni \"vidi dormivi\"."); 
}

TEST_F(fixture_utilities, sentence_assemblarator_paretheses_handling) 
{
   std::vector<std::string> words = {"veni", "(", "(", "vidi","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = mzlib::util::sentence_assemblarator([&](){return *(words_iterator++);});
   // will reject second opening paretheses in the row, but will close it before sentence ends
   ASSERT_EQ(sentence, "Veni (vidi dormivi)."); 
}

TEST_F(fixture_utilities, fast_threeway_min_lvalue) 
{
   int i1 = 1, i2 = 2, i3 = 3;
   // all permutations
   ASSERT_EQ(1, mzlib::util::fast_min_ref(i1, i2, i3));
   ASSERT_EQ(1, mzlib::util::fast_min_ref(i1, i3, i2));
   ASSERT_EQ(1, mzlib::util::fast_min_ref(i2, i1, i3));
   ASSERT_EQ(1, mzlib::util::fast_min_ref(i2, i3, i1));
   ASSERT_EQ(1, mzlib::util::fast_min_ref(i3, i1, i2));
   ASSERT_EQ(1, mzlib::util::fast_min_ref(i3, i2, i1));
}

TEST_F(fixture_utilities, fast_threeway_min_rvalue) 
{
   // all permutations
   ASSERT_EQ(1, mzlib::util::fast_min(1, 2, 3));
   ASSERT_EQ(1, mzlib::util::fast_min(1, 3, 2));
   ASSERT_EQ(1, mzlib::util::fast_min(2, 1, 3));
   ASSERT_EQ(1, mzlib::util::fast_min(2, 3, 1));
   ASSERT_EQ(1, mzlib::util::fast_min(3, 1, 2));
   ASSERT_EQ(1, mzlib::util::fast_min(3, 2, 1));
}

TEST_F(fixture_utilities, coptional_basic) 
{
   mzlib::util::coptional<int> optional;
   ASSERT_THROW(optional.get(), mzlib::exception::not_set);
   ASSERT_FALSE(optional.is_set());
   optional.set(5);
   ASSERT_NO_THROW(optional.get());
   ASSERT_EQ(5, optional.get());
   ASSERT_TRUE(optional.is_set()); 
}

TEST_F(fixture_utilities, cbasic_style_for_basic) 
{
   int should_be = 0;
   int use_step = 10;
   for(int is : mzlib::util::cbasic_style_for<int>::
           loop()->from(0)->to(1000)->step(use_step))
   {
      ASSERT_EQ(should_be, is);
      should_be += use_step;
   }
}