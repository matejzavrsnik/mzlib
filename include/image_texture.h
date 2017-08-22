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

#include "lang/exceptions.h"
#include <string>
#include <memory>

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

#ifdef MZLIB_BUILDING_TESTS

using namespace ::testing;

class fixture_image_texture : public ::testing::Test 
{

protected:
   
   fixture_image_texture () {}
   virtual ~fixture_image_texture () {}
   virtual void SetUp() {}
   virtual void TearDown() {}
   
   NiceMock<sdl_mock> m_sdl_mock;
   
   SDL_Surface* null_surface = nullptr;
   SDL_Surface the_surface, the_other_surface;
   SDL_Texture* null_texture = nullptr;
   SDL_Texture the_texture, the_other_texture;
   SDL_Renderer* null_renderer = nullptr;
   SDL_Renderer the_renderer;
   const char* image_file_path = "fake image path";
   const char* error_text = "this particular error text";
};

TEST_F(fixture_image_texture, if_image_load_failed_it_throws_an_exception_with_sdl_error_message) 
{
   {
      InSequence dummy;
      EXPECT_CALL(m_sdl_mock, IMG_Load(_)).WillOnce(Return(null_surface));
      EXPECT_CALL(m_sdl_mock, IMG_GetError()).WillOnce(Return(const_cast<char*>(error_text)));
   }
   mzlib::image_texture texture;
   try {
      texture.set_image(image_file_path);
      FAIL(); // should've thrown
   }
   catch (mzlib::exception::sdl::image_load_failure& e) {
      ASSERT_STREQ(error_text, e.what());
   }
}

TEST_F(fixture_image_texture, if_renderer_not_set_load_image_fails_with_correct_exception) 
{
   {
      InSequence dummy;
      EXPECT_CALL(m_sdl_mock, IMG_Load(_)).WillOnce(Return(&the_surface));
      EXPECT_CALL(m_sdl_mock, SDL_FreeSurface(&the_surface)).Times(1); // the surface is still cleaned
   }
   mzlib::image_texture texture;
   ASSERT_THROW(texture.set_image(image_file_path), mzlib::exception::sdl::texture_create_failure);
}

TEST_F(fixture_image_texture, create_texture_fails_with_predictable_exception) 
{
   {
      InSequence dummy;
      EXPECT_CALL(m_sdl_mock, IMG_Load(_)).WillOnce(Return(&the_surface));
      EXPECT_CALL(m_sdl_mock, SDL_CreateTextureFromSurface(_,_)).WillOnce(Return(null_texture));
      EXPECT_CALL(m_sdl_mock, SDL_GetError()).WillOnce(Return(const_cast<char*>(error_text)));
   }
   EXPECT_CALL(m_sdl_mock, SDL_FreeSurface(&the_surface)).Times(1); // the surface is still cleaned
   mzlib::image_texture texture;
   texture.set_renderer(&the_renderer);
   try {
      texture.set_image(image_file_path);
      FAIL(); // should've thrown
   }
   catch (mzlib::exception::sdl::texture_create_failure& e) {
      ASSERT_STREQ(error_text, e.what());
   }

}

TEST_F(fixture_image_texture, if_create_texture_succeeds_surface_is_freed) 
{
   {
      InSequence dummy;
      EXPECT_CALL(m_sdl_mock, IMG_Load(_)).WillOnce(Return(&the_surface));
      EXPECT_CALL(m_sdl_mock, SDL_CreateTextureFromSurface(_,_)).WillOnce(Return(&the_texture));
      EXPECT_CALL(m_sdl_mock, SDL_FreeSurface(&the_surface)).Times(1); // the surface is still cleaned
   }
   mzlib::image_texture texture;
   texture.set_renderer(&the_renderer);
   texture.set_image(image_file_path);
}

TEST_F(fixture_image_texture, destructor_doesnt_destroy_texture_if_image_not_loaded) 
{
   EXPECT_CALL(m_sdl_mock, IMG_Load(_)).Times(0);
   EXPECT_CALL(m_sdl_mock, SDL_DestroyTexture(_)).Times(0);
   {
      mzlib::image_texture texture;
      // image not loaded, texture wasn't really created, no need to destroy it
   }
}

TEST_F(fixture_image_texture, destructor_doesnt_destroy_texture_if_image_load_failed) 
{
   {
      InSequence dummy;
      EXPECT_CALL(m_sdl_mock, IMG_Load(Pointee(*image_file_path))).WillOnce(Return(null_surface));
      EXPECT_CALL(m_sdl_mock, IMG_GetError()).WillOnce(Return(const_cast<char*>(error_text)));
   }
   EXPECT_CALL(m_sdl_mock, SDL_DestroyTexture(_)).Times(0);
   {
      mzlib::image_texture texture;
      ASSERT_THROW(texture.set_image(image_file_path), mzlib::exception::sdl::image_load_failure);
   }   
}

