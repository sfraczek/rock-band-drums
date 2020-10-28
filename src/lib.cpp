#include "lib.hpp"

#include <iostream>

void Ion_DrumPad::App::KeyPressedCallback(uint32_t key_code)
{
    keybord_buttons_pressed.push_back(key_code);
    std::cout << "Key pressed!" << std::endl;
    std::cout << "Key id: " << key_code << std::endl;
}

void Ion_DrumPad::App::KeyReleasedCallback(uint32_t key_code)
{
    std::cout << "Key released!" << std::endl;
    std::cout << "Key id: " << key_code << std::endl;
}

void Ion_DrumPad::App::JoystickButtonPressedCallback(uint32_t joystick_id, uint32_t joystick_button)
{
    joystick_buttons_pressed.push_back(joystick_button);
    std::cout << "joystick button pressed!" << std::endl;
    std::cout << "joystick id: " << joystick_id << std::endl;
    std::cout << "button: " << joystick_button << std::endl;
}

void Ion_DrumPad::App::JoystickButtonReleasedCallback(uint32_t joystick_id, uint32_t joystick_button)
{
    std::cout << "joystick button released!" << std::endl;
    std::cout << "joystick id: " << joystick_id << std::endl;
    std::cout << "button: " << joystick_button << std::endl;
}

void Ion_DrumPad::App::JoystickConnectedCallback(uint32_t joystick_id)
{
    std::cout << "joystick connected: " << joystick_id << std::endl;
}

void Ion_DrumPad::App::JoystickDisconnectedCallback(uint32_t joystick_id)
{
    std::cout << "joystick disconnected: " << joystick_id << std::endl;
}

void Ion_DrumPad::App::JoystickMovedCallback(int axis, float joystick_position)
{
    joystick_buttons_pressed.push_back(button_axis_offset + axis);
    std::cout << "joystick moved in axis: " << axis << " to position: " << joystick_position << std::endl;
}