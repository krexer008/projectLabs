#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Rectangles and circle");

    window.clear(sf::Color(0xff, 0xff, 0xff));

    //I
    sf::RectangleShape shape1;
    shape1.setSize({20, 150});
    shape1.setRotation(0);
    shape1.setPosition({50, 0});
    shape1.setFillColor(sf::Color(0x0, 0x0, 0x0));
    window.draw(shape1);

    //F
    sf::RectangleShape shape2;
    shape2.setSize({80, 20});
    shape2.setRotation(0);
    shape2.setPosition({100, 0});
    shape2.setFillColor(sf::Color(0x0, 0x0, 0x0));
    window.draw(shape2);

    sf::RectangleShape shape3;
    shape3.setSize({50, 20});
    shape3.setRotation(0);
    shape3.setPosition({100, 50});
    shape3.setFillColor(sf::Color(0x0, 0x0, 0x0));
    window.draw(shape3);

    sf::RectangleShape shape4;
    shape4.setSize({20, 150});
    shape4.setRotation(0);
    shape4.setPosition({100, 0});
    shape4.setFillColor(sf::Color(0x0, 0x0, 0x0));
    window.draw(shape4);

    //V

    sf::RectangleShape shape5;
    shape5.setSize({20, 160});
    shape5.setRotation(165);
    shape5.setPosition({250, 150});
    shape5.setFillColor(sf::Color(0x0, 0x0, 0x0));
    window.draw(shape5);

    sf::RectangleShape shape6;
    shape6.setSize({20, 150});
    shape6.setRotation(195);
    shape6.setPosition({250, 150});
    shape6.setFillColor(sf::Color(0x0, 0x0, 0x0));
    window.draw(shape6);

    window.display();

    sf::sleep(sf::seconds(5));
}