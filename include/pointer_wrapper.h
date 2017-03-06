//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com

#ifndef MZLIB_POINTER_WRAPPER_H
#define	MZLIB_POINTER_WRAPPER_H

namespace mzlib {

// A thin wrapper over any pointer type that needs to run some cleanup function
// after not needed anymore. Useful in cases you need to deal with C-style API
// where you need to be careful that returned pointers are properly cleaned
// and you want to use them in object-oriented context.
template<class Type, void(*CleanupFunction)(Type*)>
class pointer_wrapper
{
   
private:
   
   Type* m_pointer;
   
   void move_into_me (pointer_wrapper&& from)
   {
      m_pointer = from.m_pointer;
      from.m_pointer = nullptr;   
   }

   void copy_into_me (const pointer_wrapper& from)
   {
      m_pointer = from.m_pointer;
   }
   
public:
   
   pointer_wrapper(Type* surface)
      : m_pointer(surface) 
   {
   }
      
   pointer_wrapper& operator= (Type* const from)
   {
      if (this != &from) {
         copy_into_me(from);
      }
      return *this;
   }
      
   pointer_wrapper& operator= (const pointer_wrapper& from)
   {
      if (this != &from) {
         copy_into_me(from);
      }
      return *this;
   }
   
   pointer_wrapper (const pointer_wrapper& from)
   {
      copy_into_me(from);
   }
   
   pointer_wrapper (pointer_wrapper&& from) 
   {
      move_into_me(std::move(from));
   }
   
   pointer_wrapper& operator= (pointer_wrapper&& from)
   {
      if (this != &from) {
         move_into_me(std::move(from));
      }
      return *this;
   }
      
   ~pointer_wrapper() 
   { 
      if (m_pointer) {
         CleanupFunction (m_pointer);
      }
   }
   
   operator Type* const ()
   {
      return m_pointer;
   }
   
   Type* const operator-> ()
   {
      return m_pointer;
   }
};

} // namespace

#endif	/* MZLIB_POINTER_WRAPPER_H */

