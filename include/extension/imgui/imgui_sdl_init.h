//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_IMGUI_SDL_RAII_H
#define MZLIB_IMGUI_SDL_RAII_H

// This file requires that <imgui.h> is included from imgui library.
#if defined(IMGUI_VERSION)

// Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
// This file requires that some common one (gl3w, glew, glad) is included
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W) || \
    defined(IMGUI_IMPL_OPENGL_LOADER_GLEW) || \
    defined(IMGUI_IMPL_OPENGL_LOADER_GLAD) || \
    defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2) || \
    defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2) || \
    defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3) || \
    defined(IMGUI_IMPL_OPENGL_LOADER_CUSTOM)

#include "../sdl/sdl_init.h"

namespace mzlib
{

// Purpose: give raii capabilities to imgui+sdl init/destroy procedures
class imgui_sdl_init
{
public:

   imgui_sdl_init(std::string_view window_title) :
      m_sdl(window_title)
   {
      // Initialize OpenGL loader
      #if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
         bool err = gl3wInit() != 0;
      #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
         bool err = glewInit() != GLEW_OK;
      #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
         bool err = gladLoadGL() == 0;
      #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
         bool err = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress) == 0; // glad2 recommend using the windowing library loader instead of the (optionally) bundled one.
      #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
         bool err = false;
         glbinding::Binding::initialize();
      #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
         bool err = false;
         glbinding::initialize([](const char* name) { return (glbinding::ProcAddress)SDL_GL_GetProcAddress(name); });
      #else
         bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
      #endif
      if (err)
      {
         throw mzlib::exception::sdl::init_failure("failed to initialize OpenGL loader.");
      }

      // Setup Dear ImGui context
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      //ImGuiIO& io = ImGui::GetIO(); (void)io;
      //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
      //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

      // Setup Dear ImGui style
      ImGui::StyleColorsDark();
      //ImGui::StyleColorsClassic();

      // Setup Platform/Renderer backends
      ImGui_ImplSDL2_InitForOpenGL(m_sdl.get_window(), m_sdl.get_context());
      ImGui_ImplOpenGL3_Init(m_sdl.get_glsl_version());

      // Load Fonts
      // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
      // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
      // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
      // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
      // - Read 'docs/FONTS.md' for more instructions and details.
      // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
      //io.Fonts->AddFontDefault();
      //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
      //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
      //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
      //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
      //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
      //IM_ASSERT(font != NULL);
   }

   ~imgui_sdl_init()
   {
      // Cleanup
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplSDL2_Shutdown();
      ImGui::DestroyContext();
   }

   void start_frame()
   {
      // Start the Dear ImGui frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplSDL2_NewFrame(m_sdl.get_window());
      ImGui::NewFrame();
   }

   void end_frame(const ImVec4& clear_color)
   {
      // Rendering
      ImGui::Render();

      // gl- prefixed functions are from openGL

      // the glViewport function sets the viewport. No clue what it does.
      // if I comment it out everything works the same.
      glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);

      // what color to clear the surface with
      glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

      // clears old surface, for example when resizing
      glClear(GL_COLOR_BUFFER_BIT); 

      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      SDL_GL_SwapWindow(m_sdl.get_window());
   }

   bool should_quit()
   {
     // Poll and handle events (inputs, window resize, etc.)
     // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
     // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
     // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
     // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
     SDL_Event event;
     while (SDL_PollEvent(&event))
     {
         ImGui_ImplSDL2_ProcessEvent(&event);
         if (event.type == SDL_QUIT)
             return true;
         if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(m_sdl.get_window()))
             return true;
     }
     return false;
   }

private:

   mzlib::sdl_init m_sdl;

};



}

#endif // MZLIB_IMGUI_SDL_RAII_H
#endif // defined(IMGUI_VERSION)
#endif // defined(IMGUI_IMPL_OPENGL_LOADER_GL3W) || ...