#pragma once

#include <chrono>
#include <string>
#include <vector>

#include "algebra.hpp"
#include "config_file.hpp"
#include "drum.hpp"
#include "timer.hpp"

namespace Ion_DrumPad
{
// Defines application callbacks and settings
struct App
{
  App() : drums(ConfigFile::ReadFromFile(config_path)) {}

  void KeyPressedCallback(uint32_t key_code);
  void KeyReleasedCallback(uint32_t key_code);
  void JoystickButtonPressedCallback(uint32_t joystick_id, uint32_t joystick_button);
  void JoystickButtonReleasedCallback(uint32_t joystick_id, uint32_t joystick_button);
  void JoystickConnectedCallback(uint32_t joystick_id);
  void JoystickDisconnectedCallback(uint32_t joystick_id);

  // Get current working directory
  static std::string GetPath();

  const Dimensions window_size{800, 600};
  const std::string window_title{"Ion Drum Pad"};
  const std::string config_path{"../config.json"};
  const std::vector<Drum> drums;
#ifdef _WIN32
  const std::string default_font{"C:\\Windows\\Fonts\\arial.ttf"};
#elif __linux__
  const std::string default_font{"/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"};
#endif
  const std::chrono::milliseconds ms_delay{16};
  std::vector<uint32_t> keybord_buttons_pressed;
  std::vector<uint32_t> joystick_buttons_pressed;
};

} // namespace Ion_DrumPad
