//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_SDL_RAII_H
#define MZLIB_SDL_RAII_H

// This file requires that <SDL2/SDL.h> is included.
#if defined(SDL_h_)

#include <string>
#include <extension/sdl/sdl_exceptions.h>

namespace mzlib
{

// Purpose: give raii capabilities to SDL init/destroy procedures
class sdl_init
{

public:

   explicit sdl_init(std::string_view title)
   {
      // (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
      // depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)
      if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
      {
         throw mzlib::exception::sdl::init_failure(std::string("error: ") + SDL_GetError());
      }

      // Decide GL+GLSL versions
      #ifdef __APPLE__
         // GL 3.2 Core + GLSL 150
         m_glsl_version = "#version 150";
         SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
         SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
         SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
         SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
      #else
         // GL 3.0 + GLSL 130
         m_glsl_version = "#version 130";
         SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
         SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
         SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
         SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
      #endif

      // Create window with graphics context
      SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
      SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
      SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
      auto window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_ALWAYS_ON_TOP /*| SDL_WINDOW_FULLSCREEN_DESKTOP*/);
      m_sdl_window = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
      m_sdl_gl_context = SDL_GL_CreateContext(m_sdl_window);
      SDL_GL_MakeCurrent(m_sdl_window, m_sdl_gl_context);
      SDL_GL_SetSwapInterval(1); // Enable vsync
   }

   ~sdl_init()
   {
      SDL_GL_DeleteContext(m_sdl_gl_context);
      SDL_DestroyWindow(m_sdl_window);
      SDL_Quit();
   }

   SDL_GLContext get_context()
   {
      return m_sdl_gl_context;
   }

   SDL_Window* get_window()
   {
      return m_sdl_window;
   }

   const char* get_glsl_version()
   {
      return m_glsl_version.data();
   }

private:

   SDL_GLContext m_sdl_gl_context;
   SDL_Window* m_sdl_window;
   std::string_view m_glsl_version;

};

}

#endif // defined(SDL_h_)

#endif // MZLIB_SDL_RAII_H