//
// Copyright (c) 2024 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <functional>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <ranges>
#include <any>

#include "../lang/exceptions.h"

namespace mzlib::simulator {
class simtor;

inline void
inert_behaviour (
   std::shared_ptr<simtor> world,
   std::shared_ptr<simtor> me
) {
   // do nothing
}


class simtor {
   template<typename Properties>
   Properties&
   access (const std::string property) {
      if (!properties.contains(property))
         throw mzlib::exception::not_set("no such property");

      if (!properties[property].has_value())
         throw mzlib::exception::not_set("no such property");

      try {
         return std::any_cast<Properties&>(properties[property]);
      }
      catch (std::bad_any_cast&) {
         throw mzlib::exception::not_set("not the right type");
      }
   }

   template<typename Properties>
   void
   add (Properties p) {
      auto property_name = typeid(Properties).name();
      properties.emplace(property_name, p);
   }

public:
   std::map<std::string, std::any> properties;
   std::vector<std::shared_ptr<simtor>> simtors;

   template<typename Properties>
   Properties&
   as () {
      const auto property_name = typeid(Properties).name();
      if (!properties.contains(property_name))
         add<Properties>(Properties());
      return access<Properties>(property_name);
   }

   template<typename Properties>
   bool
   is () const {
      const auto property_name = typeid(Properties).name();
      return properties.contains(property_name);
   }

   template<typename Properties>
   void
   as (Properties properties) {
      add(properties);
   }

   std::function<
      void (
         std::shared_ptr<simtor> world,
         std::shared_ptr<simtor> me
      )> stabilise_me = inert_behaviour;

   void
   stabilise (
      std::shared_ptr<simtor> world,
      std::shared_ptr<simtor> me
   ) {
      stabilise_me(world, me);
      stabilise_simtors(world);
   };

   void
   stabilise_simtors (
      std::shared_ptr<simtor> world
   ) {
      for (auto actor : simtors)
         actor->stabilise(world, actor);
   };
};
}

#endif //SIMULATOR_H
