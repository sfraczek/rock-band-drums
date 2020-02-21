#pragma once

#include <string>
#include <vector>

#include "config_file.hpp"
#include "algebra.hpp"
#include "drum.hpp"

namespace Ion_DrumPad
{

// Defines application callbacks and settings
struct App
{
  explicit App(std::string config_path)
  {
    auto config = ConfigFile::ReadFromFile(config_path);
  }

  void KeyPressedCallback(uint32_t key_code);
  void KeyReleasedCallback(uint32_t key_code);
  void JoystickButtonPressedCallback(uint32_t joystick_id, uint32_t joystick_button);
  void JoystickButtonReleasedCallback(uint32_t joystick_id, uint32_t joystick_button);
  void JoystickConnectedCallback(uint32_t joystick_id);
  void JoystickDisconnectedCallback(uint32_t joystick_id);

  const Dimensions window_size{800, 600};
  const std::string window_title{"Ion Drum Pad"};
  std::vector<Drum> drums;
};

} // namespace Ion_DrumPad