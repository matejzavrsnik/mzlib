//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "mass_centre.h"

TEST(mass_centre, add_to_mass_centre) 
{
   struct t_centres_of_mass {
      mzlib::mass_centre2d mass_centre;
      mzlib::mass_centre2d average_now;
   } test_mass_data[] = {
      {{{383,886},777}, {{382.99999835692836,885.99999619905623},777}},
      {{{915,793},335}, {{543.26978417266196,857.98291366906483},1112}},
      {{{386,492},649}, {{485.30948324815449,723.10335036910840},1761}},
      {{{421,362},27},  {{484.33836689038031,717.65044742729310},1788}},
      {{{690,59},763},  {{545.85143081144645,520.64915719325745},2551}},
      {{{926,540},426}, {{600.24958011420892,523.41820624790057},2977}},
      {{{172,736},211}, {{571.90558343789212,537.48808030112923},3188}},
      {{{368,567},429}, {{547.72103953552664,540.98838816698913},3617}},
      {{{782,530},862}, {{592.80888591203393,538.87363250725605},4479}},
      {{{123,67},135},  {{579.06285218899006,525.06718682271355},4614}},
      {{{929,802},22},  {{580.72346850733402,526.38136324417599},4636}},
      {{{58,69},167},   {{562.54840724547171,510.47824276493856},4803}},
      {{{393,456},11},  {{562.16098878271714,510.35375986705441},4814}},
      {{{42,229},373},  {{524.75592828224410,490.12145748987854},5187}},
      {{{421,919},784}, {{511.13264109864355,546.43376318874562},5971}},
      {{{537,198},324}, {{512.46401906274821,528.50007942811749},6295}},
      {{{315,370},413}, {{500.30649970184857,518.74150268336325},6708}},
      {{{526,91},980},  {{503.58168574401657,464.21670135275747},7688}},
      {{{956,873},862}, {{549.19391812865490,505.42970760233919},8550}},
      {{{170,996},281}, {{537.12807156607414,521.03951987317419},8831}}
   };
    
   // How I got the test numbers. (Perhaps I will need to recreate some day.)
   //
   // First I created random triplets: x, y coordinates and mass
   //  for(int i=0; i<20; i++) {
   //      auto a = std::rand()%1000;
   //      auto b = std::rand()%1000;
   //      auto c = std::rand()%1000;
   //      std::cout << "{{{" << a << "," << b << "}," << c << "}, {{0,0},0}}," << std::endl;
   //  }
   //
   // Then I calculated in the by-definition way centres of mass after adding each mass
   //for(int i=0; i<20; i++) {
   //    mzlib::cmass_centre expected;
   //    for(int j=0; j<=i; j++) {
   //        expected.add_mass(test_mass_data[j].mass_centre.get_mass());
   //    }
   //    for(int j=0; j<=i; j++) {
   //        auto r = test_mass_data[j].mass_centre.get_mass()/expected.get_mass();
   //        expected.add_location(r*test_mass_data[j].mass_centre.get_location());
   //    }
   //    auto a = test_mass_data[i].mass_centre.get_location()[0];
   //    auto b = test_mass_data[i].mass_centre.get_location()[1];
   //    auto c = test_mass_data[i].mass_centre.get_mass();
   //    auto d = expected.get_location()[0];
   //    auto e = expected.get_location()[1];
   //    auto f = expected.get_mass();
   //    std::cout.precision(17);
   //    std::cout << "{{{" << a << "," << b << "}," << c << "}, {{" << d << "," << e << "}," << f << "}}," << std::endl;
   //}
        
   mzlib::mass_centre2d mc;
   for (auto test_mass : test_mass_data) {
      add_to_mass_centre(mc, test_mass.mass_centre);
      ASSERT_NEAR(test_mass.average_now.location[0], mc.location[0], 0.00001);
      ASSERT_NEAR(test_mass.average_now.location[1], mc.location[1], 0.00001);
      ASSERT_NEAR(test_mass.average_now.mass, mc.mass, 0.00001);
   }
}

TEST(mass_centre, remove_from_mass_centre) 
{
   struct t_centres_of_mass {
      mzlib::mass_centre2d mass_centre;
      mzlib::mass_centre2d average_now;
   } test_mass_data[] = {
      // Values are slightly different than in add part of the operation.
      // The precision errors creep into the calculation when removing mass centres
      {{{383,886},777}, {{383,886.00000000000125},777}},
      {{{915,793},335}, {{543.26978417266196,857.98291366906562},1112}},
      {{{386,492},649}, {{485.30948324815449,723.10335036910897},1761}},
      {{{421,362},27}, {{484.33836689038031,717.6504474272931},1788}},
      {{{690,59},763}, {{545.85143081144645,520.64915719325745},2551}},
      {{{926,540},426}, {{600.24958011420892,523.41820624790057},2977}},
      {{{172,736},211}, {{571.90558343789212,537.48808030112923},3188}},
      {{{368,567},429}, {{547.72103953552664,540.98838816698913},3617}},
      {{{782,530},862}, {{592.80888591203393,538.87363250725605},4479}},
      {{{123,67},135}, {{579.06285218899006,525.06718682271355},4614}},
      {{{929,802},22}, {{580.72346850733402,526.38136324417599},4636}},
      {{{58,69},167}, {{562.54840724547171,510.47824276493856},4803}},
      {{{393,456},11}, {{562.16098878271714,510.35375986705441},4814}},
      {{{42,229},373}, {{524.7559282822441,490.12145748987854},5187}},
      {{{421,919},784}, {{511.13264109864355,546.43376318874562},5971}},
      {{{537,198},324}, {{512.46401906274821,528.50007942811749},6295}},
      {{{315,370},413}, {{500.30649970184857,518.74150268336325},6708}},
      {{{526,91},980}, {{503.58168574401657,464.21670135275747},7688}},
      {{{956,873},862}, {{549.1939181286549,505.42970760233919},8550}},
      {{{170,996},281}, {{537.12807156607414,521.03951987317419},8831}}
   };
      
   size_t test_data_last_index = std::extent<decltype(test_mass_data)>::value-1;
   mzlib::mass_centre2d mc = test_mass_data[test_data_last_index].average_now;
   for(size_t index = test_data_last_index; index > 0; --index) {
      remove_from_mass_centre(mc, test_mass_data[index].mass_centre);
      // can't test with ASSERT_DOUBLE_EQ even with fudging the data, because release build will
      // calculate slightly different values than debug.
      ASSERT_NEAR(test_mass_data[index-1].average_now.location[0], mc.location[0], 1e-12);
      ASSERT_NEAR(test_mass_data[index-1].average_now.location[1], mc.location[1], 1e-12);
      ASSERT_DOUBLE_EQ(test_mass_data[index-1].average_now.mass, mc.mass);
   }
}

TEST(mass_centre, add_to_mass_centre_initialised_with_zero_mass) 
{
   mzlib::mass_centre2d mass_centre;
   mass_centre.location = {50,50}; // some location
   mass_centre.mass = 0; // zero mass
   
   add_to_mass_centre(mass_centre, {{10,10},10}); // add some non-zero mass
   
   // mass center should assume new body location and mass, regardless of what the location has been before
   ASSERT_EQ(mass_centre.location, mzlib::vector2d({10,10}));
   ASSERT_DOUBLE_EQ(mass_centre.mass, 10);
}