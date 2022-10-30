//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include <functional>

#ifndef MZLIB_LOOP_H
#define	MZLIB_LOOP_H

namespace mzlib {

// You know that i in for loops that you never needed in the body of the loop
// because all you wanted was to run something N-times? Do you have irrational
// hatred of that i? Then this is a solution for you!

class loop;
   
// Not meant to be used directly
namespace internal 
{

class loop_runner_times
{

friend class mzlib::loop;

private:

   int m_times = 0;
   explicit loop_runner_times(int times) : m_times(times) {}

public:

   template <class Function, class... Args>
   void operator() (Function&& fun, Args&&... args) const
   {
      for (int i = 0; i < m_times; ++i)
         std::invoke(std::forward<Function>(fun), std::forward<Args>(args)...);
   }

};

template <typename Param>
class loop_runner_from_to
{

friend class mzlib::loop;

private:

   Param m_from, m_to;
   loop_runner_from_to(Param from, Param to) : m_from(from), m_to(to) {}

public:

   template <class Function>
   void operator() (Function&& fun) const
   {
      for (int parameter = m_from; parameter <= m_to; ++parameter)
         std::invoke(std::forward<Function>(fun), parameter);
   }

};

} // namespace internal

// It's a class instead of a namespace so that I can have private constructors 
// for various types of the loop
class loop
{

public:
   
   static const internal::loop_runner_times times(int t)
   {
      return internal::loop_runner_times(t);
   }

   template<typename Param>
   static const internal::loop_runner_from_to<Param> from_to(Param from, Param to)
   {
      return internal::loop_runner_from_to<Param>(from, to);
   }
};

} // namespace

#endif	/* MZLIB_LOOP_H */
