#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

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
void update(const sf::Vector2f &mousePosition, sf::Sprite &sprite, sf::Clock &clock)
{

    float maxSpeed = 100.f;
    float maxLineSpeed = 100.f;
    const float deltaTime = clock.restart().asSeconds();
    const sf::Vector2f motion = mousePosition - sprite.getPosition();

    const float motionLendth = std::sqrt(motion.x * motion.x + motion.y * motion.y);
    if (motionLendth != 0)
    {
        const sf::Vector2f direction = {motion.x / motionLendth, motion.y / motionLendth};
        const float distance = maxLineSpeed * deltaTime;
        if (distance != 0)
        {
            sprite.setPosition(sprite.getPosition() + direction * distance);
        }
    }

    float newAngle = toDegrees(atan2(motion.y, motion.x));
    if (newAngle < 0)
    {
        newAngle = newAngle + 360;
    }

    const float currentAngle = sprite.getRotation();

    if (newAngle != currentAngle)
    {
        float rotateAngle = newAngle - currentAngle;
        if ((rotateAngle < 180) && (rotateAngle > 0) || rotateAngle < -180)
        {
            sprite.rotate(maxSpeed * deltaTime);
        }
        else
        {
            sprite.rotate(-maxSpeed * deltaTime);
        }
    }
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, sf::Sprite &sprite)
{
    window.clear(sf::Color::White);
    window.draw(sprite);
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
    sf::Vector2f mousePosition;

    sf::Texture texture;
    if (!texture.loadFromFile("cat1.png"))
    {
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);

    sprite.setOrigin(sf::Vector2f(25, 25));
    texture.setSmooth(true);
    sprite.setPosition({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2});
    mousePosition = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, sprite, clock);
        redrawFrame(window, sprite);
    }
}