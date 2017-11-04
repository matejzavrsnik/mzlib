//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_FILENAMEARISE_H
#define MZLIB_FILENAMEARISE_H

namespace mzlib {

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

} // namespace

#endif // MZLIB_FILENAMEARISE_H

#ifdef MZLIB_FILENAMEARISE_TESTS_H
#undef MZLIB_FILENAMEARISE_TESTS_H

// Has no tests yet

#endif // MZLIB_FILENAMEARISE_TESTS_H


