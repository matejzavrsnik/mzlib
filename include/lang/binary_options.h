//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_BINARY_OPTIONS_H
#define	MZLIB_BINARY_OPTIONS_H

// More readable substitutes for simple booleans for specific meanings.
// Let's see if I am correct in that I'll need more of them in the future and that
// they'll make reading my programs a joyful experience.

namespace mzlib {
namespace option {
   
class binary_option
{
   
public:
   
   enum /*not class*/ named_options { no, yes } m_named_value = no;

   binary_option () : 
      m_named_value(no)
   {
   }
   
   // create from option
   binary_option (named_options named_value) : 
      m_named_value(named_value)
   {
   }
   
   // compare to option
   bool operator== (named_options named_value) const
   {
      return m_named_value == named_value;
   }

   // convert from bool
   binary_option (bool boolean_value) :
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
class name : public binary_option \
{ \
public: \
   using binary_option::binary_option; \
};

MZLIB_GENERATE_NEW_BINARY_OPTION( recursive      )
MZLIB_GENERATE_NEW_BINARY_OPTION( include_hidden )
MZLIB_GENERATE_NEW_BINARY_OPTION( set            )
MZLIB_GENERATE_NEW_BINARY_OPTION( exists         )
MZLIB_GENERATE_NEW_BINARY_OPTION( removed        )
MZLIB_GENERATE_NEW_BINARY_OPTION( expanded       )
MZLIB_GENERATE_NEW_BINARY_OPTION( changed        )
MZLIB_GENERATE_NEW_BINARY_OPTION( stop           )
MZLIB_GENERATE_NEW_BINARY_OPTION( fullscreen     )
MZLIB_GENERATE_NEW_BINARY_OPTION( success        )
MZLIB_GENERATE_NEW_BINARY_OPTION( descending     )
MZLIB_GENERATE_NEW_BINARY_OPTION( forward        )
MZLIB_GENERATE_NEW_BINARY_OPTION( match          )
MZLIB_GENERATE_NEW_BINARY_OPTION( alphanumeric   )
MZLIB_GENERATE_NEW_BINARY_OPTION( case_sensitive )
        
// Did you come here to add something like larger/smaller option? Think again. 
// Imagine the function that takes type larger as an argument. The meaning of 
// larger::yes is clear, but larger::no is not; does the function interpret it 
// as "equal" or as "smaller"? For this case I would need to limit the user to 
// larger/equal/smaller options, not larger::yes/larger::no, because they are 
// really not that binary, that's why it doesn't fit in. Just add a new enum 
// somewhere, they are free.
        
// Shouldn't undefine this macro. Users need convenient way to create more.
// Not every option will make sense globally, to be included here.
//#undef MZLIB_GENERATE_NEW_BINARY_OPTION

}} // namespace

#endif	/* MZLIB_BINARY_OPTIONS_H */

