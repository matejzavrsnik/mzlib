//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef NUMBER_OF_DECIMALS_H
#define NUMBER_OF_DECIMALS_H

namespace mzlib {

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

} // namespace

#endif // NUMBER_OF_DECIMALS_H

#ifdef NUMBER_OF_DECIMALS_TESTS_H

TEST(get_number_of_decimals, basic) 
{
   double double_num = 0;
   ASSERT_EQ(0, mzlib::get_number_of_decimals(double_num));
   double_num = 1;
   ASSERT_EQ(0, mzlib::get_number_of_decimals(double_num));
   double_num = 0.111;
   ASSERT_EQ(3, mzlib::get_number_of_decimals(double_num));
   double_num = 0.11100;
   ASSERT_EQ(3, mzlib::get_number_of_decimals(double_num));
   double_num = 0.111001;
   ASSERT_EQ(6, mzlib::get_number_of_decimals(double_num));
}

#endif // NUMBER_OF_DECIMALS_TESTS_H
