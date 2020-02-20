#pragma once

#include <string>
#include <vector>

namespace Ion_DrumPad
{

struct Dimensions
{
  uint32_t width;
  uint32_t height;
};

struct Position
{
  uint32_t x;
  uint32_t y;
};

// Defines a drum object
struct Drum
{
  // Uniquely identifying name of a drum. It will be displayed
  std::string name;
  // Path to the sound file
  std::string sound_file;
  // Combination of keys to trigger
  std::vector<uint32_t> keys_combination;
  // Combination of joustick buttons to trigger
  std::vector<uint32_t> joystick_buttons_combination;
  // Position on screen where to draw it
  Position position_on_screen;
};

// Manages configuration file
struct ConfigReader
{
  // Reads config from file and calls Validate
  void ReadFromFile(std::string file);
  // Returns the drums configuration
  const std::vector<Drum> &Drums();

private:
  // Checks if data is correct
  void Validate();
};

// Defines application callbacks and settings
struct App
{
  App(std::string config_path)
  {
    ConfigReader config_reader;
    config_reader.ReadFromFile(config_path);
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