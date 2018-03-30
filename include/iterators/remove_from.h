//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_REMOVE_FROM_H
#define MZLIB_REMOVE_FROM_H

#include "starts_with.h"
#include "../laws/set_intersection.h"

#include <functional>
#include <algorithm>

namespace mzlib {

template<class IteratorFull>
class remove_from
{
   using ValueType = typename IteratorFull::value_type;
   IteratorFull m_full_begin;
   IteratorFull m_full_end;
   enum class position {start, end} m_position;
   enum class modality {they_do, they_dont} m_modality;
   
public:
   
   remove_from(IteratorFull begin, IteratorFull end) :
      m_full_begin(begin),
      m_full_end(end),
      m_position(position::start),
      m_modality(modality::they_do)
   {}
   
   remove_from& which()
   {
      m_modality = modality::they_do;
      return *this;
   }
   
   remove_from& which_do_not()
   {
      m_modality = modality::they_dont;
      return *this;
   }
   
   remove_from& start()
   {
      m_position = position::start;
      return *this;
   }
   
   remove_from& end()
   {
      m_position = position::end;
      return *this;
   }
   
   
   template<class IteratorEdge>
   std::vector<ValueType> 
   with(IteratorEdge begin, IteratorEdge end)
   {
      switch(m_position) {
         case position::start:
            switch(m_modality) {
               case modality::they_do:
                  return do_start(begin, end);
                  break;
               case modality::they_dont:
                  return dont_start(begin, end);
                  break;
            }
            break;
         case position::end:
            switch(m_modality) {
               case modality::they_do:
                  return do_end(begin, end);
                  break;
               case modality::they_dont:
                  return dont_end(begin, end);
                  break;
            }
            break;
      }
   }
   
private:
   
   template<class IteratorEdge>
   std::vector<ValueType> 
   do_start(IteratorEdge begin, IteratorEdge end) 
   {
      std::vector<ValueType> result;
      for (auto full = m_full_begin; full != m_full_end; ++full) {
         bool goes_on_the_list = false;
         for (auto edge = begin; edge != end; ++edge) {
            if (starts_with_c(*full, *edge)) {
               goes_on_the_list = true;
               break;
            }
         }
         if(!goes_on_the_list) {
            result.push_back(*full);
         }
      };
      return result;
   }

   template<class IteratorEdge>
   std::vector<ValueType> 
   dont_start(IteratorEdge begin, IteratorEdge end) 
   {
      std::vector<ValueType> result;
      using ValueEdge = typename IteratorEdge::value_type;
      
      set_intersection_if(
         m_full_begin, m_full_end,
         begin, end,
         std::inserter(result, result.end()),
         starts_with_c<ValueType, ValueEdge>);
      
      return result;
   }

   template<class IteratorEdge>
   std::vector<ValueType> 
   do_end(IteratorEdge begin, IteratorEdge end) 
   {
      std::vector<ValueType> result;
      for (auto full = m_full_begin; full != m_full_end; ++full) {
         bool goes_on_the_list = false;
         for (auto edge = begin; edge != end; ++edge) {
            if (ends_with_c(*full, *edge)) {
               goes_on_the_list = true;
               break;
            }
         }
         if(!goes_on_the_list) {
            result.push_back(*full);
         }
      };
      return result;
   }

   template<class IteratorEdge>
   std::vector<ValueType> 
   dont_end(IteratorEdge begin, IteratorEdge end) 
   {
      std::vector<ValueType> result;
      using ValueEdge = typename IteratorEdge::value_type;
      
      set_intersection_if(
         m_full_begin, m_full_end,
         begin, end,
         std::inserter(result, result.end()),
         ends_with_c<ValueType, ValueEdge>);

      return result;
   }

};
   
} // namespace

#endif // MZLIB_REMOVE_FROM_H
