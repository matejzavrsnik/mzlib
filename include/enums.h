//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_ENUMS_H
#define	MZLIB_ENUMS_H

// More readable substitutes for simple booleans for specific meanings.
// Let's see if I am correct in that I'll need more of them in the future and that
// they'll make reading my programs a joyful experience.

namespace mzlib {
   
class cbinary_option
{
   
public:
   
   enum /*not class*/ named_options { no, yes } m_named_value = no;
  
   // create from option
   cbinary_option (named_options named_value) : 
      m_named_value(named_value)
   {
   }
   
   // compare to option
   bool operator== (named_options named_value) const
   {
      return m_named_value == named_value;
   }

   // convert from bool
   cbinary_option (bool boolean_value) :
      m_named_value(boolean_value ? yes : no)
   {
   }
   
   // convert to bool
   operator bool () const
   {
      return m_named_value == yes;
   }

};

// a generator to create real ones
#define MZLIB_GENERATE_NEW_BINARY_OPTION(name) \
class name : public cbinary_option \
{ \
public: \
   using cbinary_option::cbinary_option; \
};

MZLIB_GENERATE_NEW_BINARY_OPTION( erecursive      );
MZLIB_GENERATE_NEW_BINARY_OPTION( einclude_hidden );


// can't easily make this one work. Something with moves? Will solve when need be.
enum class eset { no, yes };

#undef MZLIB_GENERATE_NEW_BINARY_OPTION

} // namespace mzlib

#endif	/* MZLIB_ENUMS_H */

