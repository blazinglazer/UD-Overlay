#include <iostream>
#include <windows.h>

namespace render {
  HHOOK pre_wnd_proc = nullptr;
  HDC device_context = nullptr;
  HWND game_window = nullptr;
  RECT window_rect;
  POINT recent_position;

  void set_line_color(int r, int g, int b) {
    // Set the line color to the specified RGB values
  }

  void line_to(int x, int y) {
    // Draw a line on the overlay from the recent_position to the specified x and y coordinates
    recent_position.x = x;
    recent_position.y = y;
  }

  void set_text_color(int r, int g, int b) {
    // Set the text color to the specified RGB values
  }

  void render_text(const char* text, int x, int y) {
    // Draw the specified text on the overlay at the specified x and y coordinates
  }
}

namespace overlay {
  LRESULT call_wnd_proc(int code, WPARAM w_param, LPARAM l_param) {
    if (code == HC_ACTION) {
      CWPSTRUCT* cwp = reinterpret_cast<CWPSTRUCT*>(l_param);
      if (cwp->message == WM_CLOSE || cwp->message == WM_QUIT || cwp->message == WM_DESTROY) {
        // Exit the process if one of the specified messages is received
        exit(0);
      }
    }

    // Pass the message on to the next hook in the chain
    return CallNextHookEx(render::pre_wnd_proc, code, w_param, l_param);
  }
}

int main() {
  // Find the window with the title "Fortnite" and store its handle in the render::game_window variable
  render::game_window = FindWindowW(nullptr, L"Fortnite");
  if (render::game_window == nullptr) {
    std::cerr << "Could not find window with title 'Fortnite'" << std::endl;
    return 1;
  }

  // Set the text and line colors on the overlay
  render::set_text_color(255, 0, 0); // Red
  render::set_line_color(255, 0, 0); // Red

  // Set up the hook to capture window messages
  render::pre_wnd_proc = SetWindowsHookExW(WH_CALLWNDPROC, overlay::call_wnd_proc, nullptr, GetCurrentThreadId());
  if (render::pre_wnd_proc == nullptr) {
    std::cerr << "Could not set up hook" << std::endl;
    return 1;
  }

  // Exit the thread
  ExitThread(0);

  return 0;
}
