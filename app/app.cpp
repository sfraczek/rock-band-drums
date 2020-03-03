#include "lib.hpp"

#include <cmath>
#include <iostream>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "timer.hpp"
#include "util.hpp"

struct DrumButtonsManager
{
    explicit DrumButtonsManager(const std::vector<Ion_DrumPad::Drum> drums)
    {
        names.resize(drums.size());
        shapes.resize(drums.size());
        textures.resize(drums.size());
        samples.resize(drums.size());
        sound_buffers.resize(drums.size());
        positions.resize(drums.size());
        radiuses.resize(drums.size());
        keyboard_buttons_combination.resize(drums.size());
        joystick_buttons_combination.reserve(drums.size());
#ifdef DEBUG
        last_distances.resize(drums.size(), -1);
        std::vector<uint32_t> count(drums.size(), 0);
#endif
        for (size_t i = 0; i < drums.size(); i++)
        {
            names[i] = drums[i].name;
            positions[i] = drums[i].position_on_screen;
            radiuses[i] = drums[i].radius;
            keyboard_buttons_combination[i] = drums[i].keyboard_buttons_combination;
            joystick_buttons_combination[i] = drums[i].joystick_buttons_combination;

            // Create button shape
            shapes[i].setPosition(drums[i].position_on_screen.x, drums[i].position_on_screen.y);
            shapes[i].setRadius(drums[i].radius);
            shapes[i].setFillColor(sf::Color::Green);
            // and texture
            if (!drums[i].image_file.empty())
            {
                textures[i] = std::make_unique<sf::Texture>();
                if (!textures[i]->loadFromFile(drums[i].image_file))
                {
                    throw std::runtime_error("Couldn't load image '" + Ion_DrumPad::App::GetPath() + drums[i].image_file + "'.");
                }
                else
                {
                    shapes[i].setTexture(textures[i].get());
                }
            }
            shapes[i].setPosition(drums[i].position_on_screen.x, drums[i].position_on_screen.y);

            // Load a Sound to play
            if (!sound_buffers[i].loadFromFile(drums[i].sound_file))
            {
                throw std::runtime_error("Couldn't load sound '" + Ion_DrumPad::App::GetPath() + drums[i].sound_file + "'.");
            }
            samples[i].setBuffer(sound_buffers[i]);
        }
    }

    size_t GetButtonIndexAt(int32_t x, int32_t y)
    {
        for (int i = 0; i < positions.size(); i++)
        {
#ifdef DEBUG
            if (Contains(positions[i], radiuses[i], x, y, last_distances[i]))
#else
            if (Contains(positions[i], radiuses[i], x, y))
#endif
            {
                return i;
            }
        }
        return -1;
    }

    void Click(size_t index)
    {
        samples[index].play();
#ifdef DEBUG
        std::cout << "Visual button pressed!" << std::endl;
        std::cout << "Visual button name: " << names[index] << std::endl;
        std::cout << "Visual button distance: " << last_distances[index] << std::endl;
        std::cout << "Clicked for " << count[index]++ << " time" << std::endl;
#endif
    }

    size_t GetButtonIndexByKeyboardCombo(const std::vector<uint32_t> &combo)
    {
        for (int i = 0; i < keyboard_buttons_combination.size(); i++)
        {
            if (combo == keyboard_buttons_combination[i])
            {
                return i;
            }
        }
        return -1;
    }

    size_t GetButtonIndexByJoystickCombo(const std::vector<uint32_t> &combo)
    {
        for (int i = 0; i < joystick_buttons_combination.size(); i++)
        {
            if (combo == joystick_buttons_combination[i])
            {
                return i;
            }
        }
        return -1;
    }

private:
#ifdef DEBUG
    inline bool Contains(const Ion_DrumPad::Position &p, float radius, int32_t x, int32_t y, float &last_distance)
    {
        float dx = p.x + radius - x;
        float dy = p.y + radius - y;
        last_distance = std::hypot(dx, dy);
        return last_distance < radius;
    }
#else
    inline bool Contains(const Ion_DrumPad::Position &p, float radius, int32_t x, int32_t y)
    {
        float dx = p.x + radius - x;
        float dy = p.y + radius - y;
        return std::hypot(dx, dy) < radius;
    }
#endif

public:
    std::vector<float> radiuses;
    std::vector<std::string> names;
    std::vector<sf::CircleShape> shapes;
    std::vector<std::unique_ptr<sf::Texture>> textures;
    std::vector<sf::Sound> samples;
    std::vector<sf::SoundBuffer> sound_buffers;
    std::vector<Ion_DrumPad::Position> positions;
    std::vector<std::vector<uint32_t>> keyboard_buttons_combination;
    std::vector<std::vector<uint32_t>> joystick_buttons_combination;
#ifdef DEBUG
    std::vector<float> last_distances;
    std::vector<uint32_t> count(drums.size(), 0);
#endif
};

