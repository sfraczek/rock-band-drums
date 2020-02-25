#include "lib.hpp"

#include <cmath>
#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

struct DrumButtonsManager
{
    explicit DrumButtonsManager(const std::vector<Ion_DrumPad::Drum> drums)
    {
        names.resize(drums.size());
        shapes.resize(drums.size());
        samples.resize(drums.size());
        positions.resize(drums.size());
        radiuses.resize(drums.size());
#ifdef DEBUG
        last_distances.resize(drums.size(), -1);
        std::vector<uint32_t> count(drums.size(), 0);
#endif
        for (size_t i = 0; i < drums.size(); i++)
        {
            names[i] = drums[i].name;
            positions[i] = drums[i].position_on_screen;
            radiuses[i] = drums[i].radius;

            // Create button shape
            shapes[i].setPosition(drums[i].position_on_screen.x, drums[i].position_on_screen.y);
            shapes[i].setRadius(drums[i].radius);
            shapes[i].setFillColor(sf::Color::Green);

            // Load a Sound to play
            sf::SoundBuffer sb;
            if (!sb.loadFromFile(drums[i].sound_file))
            {
                throw std::runtime_error("Couldn't load sample '" + Ion_DrumPad::App::getPath() + drums[i].sound_file + "'.");
            }
            samples[i] = std::make_unique<sf::Sound>(sb);
        }
    }

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
        samples[index]->play();
#ifdef DEBUG
        std::cout << "Visual button pressed!" << std::endl;
        std::cout << "Visual button name: " << names[index] << std::endl;
        std::cout << "Visual button distance: " << last_distances[index] << std::endl;
        std::cout << "Clicked for " << count[index]++ << " time" << std::endl;
#endif
    }

    std::vector<float> radiuses;
    std::vector<std::string> names;
    std::vector<sf::CircleShape> shapes;
    std::vector<std::unique_ptr<sf::Sound>> samples;
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

        setString("Press any key or joystick button");
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
                        buttons_manager.shapes[index].setFillColor(sf::Color::Red);
                    }
                }
            }
            break;

            default:
                break;
            }
        }

        window.clear();
        for (auto &button : buttons_manager.shapes)
            window.draw(button);
        window.draw(text);
        window.display();
    }

    return EXIT_SUCCESS;
}
