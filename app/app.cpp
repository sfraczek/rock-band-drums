#include "lib.hpp"

/* #include <iostream>

int main(int argc, const char* argv[])
{
    Program program;
    std::cout << "Hello world " << program.add(1,2) << ".\n";
    return program.add(-10, 10);
} */

#include <SFML/Graphics.hpp>

int main()
{
    Program program;
    const std::string window_name = std::string{"SFML works! Also 1+2="}+std::to_string(program.add(1,2));

    sf::RenderWindow window(sf::VideoMode(200, 200), window_name);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}