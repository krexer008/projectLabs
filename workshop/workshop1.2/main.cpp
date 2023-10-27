#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

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
    shape.setPosition({400, 400});
    shape.setFillColor(sf::Color(0xff, 0x80, 0x0));
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(5);
}

// Переводит радианы в градусы
float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

// Обрабатывает событие MouseMove, обновляя позиции мыши
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x
              << ". y=" << event.y
              << std::endl;

    mousePosition = {float(event.x), float(event.y)};
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
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

// Обновляет фигуру, указывающую на мышь
void update(const sf::Vector2f &mousePosition, sf::ConvexShape &shape, sf::Clock &clock)
{
    float maxSpeed = 100.f;
    float maxLineSpeed = 20.f;
    const float deltaTime = clock.restart().asSeconds();
    const sf::Vector2f motion = mousePosition - shape.getPosition();

    const float motionLendth = std::sqrt(motion.x * motion.x + motion.y * motion.y);
    if (motionLendth != 0)
    {
        const sf::Vector2f direction = {motion.x / motionLendth, motion.y / motionLendth};
        const float distance = maxLineSpeed * deltaTime;
        if (distance != 0)
        {
            shape.setPosition(shape.getPosition() + direction * distance);
        }
    }

    float newAngle = toDegrees(atan2(motion.y, motion.x));
    if (newAngle < 0)
    {
        newAngle = newAngle + 360;
    }

    const float currentAngle = shape.getRotation();

    if (newAngle != currentAngle)
    {
        float rotateAngle = newAngle - currentAngle;
        if ((rotateAngle < 180) && (rotateAngle > 0) || rotateAngle < -180)
        {
            shape.rotate(maxSpeed * deltaTime);
        }
        else
        {
            shape.rotate(-maxSpeed * deltaTime);
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
    constexpr unsigned WINDOW_HEIGHT = 800;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Arrow following and mooveing to coursor", sf::Style::Default, settings);

    sf::Clock clock;
    sf::ConvexShape shape;
    sf::Vector2f mousePosition;

    init(shape);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, shape, clock);
        redrawFrame(window, shape);
    }
}