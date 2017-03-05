//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#define _SDL_H
#define _SDL_IMAGE_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <functional>

// Required SDL2 mocks
typedef int8_t Sint8;
typedef uint8_t Uint8;
typedef int16_t Sint16;
typedef uint16_t Uint16;
typedef int32_t Sint32;
typedef uint32_t Uint32;
typedef int64_t Sint64;
typedef uint64_t Uint64;

typedef enum { 
   SDL_FLIP_NONE = 0x00000000, 
   SDL_FLIP_HORIZONTAL = 0x00000001,
   SDL_FLIP_VERTICAL = 0x00000002 } SDL_RendererFlip;
typedef enum {
   SDL_FALSE = 0,
   SDL_TRUE = 1 } SDL_bool;
   
struct SDL_Rect { int x, y, w, h; };
struct SDL_Point { int x, y; };
struct SDL_PixelFormat {};
struct SDL_Surface { SDL_PixelFormat* format; int w, h; };
struct SDL_Texture {};
struct SDL_Renderer {};

// I couldn't figure out why gmocked functions that return void keel over and
// die from segfault when called from tested code. And if I just change the return
// type to int, it works fine. Should really make a difference now, the code is
// tested and all, but still bothers me. I don't know what goes wrong there.

static std::function<int(SDL_Texture*)> _SDL_DestroyTexture; // SDL version returns void
static std::function<SDL_Surface*(const char *)> _IMG_Load;
static std::function<char*(void)> _IMG_GetError;
static std::function<Uint32(const SDL_PixelFormat*, Uint8, Uint8, Uint8)> _SDL_MapRGB;
static std::function<int(SDL_Surface*, int, Uint32)> _SDL_SetColorKey;
static std::function<SDL_Texture*(SDL_Renderer*, SDL_Surface*)> _SDL_CreateTextureFromSurface;
static std::function<char*(void)> _SDL_GetError;
static std::function<int(SDL_Surface*)> _SDL_FreeSurface; // SDL version returns void
static std::function<int(SDL_Renderer*, SDL_Texture*, const SDL_Rect*, const SDL_Rect*, const double, const SDL_Point*, const SDL_RendererFlip)> _SDL_RenderCopyEx;

class sdl_mock
{
public:
   sdl_mock() 
   { 
      _SDL_DestroyTexture = [this](SDL_Texture* texture) { return SDL_DestroyTexture(texture); };
      _IMG_Load = [this](const char* file) { return IMG_Load(file); }; 
      _IMG_GetError = [this](void) { return IMG_GetError(); }; 
      _SDL_MapRGB = [this](const SDL_PixelFormat* format, Uint8 r, Uint8 g, Uint8 b) { return SDL_MapRGB(format, r, g, b); };
      _SDL_SetColorKey = [this](SDL_Surface* surface, int flag, Uint32 key) { return SDL_SetColorKey(surface, flag, key); };
      _SDL_CreateTextureFromSurface = [this](SDL_Renderer* renderer, SDL_Surface* surface) { return SDL_CreateTextureFromSurface(renderer, surface); };
      _SDL_GetError = [this](void) { return SDL_GetError(); }; 
      _SDL_FreeSurface = [this](SDL_Surface* surface) { return SDL_FreeSurface(surface); };
      _SDL_RenderCopyEx = [this](SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip) { return SDL_RenderCopyEx( renderer, texture, srcrect, dstrect, angle, center, flip); };
   }

   ~sdl_mock() 
   { 
      _SDL_DestroyTexture = {};
      _IMG_Load = {};
      _IMG_GetError = {};
      _SDL_MapRGB = {};
      _SDL_SetColorKey = {};
      _SDL_CreateTextureFromSurface = {};
      _SDL_GetError = {};
      _SDL_FreeSurface = {};
      _SDL_RenderCopyEx = {};
   }

   MOCK_METHOD1(SDL_DestroyTexture, int(SDL_Texture*));
   MOCK_METHOD1(IMG_Load, SDL_Surface*(const char*));
   MOCK_METHOD0(IMG_GetError, char*());
   MOCK_METHOD4(SDL_MapRGB, Uint32(const SDL_PixelFormat*, Uint8, Uint8, Uint8));
   MOCK_METHOD3(SDL_SetColorKey, int(SDL_Surface*, int, Uint32));
   MOCK_METHOD2(SDL_CreateTextureFromSurface, SDL_Texture*(SDL_Renderer*, SDL_Surface*));
   MOCK_METHOD0(SDL_GetError, char*());
   MOCK_METHOD1(SDL_FreeSurface, int(SDL_Surface*));
   MOCK_METHOD7(SDL_RenderCopyEx, int(SDL_Renderer*, SDL_Texture*, const SDL_Rect*, const SDL_Rect*, const double, const SDL_Point*, const SDL_RendererFlip));
};

int SDL_DestroyTexture(SDL_Texture* texture) { _SDL_DestroyTexture(texture); }  
SDL_Surface* IMG_Load(const char *file) { return _IMG_Load(file); }
char* IMG_GetError() { return _IMG_GetError(); }
Uint32 SDL_MapRGB(const SDL_PixelFormat* format, Uint8 r, Uint8 g, Uint8 b) { return _SDL_MapRGB(format, r, g, b); }
int SDL_SetColorKey(SDL_Surface* surface, int flag, Uint32 key) { return _SDL_SetColorKey(surface, flag, key); }
SDL_Texture* SDL_CreateTextureFromSurface(SDL_Renderer* renderer, SDL_Surface* surface) { return _SDL_CreateTextureFromSurface(renderer, surface); }
char* SDL_GetError() { return _SDL_GetError(); }
int SDL_FreeSurface(SDL_Surface* surface) { _SDL_FreeSurface(surface); }
int SDL_RenderCopyEx(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip) { return SDL_RenderCopyEx( renderer, texture, srcrect, dstrect, angle, center, flip); }

#include "../include/image_texture.h"

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
      EXPECT_CALL(m_sdl_mock, SDL_FreeSurface(&the_surface)).Times(1); // the surface is still cleaned
      EXPECT_CALL(m_sdl_mock, SDL_GetError()).WillOnce(Return(const_cast<char*>(error_text)));
   }
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