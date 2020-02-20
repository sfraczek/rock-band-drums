#include "lib.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <cmath>
#include <iostream>

struct DrumButton : public sf::CircleShape
{
    DrumButton()
    {
        setFillColor(sf::Color::Green);
        setRadius(100.f);

        static int i = 0;
        id = i++;
    }

    bool Contains(int32_t x, int32_t y)
    {
        float dx = GetCenterX() - x;
        float dy = GetCenterY() - y;
        last_distance = std::hypot(dx, dy);
        return last_distance < getRadius();
    }

    float GetCenterX()
    {
        return (getPosition().x + getRadius());
    }

    float GetCenterY()
    {
        return (getPosition().y + getRadius());
    }

    void Click()
    {
        sample.play();
        std::cout << "Visual button pressed!" << std::endl;
        std::cout << "Visual button id: " << id << std::endl;
        std::cout << "Visual button distance: " << last_distance << std::endl;
        static int i = 0;
        std::cout << "Clicked for " << i++ << " time" << std::endl;
    }

    void SetSample(std::string file)
    {
        // Load a music to play
        if (!sample.openFromFile(file))
            throw std::runtime_error("Couldn't load sample '" + file + "'.");
    }

private:
    sf::Music sample;
    uint32_t id;
    float last_distance;
};

struct MainText : public sf::Text
{
    MainText(sf::Font font) : font(std::move(font))
    {
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

    Ion_DrumPad::Config cfg = app.ReadConfig();

    sf::RenderWindow window(sf::VideoMode(app.window_size.width, app.window_size.height), app.window_title);

    sf::Font default_font;
    std::string fname{"C:\\Windows\\Fonts\\arial.ttf"};
    if (!default_font.loadFromFile(fname))
    {
        throw std::runtime_error("Could not load font '" + fname + "' from file.");
    }
    MainText text(default_font);

    DrumButton shape;

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
                if (shape.Contains(event.mouseButton.x, event.mouseButton.y))
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        shape.Click();
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        shape.setFillColor(sf::Color::Red);
                    }
                }
                break;

            default:
                break;
            }
        }

        window.clear();
        window.draw(shape);
        window.draw(text);
        window.display();
    }

    return 0;
}