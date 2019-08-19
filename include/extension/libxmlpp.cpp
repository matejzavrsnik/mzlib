//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "libxmlpp.h"

TEST(delete_all_children_except, demo) 
{
   xmlpp::DomParser parser;
   xmlpp::Element* root;
   
   std::string xml_file = R"(
   <show title="The Expanse">
      <chrisjen>Shohreh Aghdashloo</chrisjen>
      <amos>Wes Chatham</amos>
      <naomi>Dominique Tipper</naomi>
      <miller>Thomas Jane</miller>
   </show>
   )";

   parser.parse_memory(xml_file);
   root = parser.get_document()->get_root_node();
   
   mzlib::delete_all_children_except({"chrisjen", "amos"}, root);
   
   ASSERT_TRUE (root->get_children("chrisjen").size() > 0);
   ASSERT_TRUE (root->get_children("amos").size() > 0);
   ASSERT_FALSE(root->get_children("naomi").size() > 0);
   ASSERT_FALSE(root->get_children("miller").size() > 0);
}

TEST(delete_all_children_except, empty) 
{
   xmlpp::DomParser parser;
   xmlpp::Element* root;
   
   std::string xml_file = R"(
   <show title="The Expanse">
      <chrisjen>Shohreh Aghdashloo</chrisjen>
      <amos>Wes Chatham</amos>
      <naomi>Dominique Tipper</naomi>
      <miller>Thomas Jane</miller>
   </show>
   )";

   parser.parse_memory(xml_file);
   root = parser.get_document()->get_root_node();
   
   mzlib::delete_all_children_except({}, root);
   
   ASSERT_FALSE(root->get_children("chrisjen").size() > 0);
   ASSERT_FALSE(root->get_children("amos").size() > 0);
   ASSERT_FALSE(root->get_children("naomi").size() > 0);
   ASSERT_FALSE(root->get_children("miller").size() > 0);
}

TEST(delete_all_attributes_except, demo) 
{
   xmlpp::DomParser parser;
   xmlpp::Element* root;
   
   std::string xml_file = R"(
   <show title="The Expanse" genre="scifi" channel="SyFy" on_netflix="yes">
   </show>
   )";

   parser.parse_memory(xml_file);
   root = parser.get_document()->get_root_node();
   
   mzlib::delete_all_attributes_except({"title", "genre"}, root);
   
   ASSERT_TRUE (root->get_attribute("title") != nullptr);
   ASSERT_TRUE (root->get_attribute("genre") != nullptr);
   ASSERT_FALSE(root->get_attribute("channel") != nullptr);
   ASSERT_FALSE(root->get_attribute("on_netflix") != nullptr);
}

TEST(delete_all_attributes, demo) 
{
   xmlpp::DomParser parser;
   xmlpp::Element* root;
   
   std::string xml_file = R"(
   <show title="The Expanse" genre="scifi" channel="SyFy" on_netflix="yes">
   </show>
   )";

   parser.parse_memory(xml_file);
   root = parser.get_document()->get_root_node();
   
   mzlib::delete_all_attributes(root);
   mzlib::delete_all_attributes(root);
   
   ASSERT_TRUE(root->get_attribute("title") == nullptr);
   ASSERT_TRUE(root->get_attribute("genre") == nullptr);
   ASSERT_TRUE(root->get_attribute("channel") == nullptr);
   ASSERT_TRUE(root->get_attribute("on_netflix") == nullptr);
}

TEST(delete_all_xpath, demo) 
{
   xmlpp::DomParser parser;
   xmlpp::Element* root;
   
   std::string xml_file = R"(
   <show title="The Expanse">
      <ships>
         <mars>Rocinante</mars>
         <mars>Donnager</mars>
         <mormons>Nauvoo</mormons>
         <unn>Arboghast</unn>
      </ships>
      <characters>
         <mars>Theresa Yao</mars>
         <mars>Sutton</mars>
         <mormons>Elder McCann</mormons>
         <unn>Chrisjen Avasarala</unn>
      </characters>
   </show>
   )";

   parser.parse_memory(xml_file);
   root = parser.get_document()->get_root_node();
   
   mzlib::delete_all_xpath("/show/*/mars", root);
   
   ASSERT_FALSE(root->find("/show/ships/mars").size() > 0);
   ASSERT_FALSE(root->find("/show/characters/mars").size() > 0);
   
   ASSERT_TRUE(root->find("/show/ships/mormons").size() > 0);
   ASSERT_TRUE(root->find("/show/ships/unn").size() > 0);
   ASSERT_TRUE(root->find("/show/characters/mormons").size() > 0);
   ASSERT_TRUE(root->find("/show/characters/unn").size() > 0);
}

TEST(get_content_or_default, demo)
{
   // todo: write fixtures for these at some point
   xmlpp::Document* doc = new xmlpp::Document();
   doc->create_root_node("root");
   xmlpp::Element* root = doc->get_root_node();
   xmlpp::Element* element = root->add_child_element("element");
   element->set_first_child_text("Imperator Caesar Divi Filius Augustus");
   
   std::string s = mzlib::get_content_or_default(element);
   
   ASSERT_EQ("Imperator Caesar Divi Filius Augustus", s);
}

TEST(get_content_or_default, no_child_text_and_no_default_set)
{
   xmlpp::Document* doc = new xmlpp::Document();
   doc->create_root_node("root");
   xmlpp::Element* root = doc->get_root_node();
   xmlpp::Element* element = root->add_child_element("");
   
   std::string s = mzlib::get_content_or_default(element);
   
   ASSERT_EQ("", s);
}

TEST(get_content_or_default, no_child_text_but_default_set)
{
   xmlpp::Document* doc = new xmlpp::Document();
   doc->create_root_node("root");
   xmlpp::Element* root = doc->get_root_node();
   xmlpp::Element* element = root->add_child_element("");
   
   std::string s = mzlib::get_content_or_default(element, "default");
   
   ASSERT_EQ("default", s);
}

