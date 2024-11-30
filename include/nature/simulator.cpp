//
// Copyright (c) 2024 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "simulator.h"
#include "vector.h"
#include "../printers/print_generic.h"
#include "../printers/print_iterables.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <ranges>

#include "../grid/grid.h"

using namespace ::testing;
using namespace mzlib::simulator;


void
rabbit_business (
   std::shared_ptr<simtor> world,
   std::shared_ptr<simtor> me
) {
   // do I see a fox very near?
   // yes -> find optimal path away from fox, preferably to a group of rabbits
   // no -> eat grass; set rabbit hunger -= 0.5;
}

struct body_in_space {
   mzlib::vector2d location;
   mzlib::vector2d speed;
   double mass;
   double clock;
};

struct organism {
   enum class type {
      fox,
      rabbit
   } type;

   double hunger;
   bool alive;
};

void
foxy_business (
   std::shared_ptr<simtor> world,
   std::shared_ptr<simtor> me
) {
   // fox gets a bit hungrier every tick
   me->as<organism>().hunger += 0.1;

   // if still not hungry, sleep
   if (me->as<organism>().hunger < 2) {
      me->as<body_in_space>().speed = {0, 0};
      return;
   }

   // if hungry, the rabbits will matter
   auto rabbits =
      world->simtors
      | std::views::filter([] (std::shared_ptr<simtor> actor) {
         return actor->as<organism>().type == organism::type::rabbit;
      })
      | std::views::filter([] (std::shared_ptr<simtor> actor) {
         return actor->as<organism>().alive;
      })
      | std::ranges::to<std::vector>();

   // is it already running? fox moved in this tick
   if (mzlib::law::vector::length(me->as<body_in_space>().speed) > 0) {
      me->as<body_in_space>().location += me->as<body_in_space>().speed;
      me->as<body_in_space>().speed = {0, 0};
   }

   // what's the closest rabbit
   double smallest_distance = std::numeric_limits<double>::max();
   std::shared_ptr<simtor> closest_rabbit;
   for (auto rabbit : rabbits) {
      auto dist = mzlib::law::vector::distance(
         me->as<body_in_space>().location,
         rabbit->as<body_in_space>().location);
      if (dist < smallest_distance) {
         closest_rabbit = rabbit;
         smallest_distance = dist;
      }
   }

   // did I catch rabbit?
   if (smallest_distance < 0.5) {
      closest_rabbit->as<organism>().alive = false;
      me->as<organism>().hunger -= 5;
      return;
   }

   // start running towards the rabbit
   me->as<body_in_space>().speed =
      mzlib::law::vector::normalise(
         mzlib::law::vector::direction(
            me->as<body_in_space>().location,
            closest_rabbit->as<body_in_space>().location
         ));
}

mzlib::grid::type<std::string>
create_drawing (std::shared_ptr<simtor> meadow) {
   auto field = mzlib::grid::construct<std::string>(10, 10, "  ");
   for (auto simtor : meadow->simtors) {
      if (simtor->is<body_in_space>()
         && simtor->is<organism>()
         && (simtor->as<organism>().type == organism::type::rabbit
            || simtor->as<organism>().type == organism::type::fox)
      ) {
         std::string drawing =
            simtor->as<organism>().type == organism::type::fox
            ? "🦊"
            : simtor->as<organism>().alive
              ? "🐇"
              : "☠️";

         auto loc = simtor->as<body_in_space>().location;
         mzlib::grid::cell cell{long(loc[0]), long(loc[1])};
         mzlib::grid::access(field, cell) = drawing;
      }
   }
   return field;
}

TEST(simulator, meadow) {
   auto rabbit = std::make_shared<simtor>();
   rabbit->as<body_in_space>({
      .location = {5, 5},
      .speed = {0, 0},
      .mass = 1.0
   });
   rabbit->as<organism>({
      .type = organism::type::rabbit,
      .hunger = 0.0,
      .alive = true
   });
   rabbit->stabilise_me = rabbit_business;

   auto rabbit2 = std::make_shared<simtor>();
   rabbit2->as<body_in_space>({
      .location = {4, 4},
      .speed = {0, 0},
      .mass = 1.0
   });
   rabbit2->as<organism>({
      .type = organism::type::rabbit,
      .hunger = 0.0,
      .alive = true
   });
   rabbit2->stabilise_me = rabbit_business;

   auto fox = std::make_shared<simtor>();
   fox->as<body_in_space>({
      .location = {3, 7},
      .speed = {0, 0},
      .mass = 1.0
   });
   fox->as<organism>({
      .type = organism::type::fox,
      .hunger = 0.0,
      .alive = true
   });
   fox->stabilise_me = foxy_business;

   auto fox2 = std::make_shared<simtor>();
   fox2->as<body_in_space>({
      .location = {1, 1},
      .speed = {0, 0},
      .mass = 1.0
   });
   fox2->as<organism>({
      .type = organism::type::fox,
      .hunger = 1.0,
      .alive = true
   });
   fox2->stabilise_me = foxy_business;

   auto meadow = std::make_shared<simtor>();
   meadow->as<body_in_space>().clock = double(0.0);

   meadow->simtors.push_back(rabbit);
   meadow->simtors.push_back(rabbit2);
   meadow->simtors.push_back(fox);
   meadow->simtors.push_back(fox2);

   while (
      std::ranges::any_of(meadow->simtors,
         [] (std::shared_ptr<simtor> sim) {
            return
               sim->is<organism>()
               && sim->as<organism>().type == organism::type::rabbit
               && sim->as<organism>().alive;
         })) {
      meadow->as<body_in_space>().clock += 0.1;;
      meadow->stabilise(meadow, meadow);
      // uncommend below and see
      //mzlib::print(create_drawing(meadow));
   }

   ASSERT_TRUE(true);
}
