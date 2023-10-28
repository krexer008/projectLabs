#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

// Переводит радианы в градусы
float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

// Обрабатывает событие MouseMove, обновляя позиции мыши
void onMouseClick(const sf::Event &event, sf::Vector2f &mousePosition, sf::Sprite &sprite)
{
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        std::cout << "the left button was pressed" << std::endl;
        std::cout << "mouse x: " << event.mouseButton.x
                  << "mouse y: " << event.mouseButton.y << std::endl;
        mousePosition.x = event.mouseButton.x;
        mousePosition.y = event.mouseButton.y;
        sprite.setPosition({mousePosition.x, mousePosition.y});
    };
}

// Опрашивает и обрабатывает доступные события в цикле.
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, sf::Sprite &sprite)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            onMouseClick(event, mousePosition, sprite);
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
    sf::Vector2f motion = mousePosition - sprite.getPosition();

    // Движение кота
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

    motion = mousePosition - sprite.getPosition();
    float newAngle = toDegrees(atan2(motion.y, motion.x));
    if (newAngle < 0)
    {
        newAngle = newAngle + 360;
    }

    const float currentAngle = sprite.getRotation();
    const float delta = std::sqrt(motion.x * motion.x + motion.y * motion.y);

    if ((newAngle != currentAngle) && (delta > 1))
    {
        if ((newAngle <= 90) || (newAngle >= 270) && (newAngle < 450))
        {
            sprite.setScale(sf::Vector2f(1, 1));
        }
        else
        {
            sprite.setScale(sf::Vector2f(-1, 1));
        }
    }
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, sf::Sprite &sprite1, sf::Sprite &sprite2)
{
    window.clear(sf::Color::White);
    window.draw(sprite1);
    window.draw(sprite2);
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
        "Cat mooveing to red pointer", sf::Style::Default, settings);

    sf::Clock clock;
    sf::Vector2f mousePosition;

    sf::Texture textureCat;
    if (!textureCat.loadFromFile("cat1.png"))
    {
        std::cout << "Error load texture" << std::endl;
    }
    sf::Sprite cat;
    cat.setTexture(textureCat);

    sf::Texture textureRedPointer;
    if (!textureRedPointer.loadFromFile("red_pointer.png"))
    {
        std::cout << "Error load texturePoint" << std::endl;
    }
    cat.setOrigin(sf::Vector2f(45, 17));
    cat.setPosition({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2});

    sf::Sprite redPointer;
    redPointer.setTexture(textureRedPointer);
    redPointer.setOrigin(sf::Vector2f(16, 16));

    mousePosition = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    while (window.isOpen())
    {
        pollEvents(window, mousePosition, redPointer);
        update(mousePosition, cat, clock);
        redrawFrame(window, cat, redPointer);
    }
}
