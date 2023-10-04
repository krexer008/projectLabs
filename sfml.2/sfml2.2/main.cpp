#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr int pointCount = 200;
constexpr float circleRadius = 100.f;
constexpr float stepPerSec = 1.f;

// Инициализируем вершины псевдо-эллипса.
void shapeSetPointing(sf::ConvexShape *shape, sf::Vector2f position)
{
    shape->setPosition(position);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        const float shapeRadius = 200 * sin(6 * angle);
        sf::Vector2f point = {
            shapeRadius * std::sin(angle),
            shapeRadius * std::cos(angle)};
        shape->setPoint(pointNo, point);
    }
}

int main()
{
    // Создаём окно с параметрами сглаживания
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Rose",
        sf::Style::Default,
        settings);

    sf::Clock clock;

    const sf::Vector2f circleCenter = {400.f, 300.f};
    const float circleSpeed = stepPerSec * (2 * M_PI);

    //  Объявляем фигуру Rose
    sf::ConvexShape rose;
    rose.setFillColor(sf::Color(0xff, 0x09, 0x80));
    rose.setPointCount(pointCount);

    sf::Vector2f position = {400, 320};

    // Выполняем основной цикл программы
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        const float time = clock.getElapsedTime().asSeconds();
        float circleAngle = circleSpeed * time;
        float x = circleCenter.x + round(circleRadius * cos(circleAngle));
        float y = circleCenter.y + round(circleRadius * sin(circleAngle));

        const sf::Vector2f offset = {x, y};

        shapeSetPointing(&rose, offset);

        window.clear();
        window.draw(rose);
        window.display();
    }
}