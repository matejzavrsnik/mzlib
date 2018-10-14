//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_SENTENCE_O_MATIC_FROM_FILE_H
#define MZLIB_SENTENCE_O_MATIC_FROM_FILE_H

#include "sentence_o_matic.h"

#include <fstream>

namespace mzlib {

// Consumes a file to create markov chain sentence generator
sentence_o_matic
sentence_o_matic_from_file(
   std::string_view file)
{
   sentence_o_matic_builder builder;
   std::string word;
   std::ifstream sourcetext_stream(file.data());
   do {
      sourcetext_stream >> word;
      builder.add_state(word);
   }
   while(sourcetext_stream);
   mzlib::sentence_o_matic sentence_o_matic(builder.wrap_up());
   return sentence_o_matic;
}

} // namespace
    
#endif /* MZLIB_SENTENCE_O_MATIC_FROM_FILE_H */
