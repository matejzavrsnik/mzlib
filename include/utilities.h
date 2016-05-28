// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>
#include <limits>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <random>
#include <locale>
#include <fstream>
#include <dirent.h>

namespace mzlib {
namespace util {

// adds to objects a capability to be easily identifiable across copies of itself
class cunique
{
   
private:
   
   int m_id;
   
   static int get_unique_int()
   {
      static int m_unique_int = 0;
      return ++m_unique_int;
   }
   
public:
   
   cunique()
   {
      m_id = get_unique_int();
   }
   
   cunique(const cunique&) = default;
   cunique(cunique && ) = default;
   cunique& operator=(const cunique&) = default;
   cunique& operator=(cunique&&) = default;
   ~cunique() = default;   
   
   int id()
   {
      return m_id;
   }
};
   
// to compare doubles for equality
class dbl
{

private:

   double m_val;
   double m_compared_to;
        
public:
        
   explicit dbl (double val) : 
      m_val(val),
      m_compared_to(val)
   {
   }
        
   dbl& equals (double val) 
   {
      m_compared_to = val;
      return *this;
   }
        
   operator bool () const 
   {
      const double delta = std::abs(m_val-m_compared_to);
      const double magnitude_candidate = std::abs(m_val+m_compared_to);
      const double magnitude = (magnitude_candidate >= 1 ? magnitude_candidate : 1);
      const int units_in_last_place = 4;
      const double allowed_delta = std::numeric_limits<double>::epsilon() * magnitude * units_in_last_place;
      return delta < allowed_delta || delta < std::numeric_limits<double>::min();
   }
        
   bool within_epsilon (double eps = 1e-10) const 
   {
      return std::abs(m_val-m_compared_to) <= eps;
   }

};
    
inline unsigned int get_random_integer ()
{
   static unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
   static std::mt19937 generator(seed);
   return generator();
}
    
inline double get_random_double_between_0_1 ()
{
   unsigned random_number = get_random_integer();
   return (double)random_number / (double)std::mt19937::max();
}

inline double get_random_double ()
{
   // rand() will never return completely random type T when T is a floating point type, 
   // because the integer value will be converted to a floating point value with all 
   // decimal digits 0, I invented the following trick.

   // cast to double immediately to make sure the division will be cast properly
   double numerator = get_random_integer();
   double denominator = get_random_integer();
   // collect some decimal digits
   double decimals = numerator / denominator;
   // collect whole digits too
   double final_rand = get_random_integer() + decimals;
   return final_rand;
}
    
inline unsigned int get_random_integer_between (unsigned from, unsigned to)
{
   double random_number = get_random_double_between_0_1();
   return (random_number * (to - from) + from);
}
    
template<class T, class U> typename std::map<T,U>::iterator 
get_random_element (std::map<T,U>& from_map) 
{
   unsigned random = get_random_integer_between(0, from_map.size()-1);
   auto result = from_map.begin();
   std::advance(result, random);
   return result;
}
    
template<typename T> std::size_t 
get_number_of_decimals (T num)
{
   //todo: needs special rule for denormalised values
   // convert to string first
   std::stringstream ss;
   const int precision = std::numeric_limits<double>::digits10 + 1;
   ss << std::setprecision( precision )
      << std::fixed;
   ss << num;
   std::string str = ss.str();
   // cut out everything but decimal places
   auto pos_of_decimal = str.find_first_of(".,");
   auto pos_of_last_non_zero = str.find_last_of("123456789");
   if (pos_of_decimal == std::string::npos ||
       pos_of_last_non_zero == std::string::npos ||
       pos_of_decimal > pos_of_last_non_zero) 
   {
      return 0;
   }
   else {
      str = str.substr(pos_of_decimal+1, pos_of_last_non_zero-1);
   }
   // count 
   return str.length();
}
    
// adds to vector, unless the element is already in
// returns iterator to element in the vector
template<class T> typename std::vector<T>::iterator 
push_back_unique (std::vector<T>& v, const T& element) 
{
   auto sought_element = std::find(v.begin(), v.end(), element);
   if (sought_element == v.end()) {
      v.push_back(element);
      sought_element = --v.end();
   }
   return sought_element;
}
    
// converts iterator to index
template<class T> typename std::vector<T>::difference_type
get_index (std::vector<T>& v, typename std::vector<T>::iterator& it) 
{
   return std::distance(v.begin(), it);
}
    
template<class T>
class cprobabilator
{

public:
        
   class eempty : public std::exception {};
        
private:

   typedef std::pair<T /*event*/, double /*probability level*/> event_t;
   std::vector<event_t> m_events;
        
   void normalise () 
   {
      double sum = 0;
      for(auto const& e : m_events) sum += e.second;
      for(auto& e : m_events) e.second /= sum;
   }
        
