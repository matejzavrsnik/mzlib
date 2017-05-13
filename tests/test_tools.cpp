//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include <map>
#include <list>

#include "../include/tools/general.h"
#include "../include/lang/c64_basic_for.h"

#include "gtest/gtest.h"
    
TEST(get_number_of_decimals, basic) 
{
   double double_num = 0;
   ASSERT_EQ(0, mzlib::get_number_of_decimals(double_num));
   double_num = 1;
   ASSERT_EQ(0, mzlib::get_number_of_decimals(double_num));
   double_num = 0.111;
   ASSERT_EQ(3, mzlib::get_number_of_decimals(double_num));
   double_num = 0.11100;
   ASSERT_EQ(3, mzlib::get_number_of_decimals(double_num));
   double_num = 0.111001;
   ASSERT_EQ(6, mzlib::get_number_of_decimals(double_num));
}

TEST(push_back_if_not_in_different_vectors, basic) 
{
   std::vector<std::string> v_string;
   std::vector<int> v_int;
    
   mzlib::push_back_unique(v_string, std::string("test"));
   ASSERT_EQ(1, v_string.size());
    
   mzlib::push_back_unique(v_int, 123);
   ASSERT_EQ(1, v_int.size());
}

TEST(push_back_if_not_in, basic) 
{
   std::vector<int> v;
   ASSERT_EQ(v.size(), 0);
   auto a = mzlib::push_back_unique(v, 11);
   ASSERT_EQ(*a, 11);
   ASSERT_EQ(v.size(), 1);
   auto b = mzlib::push_back_unique(v, 11);
   ASSERT_EQ(*b, 11);
   ASSERT_EQ(v.size(), 1);
   auto c = mzlib::push_back_unique(v, 12);
   ASSERT_EQ(*c, 12);
   ASSERT_EQ(v.size(), 2);
   auto d = mzlib::push_back_unique(v, 12);
   ASSERT_EQ(*d, 12);
   ASSERT_EQ(v.size(), 2);    
   auto e = mzlib::push_back_unique(v, 13);
   ASSERT_EQ(*e, 13);
   ASSERT_EQ(v.size(), 3);
   auto f = mzlib::push_back_unique(v, 12);
   ASSERT_EQ(*f, 12);
   ASSERT_EQ(v.size(), 3);
   auto g = mzlib::push_back_unique(v, 11);
   ASSERT_EQ(*g, 11);
   ASSERT_EQ(v.size(), 3);
}

TEST(get_index, basic) 
{
   std::vector<int> v;
   for(int i=0; i<10; i++) {
      v.push_back(i);
   }
   // first 
   auto it_0 = std::find(v.begin(), v.end(), 0);
   int index_0 = mzlib::get_index(v, it_0);
   ASSERT_EQ(index_0, 0);
   // second
   auto it_1 = std::find(v.begin(), v.end(), 1);
   int index_1 = mzlib::get_index(v, it_1);
   ASSERT_EQ(index_1, 1);
   // middle
   auto it_5 = std::find(v.begin(), v.end(), 5);
   int index_5 = mzlib::get_index(v, it_5);
   ASSERT_EQ(index_5, 5);
   // last
   auto it_9 = std::find(v.begin(), v.end(), 9);
   int index_9 = mzlib::get_index(v, it_9);
   ASSERT_EQ(index_9, 9);
}

TEST(create_matrix, basic) 
{
   auto matrix = mzlib::create_matrix(2,3,0);
   
   ASSERT_EQ(2, matrix.size());
   ASSERT_EQ(3, matrix[0].size());
   ASSERT_EQ(3, matrix[1].size());
   
   ASSERT_EQ(0, matrix[0][0]);
   ASSERT_EQ(0, matrix[1][2]);
}

TEST(copy_first_n_over_rest, basic) 
{
   std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};
   
   mzlib::copy_first_n_over_rest(v, 3);
   ASSERT_EQ(1, v[0]); ASSERT_EQ(2, v[1]); ASSERT_EQ(3, v[2]);
   ASSERT_EQ(1, v[3]); ASSERT_EQ(2, v[4]); ASSERT_EQ(3, v[5]);
   ASSERT_EQ(1, v[6]); ASSERT_EQ(2, v[7]); ASSERT_EQ(3, v[8]);
   ASSERT_EQ(1, v[9]);
}