TEST_F(fixture_image_texture, on_move_constructed_destructor_doesnt_destroy_texture_in_both) 
{
   {
      InSequence dummy;
      EXPECT_CALL(m_sdl_mock, IMG_Load(_)).WillOnce(Return(&the_surface));
      EXPECT_CALL(m_sdl_mock, SDL_CreateTextureFromSurface(_,_)).WillOnce(Return(&the_texture));
   }
   
   EXPECT_CALL(m_sdl_mock, SDL_DestroyTexture(_)).Times(1);
   mzlib::image_texture texture; // created
   texture.set_renderer(&the_renderer);
   texture.set_image(image_file_path);
   mzlib::image_texture moved_texture(std::move(texture)); // move-constructed
   // Destroyed just once, because the texture has been moved to another
   // object and it would be incorrect to destroy it on move. 
}

TEST_F(fixture_image_texture, on_copy_constructed_will_reload_image_again_and_eventually_destroy_both_textures) 
{
   {
      InSequence dummy;
      EXPECT_CALL(m_sdl_mock, IMG_Load(Pointee(*image_file_path))).WillOnce(Return(&the_surface));
      EXPECT_CALL(m_sdl_mock, SDL_CreateTextureFromSurface(_,_)).WillOnce(Return(&the_texture));
      EXPECT_CALL(m_sdl_mock, IMG_Load(Pointee(*image_file_path))).WillOnce(Return(&the_other_surface));
      EXPECT_CALL(m_sdl_mock, SDL_CreateTextureFromSurface(_,_)).WillOnce(Return(&the_other_texture));
   }
   
   EXPECT_CALL(m_sdl_mock, SDL_DestroyTexture(&the_texture)).Times(1);
   EXPECT_CALL(m_sdl_mock, SDL_DestroyTexture(&the_other_texture)).Times(1);
   
   mzlib::image_texture texture; // created
   texture.set_renderer(&the_renderer);
   texture.set_image(image_file_path);
   mzlib::image_texture copied_texture(texture); // copy-constructed
   // Destroyed just twice, because the texture has been recreated from the same
   // image file again for the copy. 
}

TEST_F(fixture_image_texture, on_move_assigned_destructor_doesnt_destroy_texture_in_both) 
{
   {
      InSequence dummy;
      EXPECT_CALL(m_sdl_mock, IMG_Load(_)).WillOnce(Return(&the_surface));
      EXPECT_CALL(m_sdl_mock, SDL_CreateTextureFromSurface(_,_)).WillOnce(Return(&the_texture));
   }
   
   EXPECT_CALL(m_sdl_mock, SDL_DestroyTexture(_)).Times(1);
   mzlib::image_texture texture; // created
   texture.set_renderer(&the_renderer);
   texture.set_image(image_file_path);
   mzlib::image_texture moved_texture;
   moved_texture.operator=(std::move(texture)); // move-assigned
   // Destroyed just once, because the texture has been moved to another
   // object and it would be incorrect to destroy it on move. 
}

TEST_F(fixture_image_texture, on_copy_assigned_will_reload_image_again_and_eventually_destroy_both_textures) 
{
   {
      InSequence dummy;
      EXPECT_CALL(m_sdl_mock, IMG_Load(Pointee(*image_file_path))).WillOnce(Return(&the_surface));
      EXPECT_CALL(m_sdl_mock, SDL_CreateTextureFromSurface(_,_)).WillOnce(Return(&the_texture));
      EXPECT_CALL(m_sdl_mock, IMG_Load(Pointee(*image_file_path))).WillOnce(Return(&the_other_surface));
      EXPECT_CALL(m_sdl_mock, SDL_CreateTextureFromSurface(_,_)).WillOnce(Return(&the_other_texture));
   }
   
   EXPECT_CALL(m_sdl_mock, SDL_DestroyTexture(&the_texture)).Times(1);
   EXPECT_CALL(m_sdl_mock, SDL_DestroyTexture(&the_other_texture)).Times(1);
   
   mzlib::image_texture texture; // created
   texture.set_renderer(&the_renderer);
   texture.set_image(image_file_path);
   mzlib::image_texture copied_texture;
   copied_texture.operator=(texture); // copy-assigned
   // Destroyed just twice, because the texture has been recreated from the same
   // image file again for the copy. 
}

#endif // MZLIB_BUILDING_TESTS