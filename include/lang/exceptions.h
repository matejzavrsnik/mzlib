//
// Copyright (c) 2016 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_EXCEPTIONS_H
#define	MZLIB_EXCEPTIONS_H

#include <exception>
#include <string>

namespace mzlib {

// purpose of this nested namespace: it better explains the purpose of these class
// names when used in code. is_empty on itself means nothing, exception::is_empty
// does. To make it more readable using other means I would need to prepend
// "exception" to every class name, but that is better done using nested namespace.
namespace exception {

class generic : public std::exception
{

private:

   std::string m_explanation;

public:
   
   generic() 
   {
   }
   
   explicit generic(std::string_view explanation)
      : m_explanation(explanation) 
   {
   }
   
   const char* what() const noexcept override
   { 
      return m_explanation.c_str();
   }
};
   
class is_empty        : public generic { public: using generic::generic; };
class not_set         : public generic { public: using generic::generic; };
class not_found       : public generic { public: using generic::generic; };
class invalid_values  : public generic { public: using generic::generic; };
class not_implemented : public generic { public: using generic::generic; };
class meaningless     : public generic { public: using generic::generic; };
class out_of_range    : public generic { public: using generic::generic; };
class parse_error     : public generic { public: using generic::generic; };

} } // namespace

#endif /* MZLIB_EXCEPTIONS_H */

