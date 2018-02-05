//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "../mocks/mock_sdl.h"
#include "sdl_image_texture.h"

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