   void levelise () 
   {
      // The point of this function is to attach "levels" to each event, so that
      // when a random number [0,1] is generated, it will fall into "levels" in
      // a statistical meaningful way. Example: if there are 3 events with probabilities
      // 15%, 30%, and 55%, and then if you attach levels 0.15, 0.45, and 1.0,
      // and then you generate random number [0,1], there will be 15% chance the
      // number will fall under level 0.15, 30% chance it will be between 0.15 and 0.45,
      // and further 55% chance it will be between 0.45 and 1.0, all exactly corresponding
      // to original probabilities for events.
      double previous_level = 0;
      for (auto& e : m_events) {
         e.second += previous_level;
         previous_level = e.second;
      }
   }
        
public:

   void add_event (T event, double probability_level) 
   {
      m_events.push_back(std::make_pair(event, probability_level));
   }
        
   void add_event (T event) 
   {
      auto found = std::find_if (m_events.begin(), m_events.end(), 
         [&] (event_t& e)
         {
            return e.first == event;
         });
      if (found == m_events.end()) {
         m_events.push_back(std::make_pair(event, 1));
      }
      else {
         found->second += 1;
      }
   }
        
   void wrap_up () 
   {
      normalise();
      levelise();
   }
        
   const T get_event () 
   {
      double random = get_random_double_between_0_1();
      for (auto event_it = m_events.begin(); event_it != m_events.end(); ++event_it) {
         if (random < event_it->second) {
            return event_it->first;
         }
      }
      throw eempty(); // I couldn't imagine other way out of this
   }
   