struct MainText : public sf::Text
{
    explicit MainText(std::string fname)
    {
        if (!font.loadFromFile(fname))
        {
            throw std::runtime_error("Could not load font '" + fname + "' from file.");
        }

        setString("Click buttons with mouse or press assigned key or joystick button");
        setFont(font);
        setCharacterSize(30);
        setFillColor(sf::Color::Red);
        setOrigin((-800 + getGlobalBounds().width) / 2, -10);
    }

private:
    sf::Font font;
};

int main()
{
    Ion_DrumPad::App app;

    sf::RenderWindow window(sf::VideoMode(app.window_size.width, app.window_size.height), app.window_title);

    MainText text(app.default_font);

    DrumButtonsManager buttons_manager(app.drums);

    Timer combo_timer;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                app.KeyPressedCallback(event.key.code);
                break;

            case sf::Event::KeyReleased:
                app.KeyReleasedCallback(event.key.code);
                break;

            case sf::Event::JoystickButtonPressed:
                app.JoystickButtonPressedCallback(event.joystickButton.joystickId, event.joystickButton.button);
                break;

            case sf::Event::JoystickButtonReleased:
                app.JoystickButtonReleasedCallback(event.joystickButton.joystickId, event.joystickButton.button);
                break;

            case sf::Event::JoystickConnected:
                app.JoystickConnectedCallback(event.joystickConnect.joystickId);
                break;

            case sf::Event::JoystickDisconnected:
                app.JoystickDisconnectedCallback(event.joystickConnect.joystickId);
                break;

            case sf::Event::MouseButtonPressed:
            {
                size_t index = buttons_manager.GetButtonIndexAt(event.mouseButton.x, event.mouseButton.y);
                if (index != -1)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        buttons_manager.Click(index);
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        // Toggle colors except for black (0,0,255 -> 0,255,0 -> 0,255,255 -> ... -> 255,255,255 -> 0,0,255)
                        auto color = buttons_manager.shapes[index].getFillColor();
                        int number = ((color.r & 1) << 2) + ((color.g & 1) << 1) + (color.b & 1);
                        int new_number = std::max((number + 1) % 0b1000, 0b001);
                        sf::Color new_color(255 * ((new_number & 0b100) >> 2), 255 * ((new_number & 0b010) >> 1), 255 * (new_number & 0b001));
                        buttons_manager.shapes[index].setFillColor(new_color);
                    }
                }
            }
            break;

            default:
                break;
            }
        }

        if (combo_timer.IsItTime(app.ms_delay))
        {
            if (!app.keybord_buttons_pressed.empty())
            {
                Ion_DrumPad::sort_make_unique(app.keybord_buttons_pressed);
                auto subsets = app.GetAllSubsetsSorted(app.keybord_buttons_pressed);
                for (auto &subset : subsets)
                {
                    auto index = buttons_manager.GetButtonIndexByKeyboardCombo(subset);
                    if (index != -1)
                    {
                        app.keybord_buttons_pressed.clear();
                        buttons_manager.Click(index);
                        break;
                    }
                }
                app.keybord_buttons_pressed.clear();
            }
            if (!app.joystick_buttons_pressed.empty())
            {
                Ion_DrumPad::sort_make_unique(app.joystick_buttons_pressed);
                auto subsets = app.GetAllSubsetsSorted(app.joystick_buttons_pressed);
                for (auto &subset : subsets)
                {
                    auto index = buttons_manager.GetButtonIndexByJoystickCombo(subset);
                    app.joystick_buttons_pressed.clear();
                    if (index != -1)
                    {
                        app.joystick_buttons_pressed.clear();
                        buttons_manager.Click(index);
                        break;
                    }
                }
                app.joystick_buttons_pressed.clear();
            }
        }

        window.clear();
        for (auto &button : buttons_manager.shapes)
        {
            window.draw(button);
        }
        window.draw(text);
        window.display();
    }

    return EXIT_SUCCESS;
}
