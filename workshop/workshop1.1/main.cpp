#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

// Инициализирует фигуру-указатель
void init(sf::ConvexShape &shape)
{
    shape.setPointCount(8);
    shape.setPoint(0, {-26, 0});
    shape.setPoint(1, {-26, 13});
    shape.setPoint(2, {0, 13});
    shape.setPoint(3, {0, 26});
    shape.setPoint(4, {26, 0});
    shape.setPoint(5, {0, -26});
    shape.setPoint(6, {0, -13});
    shape.setPoint(7, {-26, -13});
    shape.setPosition({400, 300});
    shape.setFillColor(sf::Color(0xff, 0x80, 0x0));
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(5);
}

// Опрашивает и обрабатывает доступные события в цикле.
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
            /*
            case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        */
        default:
            break;
        }
    }
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &shape)
{
    window.clear(sf::Color::White);
    window.draw(shape);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Pointer follows mouse", sf::Style::Default, settings);

    sf::ConvexShape shape;
    sf::Vector2f mousePosition;

    init(shape);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        redrawFrame(window, shape);
    }
}