   unsigned count_events () const 
   {
      return m_events.size();
   }

};
    
inline std::vector<std::string> split_string_puctuation (const std::string& str) 
{
   std::vector<std::string> split_string;
   std::string new_candidate = "";
   for (std::string::const_iterator ch_it = str.begin(); ch_it != str.end(); ++ch_it) {
      char ch = *ch_it;
      if (ispunct(ch) && ch!='\'') { // as in "isn't" and so
         if (!new_candidate.empty()) {
            split_string.push_back(new_candidate);
            new_candidate = "";
         }
         std::string ch_str = "";
         ch_str += ch;
         split_string.push_back(ch_str);
      }
      else {
         new_candidate += ch;
      }
   }
   if (!new_candidate.empty()) {
      split_string.push_back(new_candidate);
   }
   return split_string;
}
    
// given language token generator, this function assembles sentences.
// Tokens can be punctuation marks or words.
// Stops when words generator produces one of sentence ending punctuations: .?!
inline std::string sentence_assemblarator (std::function<std::string()> words_generator) 
{
   // get first word
   std::string word = words_generator();
   // reset state variables
   bool open_quotes = false;
   bool open_parentheses = false;
   char previous_punctuation = 0;
   // start with uppercase word
   word[0] = toupper(word[0]);
   std::string sentence = word;
   // append other words until .?! char
   while (word[0]!='.' && word[0]!='!' && word[0]!='?') {
      word = words_generator();
      // control states of quotes and parentheses
      if (word[0]=='\"') {
         if (previous_punctuation == '\"') continue; // can't have two quotes in a row
         open_quotes = !open_quotes;
      }
      if (word[0]=='(') {
         if(open_parentheses) continue; // can't have ( and then ( again
         open_parentheses = true;
      }
      if (word[0]==')') {
         if (!open_parentheses) continue; // can't have ) without first having (
         open_parentheses = false;
      }
      // prepend space
      bool prepend_space = true;
      if (ispunct(word[0])) {
         prepend_space = false;
         if (word[0]=='\"' && open_quotes) {
            prepend_space = true;
         }
         else if (word[0]=='(' && open_parentheses) {
            prepend_space = true;
         }
      }
      else { // not punctuation
         if (previous_punctuation=='\"' && open_quotes) {
            prepend_space = false;
         }
         else if (previous_punctuation=='(') {
            prepend_space = false;
         }
      } 
      if (prepend_space) { 
         sentence += " ";
      }
      // close paretheses and quotes
      if (word[0]=='.' || word[0]=='!' || word[0]=='?') {
         if (open_parentheses) {
            sentence += ")"; // close the parentheses before the sentence ends
            open_parentheses = false;
         }
         if (open_quotes) {
            sentence += "\""; // close the quotes before the sentence ends
            open_quotes = false;
         }
      }
      previous_punctuation = word[0]; // remember state of punctuaction
      sentence += word;
   }
   return sentence;
}

// Replace all occurrences of a string in a string
inline void string_replace (std::string& str, const std::string& replace_what, const std::string& replace_with) 
{
   for (size_t pos = 0; 
        (pos = str.find(replace_what, pos)) != std::string::npos; 
        pos += replace_with.length()) 
   {
      str.replace(pos, replace_what.length(), replace_with);
   }
}
    
inline std::string get_substring_between (const std::string& str, const std::string& start, const std::string& end)
{
   std::string result;
   size_t pos_start = str.find(start)+start.length();
   size_t pos_end = str.find(end, pos_start);
   if (pos_start != std::string::npos && 
       pos_end   != std::string::npos) 
   {
      if (pos_end < pos_start) {
         std::swap(pos_start, pos_end);
      }
      result = str.substr(pos_start, pos_end-pos_start);
   }
   return result;
}
    
    
// Change a string into one that is suitable for filename
inline std::string filenamearise (const std::string& filename_candidate, char space_ch)
{
   std::string filenamearised = "";
   for (auto letter : filename_candidate) {
      if (std::isspace(letter) && filenamearised.back() != space_ch) {
         filenamearised += space_ch;
      }
      else if (std::isalnum(letter)) {
         filenamearised += std::tolower(letter);
      }
   }
   return filenamearised;
}
    
// Read file contents and return it in a string
inline std::string read_file (std::string filename) 
{
   std::ifstream filestream(filename);
   std::stringstream buffer;
   buffer << filestream.rdbuf();
   return buffer.str();
}

// Save string contents into a file
inline void save_file (std::string filename, std::string content)
{
   std::ofstream out(filename);
   out << content;
   out.close();
}

// List all files in a directory
inline std::vector<std::string> list_files (std::string directory, bool include_hidden = true)
{
   std::vector<std::string> files;	
   DIR *pDIR;
   struct dirent *entry;
   if ( (pDIR=opendir(directory.c_str())) ) {
      while ( (entry = readdir(pDIR)) ) {
         bool hidden = (entry->d_name[0] == '.');
         if (hidden && !include_hidden) {
            continue;
         }
         std::string filename = entry->d_name;
         files.push_back(filename);
      }
      closedir(pDIR);
   }
   return files;
}
    
inline std::string extract_filename_from_path (std::string path)
{
   size_t pos = path.find_last_of("/\\");
   if (pos == std::string::npos) return "";
   return path.substr(pos+1, path.length()-pos);
}

// defined in boost/filesystem.hpp
// if project includes that, it will see, compile, and be able to use the following functions
#ifdef BOOST_FILESYSTEM_FILESYSTEM_HPP    

// List all files in a directory using boost
inline std::vector<std::string> boost_list_files (std::string directory, bool include_hidden = true)
{
   std::vector<std::string> files;
   boost::filesystem::path p(directory);
   boost::filesystem::directory_iterator end;
   for (boost::filesystem::directory_iterator path_it(p); path_it != end; ++path_it)
   {
      if (boost::filesystem::is_regular_file(*path_it)) {
         std::string filename = path_it->path().string();
         bool hidden = (filename[0] == '.');
         if (hidden && !include_hidden) {
            continue;
         }
         files.push_back(filename);
      }
   }
   return files;
}
#endif    
    
// defined in libxml++.h
// if project includes libxml++ lib, it will see, compile, and be able to use the following functions
#ifdef __LIBXMLCPP_H

inline void delete_all_but (std::vector<std::string> names, xmlpp::Node* from_node) 
{
   if (from_node == nullptr) return;
   std::list<xmlpp::Node*> children = from_node->get_children();
   for (xmlpp::Node* child : children) {
      std::string child_name = child->get_name();
      bool found = (std::find(names.begin(), names.end(), child_name) != names.end());
      if (!found) {
          from_node->remove_child(child);
      }
   }
}

inline void delete_all_attributes_but (std::vector<std::string> names, xmlpp::Node* from_node)
{
   xmlpp::Element* from_element = dynamic_cast<xmlpp::Element*>(from_node);
   if (from_element == nullptr) return;
   std::list<xmlpp::Attribute*> attributes_list = from_element->get_attributes();
   for (xmlpp::Attribute* attribute : attributes_list) {
      std::string attribute_name = attribute->get_name();
      bool found = (std::find(names.begin(), names.end(), attribute_name) != names.end());
      if (!found) {
         from_node->remove_child(attribute);
      }
   }
}

inline void delete_all_attributes (xmlpp::Node* from_node)
{
   delete_all_attributes_but({}, from_node);
}

inline void delete_all_but_xpath (std::string xpath, xmlpp::Node* from_node) 
{
   std::vector<xmlpp::Node*> content_div = from_node->find(xpath);
   if(content_div.size() > 0) {
      xmlpp::Document tempXmlDocument;
      tempXmlDocument.create_root_node_by_import(content_div[0]);
      delete_all_but({}, from_node);
      from_node->import_node(tempXmlDocument.get_root_node());
   }
}

inline void delete_all_xpath (std::string xpath, xmlpp::Node* from_node) 
{
   std::vector<xmlpp::Node*> nodes_found = from_node->find(xpath);
   for (xmlpp::Node* node_found : nodes_found) {
      xmlpp::Node* parent = node_found->get_parent();
      parent->remove_child(node_found);
   }
}

inline std::string get_content (std::string xpath, xmlpp::Node* from_node)
{
   if (from_node == nullptr) return "";
   std::string content;
   std::vector<xmlpp::Node*> nodes_found = from_node->find(xpath);
   if (nodes_found.size() > 0) {
      std::list<xmlpp::Node*> children = nodes_found[0]->get_children();
      if (children.size() > 0) {
         xmlpp::ContentNode* content_node = dynamic_cast<xmlpp::ContentNode*>(children.front());
         if (content_node != nullptr) {
            content = content_node->get_content();
         }
      }
   }
   return content;
}
#endif
    
} } // namespace mzlib::util

#endif // UTILITIES_H

