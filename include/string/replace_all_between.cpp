//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "replace_all_between.h"

namespace
{
   const std::vector<mzlib::delimiting_tag<std::string_view>> between_tags {
      {"<p>", "</p>"},
      {"<code>", "</code>"},
   };
   
   const std::vector<mzlib::replacement<std::string_view>> replacements {
      {"<", "&lt;"},
      {">", "&gt;"},
   };
}

TEST(string_replace_all_between, demo)
{
   std::string html = "<html><p>replace < and > here, but not elsewhere.</p></html>";
   mzlib::string_replace_all_between(html, between_tags, replacements);
   ASSERT_EQ(
      "<html><p>replace &lt; and &gt; here, but not elsewhere.</p></html>",
      html);
}

TEST(string_replace_all_between, many_sections)
{
   std::string html = "<html><p>replace <></p><p>replace <></p><p>replace <></p></html>";
   mzlib::string_replace_all_between(html, between_tags, replacements);
   ASSERT_EQ(
      "<html><p>replace &lt;&gt;</p><p>replace &lt;&gt;</p><p>replace &lt;&gt;</p></html>",
      html);
}

TEST(string_replace_all_between, many_sections_many_replacements)
{
   std::string html = "<html><p>replace <></p><code>replace <></code><p>replace <></p></html>";
   mzlib::string_replace_all_between(html, between_tags, replacements);
   ASSERT_EQ(
      "<html><p>replace &lt;&gt;</p><code>replace &lt;&gt;</code><p>replace &lt;&gt;</p></html>",
      html);
}

TEST(string_replace_all_between, no_sections)
{
   std::string html = "<html>replace < nothing ></html>";
   mzlib::string_replace_all_between(html, between_tags, replacements);
   ASSERT_EQ(
      "<html>replace < nothing ></html>",
      html);
}

TEST(string_replace_all_between, sections_not_provied)
{
   std::string html = "<html><p>replace <></p><code>replace <></code><p>replace <></p></html>";
   mzlib::string_replace_all_between(html, {}, replacements);
   ASSERT_EQ(
      "<html><p>replace <></p><code>replace <></code><p>replace <></p></html>",
      html);
}

TEST(string_replace_all_between, replacements_not_provied)
{
   std::string html = "<html><p>replace <></p><code>replace <></code><p>replace <></p></html>";
   mzlib::string_replace_all_between(html, between_tags, {});
   ASSERT_EQ(
      "<html><p>replace <></p><code>replace <></code><p>replace <></p></html>",
      html);
}
