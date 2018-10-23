//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_FILTER_HAIKUS_H
#define MZLIB_FILTER_HAIKUS_H

#include "../apps/syllables.h"
#include "../tools/rememberator.h"
#include "../tools/try_convert_to_haiku.h"
#include "../string/remove_words.h"

#include <istream>

namespace mzlib {

// filter out haikus from stream
template<typename T>
void filter_haikus(
   std::basic_istream<T>& input_stream,
   std::basic_ostream<T>& output_stream,
   const mzlib::syllables& syllables)
{
   rememberator<std::string> seen_haikus;
   std::string candidate;
   haiku_conversion haiku;
   std::string word;

   while(input_stream)
   {
      input_stream >> word;
      candidate += " " + word;

      haiku = try_convert_to_haiku(candidate, syllables);

      if (haiku.status == haiku_conversion::e_status::succeeded &&
          !seen_haikus.recall_remember(haiku.result))
      {
         output_stream << haiku.result << std::endl;
      }

      if (haiku.status != haiku_conversion::e_status::too_short)
      {
         candidate = mzlib::remove_words_beginning(candidate);
      }
   }
}

} // namespace

#endif /* MZLIB_FILTER_HAIKUS_H */
