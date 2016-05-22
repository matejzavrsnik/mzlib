// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#include "../include/markov_chain.h"
#include "gtest/gtest.h"

#include <fstream>

namespace {

// The fixture
    
class test_markov_chain : public ::testing::Test {
 protected:

  std::string m_hesse_quotes;
     
  test_markov_chain() {
      m_hesse_quotes = 
          "I have always believed, and I still believe, that whatever good or bad fortune may "
          "come our way we can always give it meaning and transform it into something of value. " 
          "What could I say to you that would be of value, except that perhaps you seek too much, " 
          "that as a result of your seeking you cannot find. We are not going in circles, we are "
          "going upwards. The path is a spiral; we have already climbed many steps. It may be important "
          "to great thinkers to examine the world, to explain and despise it. But I think it is only "
          "important to love the world, not to despise it, not for us to hate each other, but to be "
          "able to regard the world and ourselves and all beings with love, admiration and respect.";
  }
  
  virtual ~test_markov_chain() {
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
  
};

// Tests

TEST_F(test_markov_chain, basic_test) {
    mzlib::cmarkov_chain<int> markov_chain;
    // 1 -> 2 -> 1
    //   -> 3 -> 2
    for(int number : {1,2,1,3,2})
        markov_chain.read_next(number);
    markov_chain.wrap_up();
    
    int count = 0, repetitions = 10000, next_number;
    std::array<int,3> stats = {0,0,0};
    std::vector<int> sequence;
    do {
        ++count;
        next_number = markov_chain.get_next();
        ++stats[next_number-1];
        sequence.push_back(next_number);
    }
    while(count < repetitions);
    
    // test statistical probability of items occurring
    ASSERT_NEAR(stats[0], repetitions*0.4, repetitions*0.02); // 0 happened 4000 times +- 200
    ASSERT_NEAR(stats[1], repetitions*0.4, repetitions*0.02); // 1 happened 4000 times +- 200
    ASSERT_NEAR(stats[2], repetitions*0.2, repetitions*0.02); // 2 happened 2000 times +- 200

    // test for impossible sequences, given markov chain rules
    size_t number, previous;
    for(number = 1, previous=0; number < sequence.size(); ++number, ++previous) {
        ASSERT_NE(sequence[number], sequence[previous]) << "no transition allows repeated number";
        if(sequence[number]==1) {
            ASSERT_EQ(sequence[previous], 2) 
                << "defined only 2->1, this is invalid: " 
                << sequence[previous] << "->" << sequence[number];
        }
        if(sequence[number]==3) {
            ASSERT_EQ(sequence[previous], 1) 
                << "defined only 1->3, this is invalid: " 
                << sequence[previous] << "->" << sequence[number];
        }
    }
}

TEST_F(test_markov_chain, demo_text_generation_with_markov_chains) {
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