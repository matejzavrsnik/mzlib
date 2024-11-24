//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "datashelf.h"

TEST(datashelf_foundation, node_is_empty)
{
   std::shared_ptr<mzlib::ds::node> node = 
      std::make_shared<mzlib::ds::node>();
   ASSERT_TRUE(node->is_empty());
}

TEST(datashelf_foundation, node_not_empty_if_value_set)
{
   std::shared_ptr<mzlib::ds::node> node = 
      std::make_shared<mzlib::ds::node>("", "value");
   ASSERT_FALSE(node->is_empty());
}

TEST(datashelf_foundation, node_not_empty_if_name_set)
{
   std::shared_ptr<mzlib::ds::node> node = 
      std::make_shared<mzlib::ds::node>("name");
   ASSERT_FALSE(node->is_empty());
}

#define MZLIB_FIND_WHERE(container, field, value) \
std::find_if (container.begin(), container.end(), \
   [] (decltype(container.begin()) n) \
   { return n->##field##() == value; });

TEST(datashelf_foundation, node_add_node)
{
   std::shared_ptr<mzlib::ds::node> node = 
      std::make_shared<mzlib::ds::node>();
   node->add_node("name1", "value1");
   node->add_node("name2", "value2");
   
   auto node1 = std::find_if (node->nodes().begin(), node->nodes().end(), 
      [] (const std::shared_ptr<mzlib::ds::node>& n)
      {
         return n->name() == "name1";
      });
   auto node2 = std::find_if (node->nodes().begin(), node->nodes().end(), 
      [] (const std::shared_ptr<mzlib::ds::node>& n)
      {
         return n->name() == "name2";
      });
   
   ASSERT_NE(node->nodes().end(), node1);
   ASSERT_EQ("name1", (*node1)->name());
   ASSERT_EQ("value1", (*node1)->value());
   
   ASSERT_NE(node->nodes().end(), node2);
   ASSERT_EQ("name2", (*node2)->name());
   ASSERT_EQ("value2", (*node2)->value());   
}

TEST(datashelf_foundation, node_add_node_parent_is_set)
{
   std::shared_ptr<mzlib::ds::node> node = 
      std::make_shared<mzlib::ds::node>();
   node->add_node("name1", "value1");
   
   auto node1 = std::find_if (node->nodes().begin(), node->nodes().end(), 
      [] (std::shared_ptr<mzlib::ds::node> n)
      {
         return n->name() == "name1";
      });
   
   ASSERT_NE(node->nodes().end(), node1);
   ASSERT_EQ(node, (*node1)->parent()); 
}

TEST(datashelf_foundation, node_add_node_returns_new_node)
{
   std::shared_ptr<mzlib::ds::node> node = 
      std::make_shared<mzlib::ds::node>();
   auto new_node = node->add_node("name1", "value1");

   auto node1 = std::find_if (node->nodes().begin(), node->nodes().end(),
      [] (const std::shared_ptr<mzlib::ds::node>& n)
      {
         return n->name() == "name1";
      });
   
   ASSERT_EQ(new_node, *node1);
}

TEST(datashelf_foundation, node_add_attribute)
{
   std::shared_ptr<mzlib::ds::node> node = 
      std::make_shared<mzlib::ds::node>();
   node->add_attribute("name1", "value1");
   node->add_attribute("name2", "value2");
   
   auto attr1 = std::find_if (node->attributes().begin(), node->attributes().end(), 
      [] (const std::shared_ptr<mzlib::ds::attribute>& n)
      {
         return n->name() == "name1";
      });
   auto attr2 = std::find_if (node->attributes().begin(), node->attributes().end(), 
      [] (const std::shared_ptr<mzlib::ds::attribute>& n)
      {
         return n->name() == "name2";
      });
   
   ASSERT_NE(node->attributes().end(), attr1);
   ASSERT_EQ("name1", (*attr1)->name());
   ASSERT_EQ("value1", (*attr1)->value());
   
   ASSERT_NE(node->attributes().end(), attr2);
   ASSERT_EQ("name2", (*attr2)->name());
   ASSERT_EQ("value2", (*attr2)->value());   
}

TEST(datashelf_foundation, node_add_attribute_returns_attribute)
{
   std::shared_ptr<mzlib::ds::node> node = 
      std::make_shared<mzlib::ds::node>();
   auto new_attr = node->add_attribute("name1", "value1");
   
   auto attr = std::find_if (node->attributes().begin(), node->attributes().end(), 
      [] (const std::shared_ptr<mzlib::ds::attribute>& n)
      {
         return n->name() == "name1";
      });
   
   ASSERT_EQ(new_attr, *attr);
}
