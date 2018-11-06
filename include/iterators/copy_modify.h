//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef COPY_MODIFY_H
#define COPY_MODIFY_H

namespace mzlib
{

// function to copy to another container after modifying each
// element using provided function
   
template<
   typename InputIterator, 
   typename OutputIterator, 
   typename ModifierFunction>
void copy_modify(
   InputIterator begin,
   InputIterator end,
   OutputIterator output,
   ModifierFunction modifier)
{
   for(auto it=begin; it!=end; ++it)
      *output++ = modifier(*it);
}

template<
   typename InputContainer,
   typename OutputContainer,
   typename ModifierFunction>
void copy_modify(
   const InputContainer& input,
   OutputContainer& output,
   ModifierFunction modifier)
{
   copy_modify(
      input.begin(),
      input.end(),
      std::back_inserter(output),
      modifier);
}
   
}

#endif /* COPY_MODIFY_H */

