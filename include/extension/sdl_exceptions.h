//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_SDL_EXCEPTIONS_H
#define	MZLIB_SDL_EXCEPTIONS_H

// if included SDL.h and SDL_image.h from SDL2 library
#if defined(_SDL_H) && defined(_SDL_IMAGE_H)

#include "../lang/exceptions.h"

namespace mzlib {

namespace exception { namespace sdl {
   class sdl : public mzlib::exception::generic { public: using generic::generic; };
   class render_failure : public sdl { public: using sdl::sdl; };
   class image_load_failure : public sdl { public: using sdl::sdl; };
   class texture_create_failure : public sdl { public: using sdl::sdl; };
}}
   
} // namespace

#endif

#endif // MZLIB_SDL_EXCEPTIONS_H
