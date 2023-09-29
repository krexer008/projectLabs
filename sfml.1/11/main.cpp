#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Rectangles and circle");

    window.clear(sf::Color(0xff, 0xff, 0xff));

    sf::RectangleShape shape1;
    shape1.setSize({120, 340});
    shape1.setRotation(0);
    shape1.setPosition({100, 0});
    shape1.setFillColor(sf::Color(0x0, 0x0, 0x0));
    window.draw(shape1);

    sf::CircleShape shape2(50);
    shape2.setPosition({110, 10});
    shape2.setFillColor(sf::Color(0x0, 0xff, 0x0));
    window.draw(shape2);

    sf::CircleShape shape3(50);
    shape3.setPosition({110, 120});
    shape3.setFillColor(sf::Color(0xff, 0xff, 0x0));
    window.draw(shape3);

    sf::CircleShape shape5(50);
    shape5.setPosition({110, 230});
    shape5.setFillColor(sf::Color(0xff, 0x0, 0x0));
    window.draw(shape5);

    window.display();

    sf::sleep(sf::seconds(5));
}