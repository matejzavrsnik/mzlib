//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_EXTENSTION_SDL_IMAGE_TEXTURE_H
#define	MZLIB_EXTENSTION_SDL_IMAGE_TEXTURE_H

// if included SDL.h and SDL_image.h from SDL2 library
#if defined(_SDL_H) && defined(_SDL_IMAGE_H)

#include "sdl_exceptions.h"
#include <string>
#include <memory>

namespace mzlib {

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
   
   void set_image(std::string_view image_path)
   {
      m_image_path = image_path;
      cleanup();
      load_image();
   }
   
   void load_image()
   {
      std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> 
         loaded_surface( IMG_Load( m_image_path.c_str() ), &SDL_FreeSurface);
      if (loaded_surface == nullptr) {
         const auto error = IMG_GetError();
         throw mzlib::exception::sdl::image_load_failure(error);
      }
      else {
         SDL_SetColorKey( loaded_surface.get(), SDL_TRUE, SDL_MapRGB( loaded_surface->format, 0, 0x00, 0x00 ) );
         if(!m_renderer) {
            throw mzlib::exception::sdl::texture_create_failure("Renderer not set");
         }
         m_texture = SDL_CreateTextureFromSurface( m_renderer, loaded_surface.get() );
         
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
   
  
   std::string m_image_path;
   uint m_image_width = 0;
   uint m_image_height = 0;
   SDL_Renderer* m_renderer = nullptr;
   SDL_Texture* m_texture = nullptr;
           
};
   
} // namespace

#endif

#endif // MZLIB_EXTENSTION_SDL_IMAGE_TEXTURE_H
