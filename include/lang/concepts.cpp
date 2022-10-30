//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "concepts.h"

#include <string>

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
