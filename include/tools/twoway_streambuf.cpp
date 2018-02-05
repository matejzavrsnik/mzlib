//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "twoway_streambuf.h"

TEST(basic_twoway_streambuf, demo_test_string_in_integer_out) 
{
   mzlib::twoway_streambuf stream_buffer(5000);
   
   std::ostream stream_out(&stream_buffer); // ostream to memory 
   std::istream stream_in(&stream_buffer); // istream from the same memory 

   stream_out << "42"; // send something to ostream
   
   int meaning_of_life_and_universe_and_everything;
   
   stream_in >> meaning_of_life_and_universe_and_everything; // receive from istream
   
   ASSERT_EQ(42, meaning_of_life_and_universe_and_everything); // got the message
}

TEST(basic_twoway_streambuf, demo_test_string_in_string_out) 
{
   mzlib::twoway_streambuf stream_buffer(5000); 
   
   std::ostream stream_out(&stream_buffer); // ostream to memory 
   std::istream stream_in(&stream_buffer); // istream from the same memory 

   stream_out << "This is a string. I am on a horse."; // send to ostream
   
   std::string old_spice;
   
   // Works like you would expect from stream >> string operator: word by word
   
   stream_in >> old_spice; // receive from istream
   ASSERT_EQ("This", old_spice);
   
   stream_in >> old_spice; // ...
   ASSERT_EQ("is", old_spice);
   
   stream_in >> old_spice;
   ASSERT_EQ("a", old_spice);
   
   stream_in >> old_spice;
   ASSERT_EQ("string.", old_spice);
}

TEST(basic_twoway_streambuf, demo_test_integer_in_integer_out) 
{
   mzlib::twoway_streambuf stream_buffer(5000);
   
   std::ostream stream_out(&stream_buffer); // ostream to memory 
   std::istream stream_in(&stream_buffer); // istream from the same memory 

   stream_out << 42; // send something to ostream
   
   int meaning_of_life_and_universe_and_everything;
   
   stream_in >> meaning_of_life_and_universe_and_everything; // receive from istream
   
   ASSERT_EQ(42, meaning_of_life_and_universe_and_everything); // got the message
}