//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_TRY_CONVERT_TO_HAIKU_H
#define MZLIB_TRY_CONVERT_TO_HAIKU_H

#include "../apps/syllables.h"
#include "../tools/all_equal.h"

#include <string>
#include <array>

namespace mzlib {

struct haiku_conversion
{
   enum class e_status
   {
      succeeded,
      too_long,
      cant_fit,
      too_short,
      unknown_syllable_count
   };
   
   e_status status;
   std::string result;
};

namespace internal
{
   haiku_conversion success(std::string_view haiku)
   {
      haiku_conversion hc;
      hc.status = haiku_conversion::e_status::succeeded;
      hc.result = haiku;
      return hc;
   }
   
   haiku_conversion too_long(std::string_view haiku)
   {
      haiku_conversion hc;
      hc.status = haiku_conversion::e_status::too_long;
      hc.result = haiku;
      return hc;
   }   
   
   haiku_conversion cant_fit()
   {
      haiku_conversion hc;
      hc.status = haiku_conversion::e_status::cant_fit;
      return hc;
   }
   
   haiku_conversion too_short()
   {
      haiku_conversion hc;
      hc.status = haiku_conversion::e_status::too_short;
      return hc;
   }
   
   haiku_conversion unknown_syllable_count()
   {
      haiku_conversion hc;
      hc.status = haiku_conversion::e_status::unknown_syllable_count;
      return hc;
   }
}

haiku_conversion
try_convert_to_haiku(
   std::string_view candidate,
   const mzlib::syllables& syllables,
   std::array<int, 3> syllables_to_fill = {5,7,5})
{
   std::string haiku;
   
   int line = 0;
   for(const auto& word : split(candidate, " "))
   {
      if (word.empty()) 
         continue; // something wrong with split, but innocuous
      
      if (line>2) 
         return internal::too_long(haiku);
      
      std::optional<int> syl_count = syllables.count_word(word);
      if(syl_count)
      {
         syllables_to_fill[line] -= *syl_count;
         haiku += word;
      }
      else 
         return internal::unknown_syllable_count();
      
      if (syllables_to_fill[line] == 0)
      {
         ++line;
         haiku += '\n';
      }
      else if (syllables_to_fill[line] < 0)
         return internal::cant_fit();
      else
         haiku += " ";
   }
   
   if (all_equal(syllables_to_fill, 0))
      return internal::success(haiku);
   else
      return internal::too_short();
}

} // namespace

#endif /* MZLIB_TRY_CONVERT_TO_HAIKU_H */

