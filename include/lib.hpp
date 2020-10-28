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
  void KeyPressedCallback(uint32_t key_code);
  void KeyReleasedCallback(uint32_t key_code);
  void JoystickButtonPressedCallback(uint32_t joystick_id, uint32_t joystick_button);
  void JoystickButtonReleasedCallback(uint32_t joystick_id, uint32_t joystick_button);
  void JoystickConnectedCallback(uint32_t joystick_id);
  void JoystickDisconnectedCallback(uint32_t joystick_id);
  void JoystickMovedCallback(int axis, float joustick_position);

  const Dimensions window_size{1024, 768};
  const std::string window_title{"Ion Drum Pad"};
  const std::string config_path{"config.json"};
#ifdef _WIN32
  const std::string default_font{"C:\\Windows\\Fonts\\arial.ttf"};
#elif __linux__
  const std::string default_font{"/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"};
#endif
  const std::chrono::milliseconds ms_delay{16};
  const ConfigFile::Config config{config_path};
  std::vector<uint32_t> keybord_buttons_pressed;
  std::vector<uint32_t> joystick_buttons_pressed;
  // add axis movement to joystick buttons vector with offset
  uint32_t button_axis_offset = 100;
};

} // namespace Ion_DrumPad
