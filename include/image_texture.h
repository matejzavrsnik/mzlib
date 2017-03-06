//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_IMAGE_TEXTURE_H
#define	MZLIB_IMAGE_TEXTURE_H

// if included SDL.h and SDL_image.h from SDL2 library
#if defined(_SDL_H) && defined(_SDL_IMAGE_H)

#include "exceptions.h"
#include "pointer_wrapper.h"
#include <string>

namespace mzlib {

namespace exception { namespace sdl {
   class sdl : public mzlib::exception::generic { public: using generic::generic; };
   class render_failure : public sdl { public: using sdl::sdl; };
   class image_load_failure : public sdl { public: using sdl::sdl; };
   class texture_create_failure : public sdl { public: using sdl::sdl; };
}}

// Purpose of this class is to be a wrapper for SDL library's SDL_Texture that
// defines moving and copying. SDL only exposes C API.
class image_texture 
{

public:
   
   image_texture ()
   {
   }
   
   virtual ~image_texture()
   {
      cleanup();
   }
   
   image_texture& operator= (const image_texture& from)
   {
      if (this != &from) {
         copy_into_me(from);
         load_image();
      }
      return *this;
   }
   
   image_texture (const image_texture& from)
   {
      copy_into_me(from);
      load_image();
   }
   
   image_texture (image_texture&& from) 
   {
      move_into_me(std::move(from));
   }
   
   image_texture& operator= (image_texture&& from)
   {
      if (this != &from) {
         move_into_me(std::move(from));
      }
      return *this;
   }
   
   void set_image(std::string image_path)
   {
      m_image_path = image_path;
      cleanup();
      load_image();
   }
   
   void load_image()
   {
      pointer_wrapper<SDL_Surface, free_surface> loaded_surface = IMG_Load( m_image_path.c_str() );
      if (loaded_surface == nullptr) {
         const auto error = IMG_GetError();
         throw mzlib::exception::sdl::image_load_failure(error);
      }
      else {
         SDL_SetColorKey( loaded_surface, SDL_TRUE, SDL_MapRGB( loaded_surface->format, 0, 0x00, 0x00 ) );
         if(!m_renderer) {
            throw mzlib::exception::sdl::texture_create_failure("Renderer not set");
         }
         m_texture = SDL_CreateTextureFromSurface( m_renderer, loaded_surface );
         
         if (m_texture == nullptr) {
            const auto error = SDL_GetError();
            throw mzlib::exception::sdl::texture_create_failure(error);
         }
         else {
            m_image_width = loaded_surface->w;
            m_image_height = loaded_surface->h;
         }
      }
   }
   
   void render( int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE )
   {
      SDL_Rect render_quad = { x, y, (int)m_image_width, (int)m_image_height };

      if (clip != nullptr) {
         render_quad.w = clip->w;
         render_quad.h = clip->h;
      }

      // Renders to screen
      if (-1 == SDL_RenderCopyEx( m_renderer, m_texture, clip, &render_quad, angle, center, flip )) {
         auto error = SDL_GetError();
         throw mzlib::exception::sdl::render_failure(error);
      }
   }
   
   void set_renderer(SDL_Renderer* renderer)
   {
      m_renderer = renderer;
   }
   
private:
   
   void cleanup()
   {
      if( m_texture != nullptr )
      {
         SDL_DestroyTexture( m_texture );
         m_texture = nullptr;
         m_image_width = 0;
         m_image_height = 0;
      }
   }
   
   void move_into_me (image_texture&& from)
   {
      m_image_path = std::move(from.m_image_path);
      m_image_height = from.m_image_height;
      m_image_width = from.m_image_width;
      m_renderer = from.m_renderer;
      m_texture = from.m_texture;
      
      from.m_texture = nullptr;
      // leave renderer alone, it's shared across all texture instances
      //from.m_renderer = nullptr;      
   }

   void copy_into_me (const image_texture& from)
   {
      m_image_path = from.m_image_path;
      m_image_height = from.m_image_height;
      m_image_width = from.m_image_width;
      m_renderer = from.m_renderer;
      // don't copy from.m_texture pointer
   }
   
   // This function is only needed because I used pointer wrapper that takes as
   // a template parameter a function which destroys pointer. As I didn't know
   // how to write a template parameter type so that a function can return any
   // data type or void, I needed to change the signature of this call so that
   // it is compatible with void(*func)(type*). When I learn more about templates
   // I will do this last step.
   static void free_surface(SDL_Surface* surface)
   {
      SDL_FreeSurface (surface);
   }
   
   std::string m_image_path;
   uint m_image_width = 0;
   uint m_image_height = 0;
   SDL_Renderer* m_renderer = nullptr;
   SDL_Texture* m_texture = nullptr;
           
};
   
} // namespace

#endif


#endif	/* MZLIB_IMAGE_TEXTURE_H */

