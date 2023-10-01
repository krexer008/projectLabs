#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
    // Инициализация окружности:
    constexpr int pointCount = 30;
    constexpr float circleRadius = 200;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Ellipse");

    //  - объявляем переменную типа sf::ConvexShape
    sf::ConvexShape shape;
    shape.setPosition({400, 320});
    shape.setFillColor(sf::Color(0xff, 0xff, 0xff));

    shape.setPointCount(pointCount);

    //  - в цикле по i от 1 до N, где N - точность рисования круга
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {

        //    1. вычисляем angle как (2 * π * i / N)
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = sf::Vector2f{
            circleRadius * std::sin(angle),
            circleRadius * std::cos(angle)};
        shape.setPoint(pointNo, point);
    }

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

        window.clear();
        window.draw(shape);
        window.display();
    }

    //    3. переводим координаты из полярных (angle, radius)
    //       в декартовы (x, y)

    //    4. добавляем точку в ConvexShape с номером i, используя
    //       координаты (x, y)

    // Основной цикл:
    // 1. обработка событий (вложенный цикл)
    // 2. обновление состояния (перемещение)
    // 3. рисование
}