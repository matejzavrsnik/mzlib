//
// Copyright (c) 2021 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_METRONOME_H
#define MZLIB_METRONOME_H

#include <future>

namespace mzlib
{

/**
 * @brief A non-blocking timer which invokes a signal on a set_or_add period.
 * @details Signal will be invoked from another thread so make necessary arrangements if this is going to
 * be a problem. For example, Qt widgets can't be signalled safely from another thread.
 * Destructor will stop the timer.
 * @tparam Signal Any signal/slot facility that can be invoke a signal by operator().
 * @example
 * Following example is using sigslot library for signal/slot.
 * \code{.cpp}
 * struct clock
 * {
 *   metronome &lt;sigslot::signal&lt;>> m_timer;
 *
 *   clock() {
 *     m_timer.tick.connect(&clock::tick, this);
 *     m_timer.start(1000ms);
 *   }
 *
 *   void tick () {
 *     cout << "A second has passed." << endl;
 *   }
 * };
 * \endcode
 */
template <typename Signal>
class metronome
{

public:

   Signal tick;

   void
   start (std::chrono::milliseconds period)
   {
      m_stop = false;
      m_ftr = std::async(std::launch::async, &metronome::runner, this, period);
   }

   void
   stop ()
   {
      m_stop = true;
   }

   ~metronome ()
   {
      stop();
   }

private:

   bool m_stop;
   std::future<void> m_ftr; // future needs to outlive scope of std::async otherwise dtor will block

   void
   runner (std::chrono::milliseconds period)
   {
      while (!m_stop)
      {
         std::this_thread::sleep_for(period);
         if (!m_stop)
            tick();
      }
   }
};

} // namespace

#endif	/* MZLIB_METRONOME_H */

