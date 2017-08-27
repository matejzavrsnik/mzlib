//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef SENTENCE_ASSEMBLARATOR_H
#define SENTENCE_ASSEMBLARATOR_H

#include <string>
#include <functional>

namespace mzlib {

// given a language token generator, this function assembles sentences.
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
      // close parentheses and quotes
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
      previous_punctuation = word[0]; // remember state of punctuation
      sentence += word;
   }
   return sentence;
}

} // namespace

#endif // SENTENCE_ASSEMBLARATOR_H

#ifdef MZLIB_BUILDING_TESTS

#ifndef SENTENCE_ASSEMBLARATOR_TESTS_H
#define SENTENCE_ASSEMBLARATOR_TESTS_H

TEST(sentence_assemblarator, basic) 
{
   std::vector<std::string> words = {"veni", ",", "vidi", ",","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = mzlib::sentence_assemblarator([&](){return *(words_iterator++);});
   // starts sentence with uppercase
   // inserts spaces between words, but after commas
   // stops when encounters '.'
   ASSERT_EQ(sentence, "Veni, vidi, dormivi."); 
}

TEST(sentence_assemblarator, stops_on_exclamation_mark) 
{
   std::vector<std::string> words = {"veni", "!", "vidi", ",","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = mzlib::sentence_assemblarator([&](){return *(words_iterator++);});
   ASSERT_EQ(sentence, "Veni!"); 
}

TEST(sentence_assemblarator, stops_on_question_mark) 
{
   std::vector<std::string> words = {"veni", "?", "vidi", ",","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = mzlib::sentence_assemblarator([&](){return *(words_iterator++);});
   ASSERT_EQ(sentence, "Veni?"); 
}

TEST(sentence_assemblarator, spaces_around_quotes) 
{
   std::vector<std::string> words = {"veni", "\"", "vidi", "\"","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = mzlib::sentence_assemblarator([&](){return *(words_iterator++);});
   // insert space before opening quote, but after closing quote
   ASSERT_EQ(sentence, "Veni \"vidi\" dormivi."); 
}

TEST(sentence_assemblarator, spaces_around_paretheses) 
{
   std::vector<std::string> words = {"veni", "(", "vidi", ")","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = mzlib::sentence_assemblarator([&](){return *(words_iterator++);});
   // insert space before opening parentheses, but after closing parentheses
   ASSERT_EQ(sentence, "Veni (vidi) dormivi."); 
}

TEST(sentence_assemblarator, quote_handling) 
{
   std::vector<std::string> words = {"veni", "\"", "\"", "vidi","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = mzlib::sentence_assemblarator([&](){return *(words_iterator++);});
   // will reject second quote in the row, but will close the quote before sentence ends
   ASSERT_EQ(sentence, "Veni \"vidi dormivi\"."); 
}

TEST(sentence_assemblarator, paretheses_handling) 
{
   std::vector<std::string> words = {"veni", "(", "(", "vidi","dormivi", "."};
   auto words_iterator = words.begin();
   std::string sentence = mzlib::sentence_assemblarator([&](){return *(words_iterator++);});
   // will reject second opening paretheses in the row, but will close it before sentence ends
   ASSERT_EQ(sentence, "Veni (vidi dormivi)."); 
}

#endif // SENTENCE_ASSEMBLARATOR_TESTS_H

#endif // MZLIB_BUILDING_TESTS
