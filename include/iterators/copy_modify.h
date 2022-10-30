//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef COPY_MODIFY_H
#define COPY_MODIFY_H

#include <algorithm>

namespace mzlib
{

// function to copy to another container after modifying each
// element using provided function

template<
   typename InputContainer,
   typename OutputContainer,
   typename ModifierFunction>
void copy_modify(
   const InputContainer& input,
   OutputContainer& output,
   ModifierFunction modifier)
{
   std::transform(
      input.begin(), 
      input.end(), 
      std::back_inserter(output), 
      modifier);
}
   
}

#endif /* COPY_MODIFY_H */

