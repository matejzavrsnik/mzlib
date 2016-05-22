// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#include <map>

#include "../include/utilities.h"
#include "gtest/gtest.h"

using namespace mzlib::util;

namespace {

// The fixture
    
class test_utilities : public ::testing::Test {
 protected:

  test_utilities() {
  }
  
  virtual ~test_utilities() {
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
  
  double allowed_double_delta(double val, int ulp){
    double use_val = std::abs(val);
    if(use_val<1) use_val = 1;
    return std::numeric_limits<double>::epsilon() * use_val * ulp;
  }
};

// Tests

TEST_F(test_utilities, compare_equal_doubles_for_equality) {
    ASSERT_TRUE(dbl(13.3L).equals(13.3L));
}

TEST_F(test_utilities, compare_different_doubles_for_equality) {
    ASSERT_FALSE(dbl(13.3L).equals(13.2L));
}

TEST_F(test_utilities, compare_ranges_of_nearly_equals_doubles_for_equality) {
    // allowed difference is 4 units in last place
    const int ulp = 4;
    // compare all values in epsilon vicinity of centre values
    double centre_values[] = { 
        std::numeric_limits<double>::min(), // smallest possible
        -1e300L, // small, but far from min
        -1e10L, // almost zero on negative side, but far from zero
        -1e-321L, // compare to nearly zero on negative side
        -0L, // compare to negative zero
        0L, // around zero
        1e-321L, // compare to nearly zero on positive side
        1e-10L, // almost zero on positive side, but far from zero
        1L, // one
        13.3L, // something "normal"
        1e300, // large, but still far from max
        std::numeric_limits<double>::max()
    }; 
    // epsilon vicinity is 1000 representable values around specific centre value
    const int count_max = 1000;
    // for each such number
    for(double centre_value : centre_values) {
        double value=centre_value;
        // rewind half-way back to the negative
        for(int count=0; count<(count_max/2); ++count) {
            value = std::nextafter(value, value-1);
        }
        // run count_max comparisons to the positive
        for(int count=0; count<count_max; value = std::nextafter(value, value+1), ++count) {
            const double allowed_difference = allowed_double_delta(centre_value+value, ulp);
            const double difference = std::abs(value-centre_value);
            if(difference <= allowed_difference) {
                ASSERT_TRUE(dbl(value).equals(centre_value)) 
                    << "Comparing " << value << " to " << centre_value << 
                    " failed, but they are within " << ulp << " ulp.";
            }
            else {
                ASSERT_FALSE(dbl(value).equals(centre_value)) 
                    << "Comparing " << value << " to " << centre_value << 
                    " succeeded, but they are " << ulp << " ulp appart.";
            }
        }
    }
}

TEST_F(test_utilities, compare_equal_doubles_for_equality_within_epsilon) {
    ASSERT_TRUE(dbl(13.3).equals(13.2).within_epsilon(0.2));
}

TEST_F(test_utilities, compare_different_doubles_for_equality_within_epsilon) {
    ASSERT_FALSE(dbl(13.3).equals(13.2).within_epsilon(0.01));
}

TEST_F(test_utilities, get_number_of_decimals) {
    double double_num = 0;
    ASSERT_EQ(0, get_number_of_decimals(double_num));
    double_num = 1;
    ASSERT_EQ(0, get_number_of_decimals(double_num));
    double_num = 0.111;
    ASSERT_EQ(3, get_number_of_decimals(double_num));
    double_num = 0.11100;
    ASSERT_EQ(3, get_number_of_decimals(double_num));
    double_num = 0.111001;
    ASSERT_EQ(6, get_number_of_decimals(double_num));
}

TEST_F(test_utilities, push_back_if_not_in_different_vectors) {
    std::vector<std::string> v_string;
    std::vector<int> v_int;
    
    push_back_unique(v_string, std::string("test"));
    ASSERT_EQ(1, v_string.size());
    
    push_back_unique(v_int, 123);
    ASSERT_EQ(1, v_int.size());
}

TEST_F(test_utilities, push_back_if_not_in) {
    std::vector<int> v;
    ASSERT_EQ(v.size(), 0);
    auto a = push_back_unique(v, 11);
    ASSERT_EQ(*a, 11);
    ASSERT_EQ(v.size(), 1);
    auto b = push_back_unique(v, 11);
    ASSERT_EQ(*b, 11);
    ASSERT_EQ(v.size(), 1);
    auto c = push_back_unique(v, 12);
    ASSERT_EQ(*c, 12);
    ASSERT_EQ(v.size(), 2);
    auto d = push_back_unique(v, 12);
    ASSERT_EQ(*d, 12);
    ASSERT_EQ(v.size(), 2);    
    auto e = push_back_unique(v, 13);
    ASSERT_EQ(*e, 13);
    ASSERT_EQ(v.size(), 3);
    auto f = push_back_unique(v, 12);
    ASSERT_EQ(*f, 12);
    ASSERT_EQ(v.size(), 3);
    auto g = push_back_unique(v, 11);
    ASSERT_EQ(*g, 11);
    ASSERT_EQ(v.size(), 3);
}

TEST_F(test_utilities, get_random_integer) {
    unsigned int a = get_random_integer();
    unsigned int b = get_random_integer();
    unsigned int c = get_random_integer();
    unsigned int d = get_random_integer();
    ASSERT_NE(a, b);
    ASSERT_NE(b, c);
    ASSERT_NE(c, d);
}

TEST_F(test_utilities, get_random_double_between_0_1) {
    double a = get_random_double_between_0_1();
    double b = get_random_double_between_0_1();
    double c = get_random_double_between_0_1();
    double d = get_random_double_between_0_1();
    ASSERT_NE(a, b);
    ASSERT_NE(b, c);
    ASSERT_NE(c, d);
}

TEST_F(test_utilities, get_random_element) {
    std::map<int,int> example;
    example[0] = 0;
    example[1] = 2;
    example[2] = 3;
    std::map<int,int>::iterator does_it_work = get_random_element(example);
    ASSERT_TRUE(true);
}

TEST_F(test_utilities, probabilator_basic_test) {
    cprobabilator<int> probabilator;
    probabilator.add_event(0, 10); // event 1, probability 10%
    probabilator.add_event(1, 30); // event 2, probability 30%
    probabilator.add_event(2, 60); // event 3, probability 60%
    probabilator.wrap_up();
    
    std::vector<int> event_occurences = {0,0,0};
    int repetitions = 10000;
    for(int i=0; i<repetitions; ++i) {
        int event = probabilator.get_event();
        event_occurences[event]++;
    }
    
    ASSERT_NEAR(event_occurences[0], repetitions*0.1, repetitions*0.02); // event 0 happened 1000 times +- 200
    ASSERT_NEAR(event_occurences[1], repetitions*0.3, repetitions*0.02); // event 1 happened 3000 times +- 200
    ASSERT_NEAR(event_occurences[2], repetitions*0.6, repetitions*0.02); // event 2 happened 6000 times +- 200
}

TEST_F(test_utilities, get_index) {
    std::vector<int> v;
    for(int i=0; i<10; i++) {
        v.push_back(i);
    }
    // first 
    auto it_0 = std::find(v.begin(), v.end(), 0);
    int index_0 = get_index(v, it_0);
    ASSERT_EQ(index_0, 0);
    // second
    auto it_1 = std::find(v.begin(), v.end(), 1);
    int index_1 = get_index(v, it_1);
    ASSERT_EQ(index_1, 1);
    // middle
    auto it_5 = std::find(v.begin(), v.end(), 5);
    int index_5 = get_index(v, it_5);
    ASSERT_EQ(index_5, 5);
    // last
    auto it_9 = std::find(v.begin(), v.end(), 9);
    int index_9 = get_index(v, it_9);
    ASSERT_EQ(index_9, 9);
}

TEST_F(test_utilities, split_string_puctuation_basic) {
    std::string test = ",word!)";
    std::vector<std::string> result = split_string_puctuation(test);
    ASSERT_EQ(result.size(), 4);
    ASSERT_EQ(result[0], ",");
    ASSERT_EQ(result[1], "word");
    ASSERT_EQ(result[2], "!");
    ASSERT_EQ(result[3], ")");
}

TEST_F(test_utilities, split_string_puctuation_no_punctuations) {
    std::string test = "word";
    std::vector<std::string> result = split_string_puctuation(test);
    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(result[0], "word");
}

TEST_F(test_utilities, split_string_puctuation_no_punctuations_at_beginning) {
    std::string test = "word).";
    std::vector<std::string> result = split_string_puctuation(test);
    ASSERT_EQ(result.size(), 3);
    ASSERT_EQ(result[0], "word");
    ASSERT_EQ(result[1], ")");
    ASSERT_EQ(result[2], ".");
}

TEST_F(test_utilities, split_string_puctuation_no_punctuations_at_end) {
    std::string test = "\",word";
    std::vector<std::string> result = split_string_puctuation(test);
    ASSERT_EQ(result.size(), 3);
    ASSERT_EQ(result[0], "\"");
    ASSERT_EQ(result[1], ",");
    ASSERT_EQ(result[2], "word");
}

TEST_F(test_utilities, split_string_puctuation_all_punctuations) {
    std::string test = "!?.,;:-\"()\n";
    std::vector<std::string> result = split_string_puctuation(test);
    ASSERT_EQ(result.size(), 11);
    ASSERT_EQ(result[0], "!");
    ASSERT_EQ(result[1], "?");
    ASSERT_EQ(result[2], ".");
    ASSERT_EQ(result[3], ",");
    ASSERT_EQ(result[4], ";");
    ASSERT_EQ(result[5], ":");
    ASSERT_EQ(result[6], "-");
    ASSERT_EQ(result[7], "\"");
    ASSERT_EQ(result[8], "(");
    ASSERT_EQ(result[9], ")");
    ASSERT_EQ(result[10], "\n");
}

TEST_F(test_utilities, sentence_assemblarator_basic_test) {
    std::vector<std::string> words = {"veni", ",", "vidi", ",","dormivi", "."};
    auto words_iterator = words.begin();
    std::string sentence = sentence_assemblarator([&](){return *(words_iterator++);});
    // starts sentence with uppercase
    // inserts spaces between words, but after commas
    // stops when encounters '.'
    ASSERT_EQ(sentence, "Veni, vidi, dormivi."); 
}

TEST_F(test_utilities, sentence_assemblarator_stops_on_exclamation_mark) {
    std::vector<std::string> words = {"veni", "!", "vidi", ",","dormivi", "."};
    auto words_iterator = words.begin();
    std::string sentence = sentence_assemblarator([&](){return *(words_iterator++);});
    ASSERT_EQ(sentence, "Veni!"); 
}

TEST_F(test_utilities, sentence_assemblarator_stops_on_question_mark) {
    std::vector<std::string> words = {"veni", "?", "vidi", ",","dormivi", "."};
    auto words_iterator = words.begin();
    std::string sentence = sentence_assemblarator([&](){return *(words_iterator++);});
    ASSERT_EQ(sentence, "Veni?"); 
}

TEST_F(test_utilities, sentence_assemblarator_spaces_around_quotes) {
    std::vector<std::string> words = {"veni", "\"", "vidi", "\"","dormivi", "."};
    auto words_iterator = words.begin();
    std::string sentence = sentence_assemblarator([&](){return *(words_iterator++);});
    // insert space before opening quote, but after closing quote
    ASSERT_EQ(sentence, "Veni \"vidi\" dormivi."); 
}

TEST_F(test_utilities, sentence_assemblarator_spaces_around_paretheses) {
    std::vector<std::string> words = {"veni", "(", "vidi", ")","dormivi", "."};
    auto words_iterator = words.begin();
    std::string sentence = sentence_assemblarator([&](){return *(words_iterator++);});
    // insert space before opening parentheses, but after closing parentheses
    ASSERT_EQ(sentence, "Veni (vidi) dormivi."); 
}

TEST_F(test_utilities, sentence_assemblarator_quote_handling) {
    std::vector<std::string> words = {"veni", "\"", "\"", "vidi","dormivi", "."};
    auto words_iterator = words.begin();
    std::string sentence = sentence_assemblarator([&](){return *(words_iterator++);});
    // will reject second quote in the row, but will close the quote before sentence ends
    ASSERT_EQ(sentence, "Veni \"vidi dormivi\"."); 
}

TEST_F(test_utilities, sentence_assemblarator_paretheses_handling) {
    std::vector<std::string> words = {"veni", "(", "(", "vidi","dormivi", "."};
    auto words_iterator = words.begin();
    std::string sentence = sentence_assemblarator([&](){return *(words_iterator++);});
    // will reject second opening paretheses in the row, but will close it before sentence ends
    ASSERT_EQ(sentence, "Veni (vidi dormivi)."); 
}

}