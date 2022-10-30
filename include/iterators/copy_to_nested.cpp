//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "copy_to_nested.h"
#include <vector>

TEST(copy_to_nested, containers_equal_size_subs_equal_size) 
{
   std::string a = "Do You know Gods Of Death Love Apples?";
   std::vector<std::string> b = {
      "___________________",
      "___________________"};
   
   std::vector<std::string> expected = {
      "Do You know Gods Of",
      " Death Love Apples?"};
   auto copied = mzlib::copy_to_nested(a.begin(), a.end(), b.begin(), b.end());
   
   ASSERT_EQ(expected, b);
   ASSERT_EQ(copied.input_it, a.end());
   ASSERT_EQ(copied.output_it, b[1].end());
}

TEST(copy_to_nested, containers_equal_size_subs_not_equal_size) 
{
   std::string a = "Do You know Gods Of Death Love Apples?";
   std::vector<std::string> b = {
      "___________________",
      "____",
      "_______________"};
   
   std::vector<std::string> expected = {
      "Do You know Gods Of",
      " Dea",
      "th Love Apples?"};
   auto copied = mzlib::copy_to_nested(a.begin(), a.end(), b.begin(), b.end());
   
   ASSERT_EQ(expected, b);
   ASSERT_EQ(copied.input_it, a.end());
   ASSERT_EQ(copied.output_it, b[2].end());
}

TEST(copy_to_nested, source_larger_subs_equal_size) 
{
   std::string a = "Do You know Gods Of Death Love Apples?";
   std::vector<std::string> b = {
      "__________",
      "__________"};
   
   std::vector<std::string> expected = {
      "Do You kno",
      "w Gods Of "};
   auto copied = mzlib::copy_to_nested(a.begin(), a.end(), b.begin(), b.end());
   
   ASSERT_EQ(expected, b);
   ASSERT_EQ(copied.input_it, a.begin()+20);
   ASSERT_EQ(copied.output_it, b[1].end());
}

TEST(copy_to_nested, source_larger_subs_not_equal_size) 
{
   std::string a = "Do You know Gods Of Death Love Apples?";
   std::vector<std::string> b = {
      "__________",
      "___",
      "_______"};
   
   std::vector<std::string> expected = {
      "Do You kno",
      "w G",
      "ods Of "};
   auto copied = mzlib::copy_to_nested(a.begin(), a.end(), b.begin(), b.end());
   
   ASSERT_EQ(expected, b);
   ASSERT_EQ(copied.input_it, a.begin()+20);
   ASSERT_EQ(copied.output_it, b[2].end());
}





TEST(copy_to_nested, destination_larger_subs_equal_size) 
{
   std::string a = "Gods Of Death Love Apples";
   std::vector<std::string> b = {
      "______________",
      "______________"};
   
   std::vector<std::string> expected = {
      "Gods Of Death ",
      "Love Apples___"};
   auto copied = mzlib::copy_to_nested(a.begin(), a.end(), b.begin(), b.end());
   
   ASSERT_EQ(expected, b);
   ASSERT_EQ(copied.input_it, a.end());
   ASSERT_EQ(copied.output_it, b[1].begin()+11);
}

TEST(copy_to_nested, destination_larger_subs_not_equal_size) 
{
   std::string a = "Gods Of Death Love Apples";
   std::vector<std::string> b = {
      "______________",
      "_____",
      "________"};
   
   std::vector<std::string> expected = {
      "Gods Of Death ",
      "Love ",
      "Apples__"};
   auto copied = mzlib::copy_to_nested(a.begin(), a.end(), b.begin(), b.end());
   
   ASSERT_EQ(expected, b);
   ASSERT_EQ(copied.input_it, a.end());
   ASSERT_EQ(copied.output_it, b[2].begin()+6);
}

TEST(copy_to_nested, copy_middle) 
{
   std::string a = "Gods Of Death Love Apples";
   std::vector<std::string> b = {
      "______________",
      "_____",
      "________"};
   
   std::vector<std::string> expected = {
      "______________",
      "Love ",
      "________"};
   auto copied = mzlib::copy_to_nested(
      a.begin()+14, a.begin()+19, 
      b.begin()+1, b.begin()+2);
   
   ASSERT_EQ(expected, b);
   ASSERT_EQ(copied.input_it, a.begin()+19);
   ASSERT_EQ(copied.output_it, b[1].end());
}