TEST(sentence_assemblarator, basic) 
{
   std::vector<std::string> words = {"veni", ",", "vidi", ",","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = mzlib::sentence_assemblarator([&](){return *(words_iterator++);});
   // starts sentence with uppercase
   // inserts spaces between words, but after commas
   // stops when encounters '.'
   ASSERT_EQ(sentence, "Veni, vidi, dormivi."); 
}

TEST(sentence_assemblarator, stops_on_exclamation_mark) 
{
   std::vector<std::string> words = {"veni", "!", "vidi", ",","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = mzlib::sentence_assemblarator([&](){return *(words_iterator++);});
   ASSERT_EQ(sentence, "Veni!"); 
}

TEST(sentence_assemblarator, stops_on_question_mark) 
{
   std::vector<std::string> words = {"veni", "?", "vidi", ",","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = mzlib::sentence_assemblarator([&](){return *(words_iterator++);});
   ASSERT_EQ(sentence, "Veni?"); 
}

TEST(sentence_assemblarator, spaces_around_quotes) 
{
   std::vector<std::string> words = {"veni", "\"", "vidi", "\"","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = mzlib::sentence_assemblarator([&](){return *(words_iterator++);});
   // insert space before opening quote, but after closing quote
   ASSERT_EQ(sentence, "Veni \"vidi\" dormivi."); 
}

TEST(sentence_assemblarator, spaces_around_paretheses) 
{
   std::vector<std::string> words = {"veni", "(", "vidi", ")","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = mzlib::sentence_assemblarator([&](){return *(words_iterator++);});
   // insert space before opening parentheses, but after closing parentheses
   ASSERT_EQ(sentence, "Veni (vidi) dormivi."); 
}

TEST(sentence_assemblarator, quote_handling) 
{
   std::vector<std::string> words = {"veni", "\"", "\"", "vidi","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = mzlib::sentence_assemblarator([&](){return *(words_iterator++);});
   // will reject second quote in the row, but will close the quote before sentence ends
   ASSERT_EQ(sentence, "Veni \"vidi dormivi\"."); 
}

TEST(sentence_assemblarator, paretheses_handling) 
{
   std::vector<std::string> words = {"veni", "(", "(", "vidi","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = mzlib::sentence_assemblarator([&](){return *(words_iterator++);});
   // will reject second opening paretheses in the row, but will close it before sentence ends
   ASSERT_EQ(sentence, "Veni (vidi dormivi)."); 
}

TEST(fast_threeway_min_lvalue, basic) 
{
   int i1 = 1, i2 = 2, i3 = 3;
   // all permutations
   ASSERT_EQ(1, mzlib::fast_min_ref(i1, i2, i3));
   ASSERT_EQ(1, mzlib::fast_min_ref(i1, i3, i2));
   ASSERT_EQ(1, mzlib::fast_min_ref(i2, i1, i3));
   ASSERT_EQ(1, mzlib::fast_min_ref(i2, i3, i1));
   ASSERT_EQ(1, mzlib::fast_min_ref(i3, i1, i2));
   ASSERT_EQ(1, mzlib::fast_min_ref(i3, i2, i1));
}

TEST(fast_threeway_min_rvalue, basic) 
{
   // all permutations
   ASSERT_EQ(1, mzlib::fast_min(1, 2, 3));
   ASSERT_EQ(1, mzlib::fast_min(1, 3, 2));
   ASSERT_EQ(1, mzlib::fast_min(2, 1, 3));
   ASSERT_EQ(1, mzlib::fast_min(2, 3, 1));
   ASSERT_EQ(1, mzlib::fast_min(3, 1, 2));
   ASSERT_EQ(1, mzlib::fast_min(3, 2, 1));
}

TEST(coptional, basic) 
{
   mzlib::optional<int> optional;
   ASSERT_THROW(optional.get(), mzlib::exception::not_set);
   ASSERT_FALSE(optional.is_set());
   optional = 5;
   ASSERT_NO_THROW(optional.get());
   ASSERT_EQ(5, optional.get());
   ASSERT_TRUE(optional.is_set()); 
   optional.unset();
   ASSERT_THROW(optional.get(), mzlib::exception::not_set);
}

TEST(c64_basic_for, basic) 
{
   int should_be = 0;
   int use_step = 10;
   using c64_for = mzlib::c64_basic_for<int>;
   for(int is : c64_for::loop()->from(0)->to(1000)->step(use_step))
   {
      ASSERT_EQ(should_be, is);
      should_be += use_step;
   }
}

TEST(add_to_tally, basic) 
{
   std::map<std::string, int> map;
   
   mzlib::add_to_tally(map, std::string("word"));
   ASSERT_EQ(1, map["word"]);
   
   mzlib::add_to_tally(map, std::string("word"));
   ASSERT_EQ(2, map["word"]);
   
   mzlib::add_to_tally(map, std::string("another word"));
   ASSERT_EQ(2, map["word"]);
   ASSERT_EQ(1, map["another word"]);
}

TEST(sort_map_by_value, ascending) 
{
   std::map<int, std::string> map;
   map[1] = "ddd";
   map[2] = "ccc";
   map[3] = "bbb";
   map[4] = "aaa";
   
   // If map was iterated here, it would come out sorted by key.
   // We need it sorted by values instead;
   
   std::vector<std::pair<int, std::string>> sorted = 
      mzlib::sort_map_by_value(map, mzlib::option::descending::no);
   
   ASSERT_EQ("aaa", sorted[0].second);
   ASSERT_EQ("bbb", sorted[1].second);
   ASSERT_EQ("ccc", sorted[2].second);
   ASSERT_EQ("ddd", sorted[3].second);
}

TEST(sort_map_by_value, descending) 
{
   std::map<int, std::string> map;
   map[1] = "ddd";
   map[2] = "ccc";
   map[3] = "bbb";
   map[4] = "aaa";
   
   // If map was iterated here, it would come out sorted by key.
   // We need it sorted by values instead;
   
   std::vector<std::pair<int, std::string>> sorted = 
      mzlib::sort_map_by_value(map, mzlib::option::descending::yes);
   
   ASSERT_EQ("ddd", sorted[0].second);
   ASSERT_EQ("ccc", sorted[1].second);
   ASSERT_EQ("bbb", sorted[2].second);
   ASSERT_EQ("aaa", sorted[3].second);
}

TEST(get_index_from_coordinates, basic)
{
   ASSERT_EQ(0, mzlib::get_index_from_coordinates({0,0}, 3));
   ASSERT_EQ(1, mzlib::get_index_from_coordinates({1,0}, 3));
   ASSERT_EQ(2, mzlib::get_index_from_coordinates({2,0}, 3));
   ASSERT_EQ(3, mzlib::get_index_from_coordinates({0,1}, 3));
   
   ASSERT_EQ(4, mzlib::get_index_from_coordinates({0,1}, 4));
   ASSERT_EQ(5, mzlib::get_index_from_coordinates({0,1}, 5));
   
   ASSERT_EQ(24, mzlib::get_index_from_coordinates({4,4}, 5));
}

TEST(get_coordinates_from_index, basic)
{
   using coor = mzlib::vector<uint,2>;
   ASSERT_EQ(coor({0,0}), mzlib::get_coordinates_from_index(0,3));
   ASSERT_EQ(coor({1,0}), mzlib::get_coordinates_from_index(1,3));
   ASSERT_EQ(coor({2,0}), mzlib::get_coordinates_from_index(2,3));
   ASSERT_EQ(coor({0,1}), mzlib::get_coordinates_from_index(3,3));

   ASSERT_EQ(coor({0,1}), mzlib::get_coordinates_from_index(4, 4));
   ASSERT_EQ(coor({0,1}), mzlib::get_coordinates_from_index(5, 5));
   
   ASSERT_EQ(coor({4,4}), mzlib::get_coordinates_from_index(24, 5));
}

TEST(circular_next, vector)
{
   std::vector<int> v{1,2,3};
   auto it = v.begin();
   
   ASSERT_EQ(1, *it);
   mzlib::circular_next(it, v.begin(), v.end());
   ASSERT_EQ(2, *it);
   mzlib::circular_next(it, v.begin(), v.end());
   ASSERT_EQ(3, *it);
   mzlib::circular_next(it, v.begin(), v.end());
   ASSERT_EQ(1, *it);
   mzlib::circular_next(it, v.begin(), v.end());
   ASSERT_EQ(2, *it);
   mzlib::circular_next(it, v.begin(), v.end());
   ASSERT_EQ(3, *it);
   mzlib::circular_next(it, v.begin(), v.end());
   ASSERT_EQ(1, *it);
}

TEST(circular_next, vector_section)
{
   std::vector<int> v{1,2,3,4,5};
   auto it = v.begin();
   auto begin = v.begin()+1;
   auto end = v.begin()+3;
   
   ASSERT_EQ(1, *it);
   mzlib::circular_next(it, begin, end);
   ASSERT_EQ(2, *it);
   mzlib::circular_next(it, begin, end);
   ASSERT_EQ(3, *it);
   mzlib::circular_next(it, begin, end);
   ASSERT_EQ(2, *it);
   mzlib::circular_next(it, begin, end);
   ASSERT_EQ(3, *it);
   mzlib::circular_next(it, begin, end);
   ASSERT_EQ(2, *it);
}

TEST(circular_next, list)
{
   std::list<int> l{1,2,3};
   auto it = l.begin();
   
   ASSERT_EQ(1, *it);
   mzlib::circular_next(it, l.begin(), l.end());
   ASSERT_EQ(2, *it);
   mzlib::circular_next(it, l.begin(), l.end());
   ASSERT_EQ(3, *it);
   mzlib::circular_next(it, l.begin(), l.end());
   ASSERT_EQ(1, *it);
   mzlib::circular_next(it, l.begin(), l.end());
   ASSERT_EQ(2, *it);
   mzlib::circular_next(it, l.begin(), l.end());
   ASSERT_EQ(3, *it);
   mzlib::circular_next(it, l.begin(), l.end());
   ASSERT_EQ(1, *it);
}

TEST(average, basic)
{
   std::vector<int> v{1,2,3,4,5};
   ASSERT_EQ(3.0, mzlib::average(v.begin(),   v.end()));
   ASSERT_EQ(3.5, mzlib::average(v.begin()+1, v.end()));
   ASSERT_EQ(2.5, mzlib::average(v.begin(),   v.end()-1));
}

TEST(is_distance_larger, basic)
{
   std::vector<int> v = {1,2,3,4,5};
   
   ASSERT_FALSE(mzlib::is_distance_larger(v.begin(), v.begin(), 2));
   ASSERT_FALSE(mzlib::is_distance_larger(v.begin(), v.begin()+1, 2));
   ASSERT_FALSE(mzlib::is_distance_larger(v.begin(), v.begin()+2, 2));
   ASSERT_TRUE (mzlib::is_distance_larger(v.begin(), v.begin()+3, 2));
}

TEST(is_distance_smaller, basic)
{
   std::vector<int> v = {1,2,3,4,5};
   
   ASSERT_TRUE (mzlib::is_distance_smaller(v.begin(), v.begin(), 2));
   ASSERT_TRUE (mzlib::is_distance_smaller(v.begin(), v.begin()+1, 2));
   ASSERT_FALSE(mzlib::is_distance_smaller(v.begin(), v.begin()+2, 2));
   ASSERT_FALSE(mzlib::is_distance_smaller(v.begin(), v.begin()+3, 2));
}

TEST(is_distance_equal, basic)
{
   std::vector<int> v = {1,2,3,4,5};
   
   ASSERT_FALSE(mzlib::is_distance_equal(v.begin(), v.begin(), 2));
   ASSERT_FALSE(mzlib::is_distance_equal(v.begin(), v.begin()+1, 2));
   ASSERT_TRUE (mzlib::is_distance_equal(v.begin(), v.begin()+2, 2));
   ASSERT_FALSE(mzlib::is_distance_equal(v.begin(), v.begin()+3, 2));
}

TEST(next_lex_permutation, basic)
{
   std::vector<int> v = {1,2,3,4,5};
   
   mzlib::next_lex_permutation(v.begin(), v.end());
   ASSERT_EQ(v, std::vector<int>({1,2,3,5,4}));
   mzlib::next_lex_permutation(v.begin(), v.end());
   ASSERT_EQ(v, std::vector<int>({1,2,4,3,5}));
   mzlib::next_lex_permutation(v.begin(), v.end());
   ASSERT_EQ(v, std::vector<int>({1,2,4,5,3}));
   mzlib::next_lex_permutation(v.begin(), v.end());
   ASSERT_EQ(v, std::vector<int>({1,2,5,3,4}));
   mzlib::next_lex_permutation(v.begin(), v.end());
   ASSERT_EQ(v, std::vector<int>({1,2,5,4,3}));
}

TEST(next_lex_permutation, empty)
{
   std::vector<int> v = {};
   
   mzlib::next_lex_permutation(v.begin(), v.end());
   ASSERT_EQ(v, std::vector<int>({}));
}

TEST(next_lex_permutation, one)
{
   std::vector<int> v = {1};
   
   mzlib::next_lex_permutation(v.begin(), v.end());
   ASSERT_EQ(v, std::vector<int>({1}));
}

TEST(next_lex_permutation, two)
{
   std::vector<int> v = {1,2};
   
   mzlib::next_lex_permutation(v.begin(), v.end());
   ASSERT_EQ(v, std::vector<int>({2,1}));
}

TEST(next_lex_permutation, end)
{
   std::vector<int> v = {2,1};
   
   mzlib::next_lex_permutation(v.begin(), v.end());
   ASSERT_EQ(v, std::vector<int>({2,1}));
}

TEST(find_last_where_value_larger_then_given, basic)
{
   std::vector<int> v = {1,2,3,4,5};
   
   auto res = mzlib::find_last_where_value_larger_then_given(v.begin(), v.end(), 3);
   ASSERT_EQ(*res, 5);
}

TEST(find_last_where_value_larger_then_given, empty)
{
   std::vector<int> v = {};
   
   auto res = mzlib::find_last_where_value_larger_then_given(v.begin(), v.end(), 3);
   ASSERT_EQ(res, v.end());
}

TEST(find_last_where_value_larger_then_given, one_is_larger)
{
   std::vector<int> v = {5};
   
   auto res = mzlib::find_last_where_value_larger_then_given(v.begin(), v.end(), 3);
   ASSERT_EQ(*res, 5);
}

TEST(find_last_where_value_larger_then_given, one_is_smaller)
{
   std::vector<int> v = {2};
   
   auto res = mzlib::find_last_where_value_larger_then_given(v.begin(), v.end(), 3);
   ASSERT_EQ(res, v.end());
}

TEST(find_last_where_value_smaller_then_next, basic)
{
   std::vector<int> v = {1,4,6,1,2,3};
   // Smaller then nexts ^ ^   ^ ^ 
   
   auto res = mzlib::find_last_where_value_smaller_then_next(v.begin(), v.end());
   ASSERT_EQ(*res, 2);
}

TEST(find_last_where_value_smaller_then_next, empty)
{
   std::vector<int> v = {};
   
   auto res = mzlib::find_last_where_value_smaller_then_next(v.begin(), v.end());
   ASSERT_EQ(res, v.end());
}

TEST(find_last_where_value_smaller_then_next, one)
{
   std::vector<int> v = {1};
   
   auto res = mzlib::find_last_where_value_smaller_then_next(v.begin(), v.end());
   ASSERT_EQ(res, v.end());
}

TEST(find_last_where_value_smaller_then_next, two_equals)
{
   std::vector<int> v = {1,1};
   
   auto res = mzlib::find_last_where_value_smaller_then_next(v.begin(), v.end());
   ASSERT_EQ(res, v.end());
}

TEST(find_last_where_value_smaller_then_next, two)
{
   std::vector<int> v = {1,2};
   
   auto res = mzlib::find_last_where_value_smaller_then_next(v.begin(), v.end());
   ASSERT_EQ(*res, 1);
}