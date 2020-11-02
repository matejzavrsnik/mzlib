//
// Copyright (c) 2020 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

// this file requires that <imgui.h> is included from imgui library
#if defined(IMGUI_VERSION)

#include <string_view>

namespace mzlib {
namespace imgui {

///
/// If delta is negative, that is interpreted as this much from the right or bottom.
/// If delta is negative, that is interpreted as this much from the left or top.
///
void set_next_window_relative_position(const float delta_x, const float delta_y)
{
   auto displaySize = ImGui::GetIO().DisplaySize;

   displaySize.x = delta_x > 0 ? delta_x : displaySize.x + delta_x;
   displaySize.y = delta_y > 0 ? delta_y : displaySize.y + delta_y;

   ImGui::SetNextWindowPos(displaySize);
}

bool standalone_button(std::string_view button_text) {
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
}

#endif