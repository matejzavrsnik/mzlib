
#include <iterator>

//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_COPY_ITERATORS_H
#define MZLIB_COPY_ITERATORS_H

namespace mzlib {

// Because std::copy assumes destination is at least as large as source.
// You could use copy_n, but for general case you would then need to call 
// std::min to determine which range is smaller and copy that much only.
// Seems a bit superfluous to call std::min in this case, when you can just
// check if any of the iterators are at position "last" instead of just the
// input range, as std::copy does. Or am I missing something?
   
template<class OutputIt, class InputIt>
constexpr OutputIt copy(
   InputIt  in_first,  const InputIt  in_last,
   OutputIt out_first, const OutputIt out_last)
{
   while(out_first != out_last && in_first != in_last) {
      *out_first = *in_first;
      out_first = std::next(out_first);
      in_first = std::next(in_first);
   }
   return out_first;
}

} // namespace

#endif // MZLIB_COPY_ITERATORS_H

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_COPY_ITERATORS_TESTS_H
#define MZLIB_COPY_ITERATORS_TESTS_H

TEST(copy_iterators, equal_size) 
{
   std::string a = "Do You know Gods Of Death Love Apples?";
   std::string b = "______________________________________";
   mzlib::copy(a.begin(), a.end(), b.begin(), b.end());
   ASSERT_EQ(a, b);
}

TEST(copy_iterators, source_larger) 
{
   std::string a = "Do You know Gods Of Death Love Apples?";
   std::string b = "________________";
   mzlib::copy(a.begin(), a.end(), b.begin(), b.end());
   ASSERT_EQ("Do You know Gods", b);
}

TEST(copy_iterators, destination_larger) 
{
   std::string a = "Gods Of Death Love Apples?";
   std::string b = "______________________________________";
   mzlib::copy(a.begin(), a.end(), b.begin(), b.end());
   ASSERT_EQ("Gods Of Death Love Apples?____________", b);
}

TEST(copy_iterators, copy_middle) 
{
   std::string a = "Do You know Gods Of Death Love Apples?";
   std::string b = "______________________________________";
   mzlib::copy(a.begin()+12, a.begin()+25, b.begin(), b.end());
   ASSERT_EQ("Gods Of Death_________________________", b);
}

#endif // MZLIB_COPY_ITERATORS_TESTS_H

#endif // MZLIB_BUILDING_TESTS
