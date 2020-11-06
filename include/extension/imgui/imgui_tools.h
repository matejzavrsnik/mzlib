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

bool DisplayControlButton(const std::string_view &button_text);

/**
 * @brief Begins an invisible window.
 * @details Begins a window without background, title bar or resize option. Window title doesn't seem necessary, but
 * I think ImGui is using them as an ID because if not provided, the rest of the layout doesn't work correctly anymore.
 * You need to call ImGui::End yourself after this.
 * @return Void, window created.
 */
void BeginInvisibleWindow(
   std::string_view window_title /**< Invisible title of the window. */)
{
   bool show = true;
   auto flags_invisible_window =
      ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground |
      ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar |
      ImGuiWindowFlags_::ImGuiWindowFlags_NoResize;

   ImGui::Begin(window_title.data(), &show, flags_invisible_window);
}




}
}

#endif