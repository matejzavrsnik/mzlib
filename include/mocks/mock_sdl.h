//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//
// Contains gmocks for testing stuff build on top of SDL2 library

#ifndef MZLIB_MOCK_SDL_H
#define	MZLIB_MOCK_SDL_H

// Fake included SDL2 files
#define _SDL_H
#define _SDL_IMAGE_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <functional>

// Types
typedef int8_t Sint8;
typedef uint8_t Uint8;
typedef int16_t Sint16;
typedef uint16_t Uint16;
typedef int32_t Sint32;
typedef uint32_t Uint32;
typedef int64_t Sint64;
typedef uint64_t Uint64;

// Enums
typedef enum { 
   SDL_FLIP_NONE = 0x00000000, 
   SDL_FLIP_HORIZONTAL = 0x00000001,
   SDL_FLIP_VERTICAL = 0x00000002 } SDL_RendererFlip;
typedef enum {
   SDL_FALSE = 0,
   SDL_TRUE = 1 } SDL_bool;
   
// Structs
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

int SDL_DestroyTexture(SDL_Texture* texture) { return _SDL_DestroyTexture(texture); }  
SDL_Surface* IMG_Load(const char *file) { return _IMG_Load(file); }
char* IMG_GetError() { return _IMG_GetError(); }
Uint32 SDL_MapRGB(const SDL_PixelFormat* format, Uint8 r, Uint8 g, Uint8 b) { return _SDL_MapRGB(format, r, g, b); }
int SDL_SetColorKey(SDL_Surface* surface, int flag, Uint32 key) { return _SDL_SetColorKey(surface, flag, key); }
SDL_Texture* SDL_CreateTextureFromSurface(SDL_Renderer* renderer, SDL_Surface* surface) { return _SDL_CreateTextureFromSurface(renderer, surface); }
char* SDL_GetError() { return _SDL_GetError(); }
int SDL_FreeSurface(SDL_Surface* surface) { return _SDL_FreeSurface(surface); }
int SDL_RenderCopyEx(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip) { return SDL_RenderCopyEx( renderer, texture, srcrect, dstrect, angle, center, flip); }

#endif /*MZLIB_MOCK_SDL_H*/