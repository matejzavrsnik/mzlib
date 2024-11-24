
#include <iterator>

//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_COPY_ITERATORS_H
#define MZLIB_COPY_ITERATORS_H

namespace mzlib {

// Because std::copy assumes destination is at least as large as source.
// You could use copy_n, but for general case you would then need to call 
// std::min to determine which range is smaller and copy that much only.
// Seems a bit superfluous to call std::min in this case, when you can just
// check if any of the iterators are at position "last" instead of just the
// input range, as std::copy does. Or am I missing something?

// returns where it had to stop
template<class OutputIt, class InputIt>
struct copied
{
   InputIt input_it;
   OutputIt output_it;
};

template<class OutputIt, class InputIt>
constexpr copied<OutputIt, InputIt> copy(
   InputIt  in_first,  const InputIt  in_last,
   OutputIt out_first, const OutputIt out_last)
{
   while(out_first != out_last && in_first != in_last) {
      *out_first = *in_first;
      out_first = std::next(out_first);
      in_first = std::next(in_first);
   }
   return {in_first, out_first};
}

} // namespace

#endif // MZLIB_COPY_ITERATORS_H
