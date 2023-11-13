//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "concepts.h"

#include <string>
#include <unordered_set>

// -----------------------

enum class work_on_string_overload
{
   readable,
   writable
};

work_on_string_overload work_on_string(mzlib::readable_string auto)
{
   return work_on_string_overload::readable;
}

work_on_string_overload work_on_string(mzlib::writable_string auto)
{
   return work_on_string_overload::writable;
}

TEST(concepts, readonly_string) 
{
   ASSERT_EQ(work_on_string_overload::readable, work_on_string(std::string_view("a")));
   ASSERT_EQ(work_on_string_overload::readable, work_on_string(std::wstring_view(L"a")));
   ASSERT_EQ(work_on_string_overload::readable, work_on_string(std::u16string_view(u"a")));
   ASSERT_EQ(work_on_string_overload::readable, work_on_string(std::u32string_view(U"a")));
   
   ASSERT_EQ(work_on_string_overload::writable, work_on_string(std::string("a")));
   ASSERT_EQ(work_on_string_overload::writable, work_on_string(std::wstring(L"a")));
   ASSERT_EQ(work_on_string_overload::writable, work_on_string(std::u16string(u"a")));
   ASSERT_EQ(work_on_string_overload::writable, work_on_string(std::u32string(U"a")));
}

// -----------------------

template<typename T>
bool resolved_as_concept_iterable(T arg)
{
   return false;
}

template<mzlib::iterable T>
bool resolved_as_concept_iterable(T arg)
{
   return true;
}

TEST(concepts, iterable)
{
   ASSERT_TRUE(resolved_as_concept_iterable(std::vector<int>()));
   ASSERT_TRUE(resolved_as_concept_iterable(std::map<int, int>()));
   ASSERT_TRUE(resolved_as_concept_iterable(std::unordered_map<int, int>()));
   ASSERT_TRUE(resolved_as_concept_iterable(std::set<int, int>()));
   ASSERT_TRUE(resolved_as_concept_iterable(std::unordered_set<int, int>()));

   ASSERT_FALSE(resolved_as_concept_iterable((int)1));
   ASSERT_FALSE(resolved_as_concept_iterable((long)1));
}

// -----------------------

template<typename T>
bool resolved_as_concept_stream_outable(T arg)
{
   return false;
}

template<mzlib::stream_outable T>
bool resolved_as_concept_stream_outable(T arg)
{
   return true;
}

TEST(concepts, stream_outable)
{
   ASSERT_TRUE(resolved_as_concept_stream_outable(1));
   ASSERT_TRUE(resolved_as_concept_stream_outable("string"));
   ASSERT_TRUE(resolved_as_concept_stream_outable(std::string("string")));

   // so uness my printer for std::pair is included, there is no operator<< for std::pair
   ASSERT_FALSE(resolved_as_concept_iterable(std::make_pair(1, "str")));
}