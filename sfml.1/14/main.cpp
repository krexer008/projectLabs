#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Shapes HomeBuild");

    sf::RectangleShape base;
    base.setSize({480, 252});
    base.setRotation(0);
    base.setPosition({160, 320});
    base.setFillColor(sf::Color(0x77, 0x34, 0x14));

    sf::RectangleShape door;
    door.setSize({80, 160});
    door.setRotation(0);
    door.setPosition({208, 408});
    door.setFillColor(sf::Color(0x40, 0x40, 0x40));

    sf::ConvexShape roof;
    roof.setFillColor(sf::Color(0x89, 0x08, 0x35));
    roof.setPosition({400, 260});
    roof.setPointCount(4);
    roof.setPoint(0, {-120, -60});
    roof.setPoint(1, {120, -60});
    roof.setPoint(2, {+300, 60});
    roof.setPoint(3, {-300, 60});

    sf::RectangleShape chimney;
    chimney.setSize({40, 65});
    chimney.setRotation(0);
    chimney.setPosition({460, 192});
    chimney.setFillColor(sf::Color(0x70, 0x69, 0x68));

    sf::RectangleShape chimneyHead;
    chimneyHead.setSize({64, 44});
    chimneyHead.setRotation(0);
    chimneyHead.setPosition({448, 148});
    chimneyHead.setFillColor(sf::Color(0x70, 0x69, 0x68));

    sf::CircleShape smokeCloud1(16);
    smokeCloud1.setPosition({476, 120});
    smokeCloud1.setFillColor(sf::Color(0x9b, 0x9b, 0x9b));

    sf::CircleShape smokeCloud2(20);
    smokeCloud2.setPosition({484, 88});
    smokeCloud2.setFillColor(sf::Color(0x9b, 0x9b, 0x9b));

    sf::CircleShape smokeCloud3(24);
    smokeCloud3.setPosition({500, 60});
    smokeCloud3.setFillColor(sf::Color(0x9b, 0x9b, 0x9b));

    sf::CircleShape smokeCloud4(24);
    smokeCloud4.setPosition({516, 28});
    smokeCloud4.setFillColor(sf::Color(0x9b, 0x9b, 0x9b));

    window.clear(sf::Color(0xff, 0xff, 0xff));

    window.draw(base);
    window.draw(door);
    window.draw(roof);
    window.draw(chimney);

    window.draw(smokeCloud1);
    window.draw(chimneyHead);

    window.draw(smokeCloud2);

    window.draw(smokeCloud3);
    window.draw(smokeCloud4);

    window.display();

    sf::sleep(sf::seconds(2));
}