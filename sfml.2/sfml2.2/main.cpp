#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr int pointCount = 200;
constexpr float radiusCircle = 50.f;
constexpr float stepPerSec = 2.f;

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

    const sf::Vector2f centerCircle = {400.f, 320.f};
    const float circleSpeed = stepPerSec * (2 * M_PI);

    //  Объявляем фигуру Rose
    sf::ConvexShape rose;
    rose.setFillColor(sf::Color(0xff, 0x09, 0x80));
    rose.setPointCount(pointCount);

    sf::Vector2f position = {400, 320};

    // Инициализируем вершины псевдо-эллипса.
    /*
    rose.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);

        float roseRadius = 200 * sin(6 * angle);

        sf::Vector2f point = {
            roseRadius * std::sin(angle),
            roseRadius * std::cos(angle)};
        rose.setPoint(pointNo, point);
    }
    */

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

        shapeSetPointing(&rose, position);

        window.clear();
        window.draw(rose);
        window.display();
    }
}