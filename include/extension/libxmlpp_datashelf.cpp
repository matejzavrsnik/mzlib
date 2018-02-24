//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "libxmlpp_datashelf.h"
#include "../tools/fluent_datashelf.h"

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

void receives_sv(std::string_view sv) { return; };
void receives_str(std::string str) { return; };
std::string_view returns_sv() { return "sv"; };
std::string returns_str() { return "str"; };

TEST_F(fixture_datashelf_former, create_datashelf_from_xml_string_demo)
{  
   Glib::ustring ustr = "ustr";
   std::string str = "str";
   std::string_view sv = "sv";
   char* cp = "literal";
   
   // between friends
   str = sv; // ok
   sv = str; // ok
   std::string str2(sv); // ok
   std::string_view sv2(str); // ok
   //cp = str; // error
   //cp = sv; // error
   str = cp; // ok
   sv = cp; // ok
   receives_sv(cp); // ok
   receives_str(cp); // ok
   
   // non-standard strings
   str = ustr; // ok, conversion provided by Glib::ustring
   //sv = ustr; // error: could not convert
   sv = ustr.data(); // ok, .data() returns char*
   //ustr = sv; // error: could not convert
   ustr = sv.data(); // ok, .data() returns char*
   ustr = str; // ok, conversion provided by Glib::ustring
   //receives_sv(ustr); // error: could not convert
   receives_str(ustr); // ok
   ustr = returns_str(); // ok
   //ustr = returns_sv(); // error: could not convert
   
   // implicit conversions to std::string_view
   receives_sv(str); // ok
   receives_sv(sv); // ok
   receives_sv("literal"); // ok
   receives_sv(cp); // ok
   //receives_sv(ustr); // error: could not convert
   receives_sv(ustr.data()); // ok, .data() returns char*
   
   // implicit conversions to std::string
   receives_str(str); // ok
   //receives_str(sv); // error: could not convert
   receives_str(sv.data()); // ok, .data() returns char*
   receives_str("literal"); // ok
   receives_str(cp); // ok
   receives_str(ustr); // error: could not convert
   
   // operators
   str == sv; // ok
   //str = sv + str2; // error: no such operator+
   

   
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