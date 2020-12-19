//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_REMOVE_ELEMENT_H
#define MZLIB_REMOVE_ELEMENT_H

#include <algorithm>

namespace mzlib {
    
/**
 * @brief Removes pointer to an element from a container of smart pointers
 * @tparam Container is any std compatible container that stores smart pointers, for example vector &lt; unique_ptr &lt; my_class>>
 * @tparam Element is a type that smart pointers in container are storing, for example my_class*
 * @example
 * \code{.cpp}
 * auto b_ptr = make_unique<my_class> (b);
 * vector &lt; unique_ptr &lt; my_class>> container {b_ptr};
 * remove_element_ptr (container, b_ptr.get());
 * \endcode
 */
template <typename Container, typename Element>
void
remove_element_ptr (
   Container& container, /**< [in/out] container from which a smart pointer to the element will be removed */
   const Element* const element /**< [in] pointer to element to be removed */
)
{
   container.erase(
      std::remove_if(
         std::begin(container), std::end(container), [&element] (const auto& contained_element)
         {
            return contained_element.get() == element;
         }
      ), std::end(container)
   );
}
    
} // namespace

#endif /* MZLIB_REMOVE_ELEMENT_H */
