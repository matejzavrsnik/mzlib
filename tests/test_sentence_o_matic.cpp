// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#include "../include/sentence_o_matic.h"
#include "gtest/gtest.h"

#include <fstream>

namespace {

// The fixture
    
class test_sentence_o_matic : public ::testing::Test {
 protected:

  std::string m_hesse_quotes;
     
  test_sentence_o_matic() :
      m_hesse_quotes( 
          "I have always believed, and I still believe, that whatever good or bad fortune may "
          "come our way we can always give it meaning and transform it into something of value. " 
          "What could I say to you that would be of value, except that perhaps you seek too much, " 
          "that as a result of your seeking you cannot find. We are not going in circles, we are "
          "going upwards. The path is a spiral; we have already climbed many steps. It may be important "
          "to great thinkers to examine the world, to explain and despise it. But I think it is only "
          "important to love the world, not to despise it, not for us to hate each other, but to be "
          "able to regard the world and ourselves and all beings with love, admiration and respect.")
  {
  }
  
  virtual ~test_sentence_o_matic() {
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
  
};

// Tests

TEST_F(test_sentence_o_matic, demo_test) {
    mzlib::csentence_o_matic sentence_o_matic;
    std::stringstream ss(m_hesse_quotes);
    std::string word;
    do {
        ss >> word;
        sentence_o_matic.read_next(word);
    }
    while(ss);
    sentence_o_matic.wrap_up();
    
    std::string generated = "";
    do {
        generated += "\n";
        generated += sentence_o_matic.get_next();
    }
    while(generated.length() < 10000);
    
    //std::cout << generated;
    ASSERT_TRUE(generated.length() >= 10000); // how do you test meaningless content?
}

}