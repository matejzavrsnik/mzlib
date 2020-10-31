//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

// this file requires that <imgui.h> is included from imgui library
#if defined(IMGUI_VERSION)

#include <string_view>

namespace mzlib
{

bool standalone_button(std::string_view button_text)
{
   bool show = true;
   bool pressed = false;
   auto flags_invisible_window =
      ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground |
      ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar |
      ImGuiWindowFlags_::ImGuiWindowFlags_NoResize;

   // I don't need window title here, but if left empty it crashes on Windows
   ImGui::Begin("_", &show, flags_invisible_window);

   if (ImGui::Button(button_text.data()))
      pressed = true;

   ImGui::End();
   return pressed;
}

}

#endif