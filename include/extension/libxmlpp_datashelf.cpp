//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "libxmlpp_datashelf.h"

class fixture_datashelf_former : public ::testing::Test 
{

protected:

   fixture_datashelf_former() {}
   virtual ~fixture_datashelf_former() {}
   
   virtual void SetUp() {}
   virtual void TearDown() {}
   
   std::string m_xml = R"(
      <shelf title="my bookshelf">
         <airplane model="spitfire" year="1943" designer="R. J. Mitchell"/>
         <book title="Children of Time">
            <rating source="Goodreads">4.29</rating>
            <rating source="Amazon">4.5</rating>
            <author>Adrian Tchaikovsky</author>
            <year>2016</year>
         </book>
         <folder>
            <coin_collection></coin_collection>
         </folder>
         <book title="Morning Star">
            <rating source="Goodreads">4.5</rating>
            <rating source="Amazon">4.6</rating>
            <author>Pierce Brown</author>
         </book>
      </shelf>
   )";
};

TEST_F(fixture_datashelf_former, create_datashelf_from_xml_string_demo)
{  
   auto shelf = mzlib::create_datashelf_from_xml_string(m_xml);
   auto rating = mzlib::ds::fluent(shelf).first("book").first("rating");
   ASSERT_EQ("Goodreads", rating.get_attribute("source").value());
   ASSERT_EQ("4.29", rating.get()->value());
}

TEST_F(fixture_datashelf_former, save_datashelf_to_xml_string_demo)
{  
   auto shelf = mzlib::create_datashelf_from_xml_string(m_xml);
   std::string created = mzlib::save_datashelf_to_xml_string(shelf);
   
   std::string expected = R"(<?xml version="1.0" encoding="UTF-8"?>
<shelf title="my bookshelf">
  <airplane model="spitfire" year="1943" designer="R. J. Mitchell"/>
  <book title="Children of Time">
    <rating source="Goodreads">4.29</rating>
    <rating source="Amazon">4.5</rating>
    <author>Adrian Tchaikovsky</author>
    <year>2016</year>
  </book>
  <folder>
    <coin_collection/>
  </folder>
  <book title="Morning Star">
    <rating source="Goodreads">4.5</rating>
    <rating source="Amazon">4.6</rating>
    <author>Pierce Brown</author>
  </book>
</shelf>
)";

   ASSERT_EQ(expected, created);
}