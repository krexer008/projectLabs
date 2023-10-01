#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
    // Инициализация окружности:
    constexpr int pointCount = 200;
    const sf::Vector2f ellipseRadius = {200.f, 80.f};

    // Создаём окно с параметрами сглаживания
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}), "Ellipse",
        sf::Style::Default, settings);

    //  Объявляем фигуру которая будет выглядеть как еллипс
    sf::ConvexShape ellipse;
    ellipse.setPosition({400, 320});
    ellipse.setFillColor(sf::Color(0xff, 0xff, 0xff));

    // Инициализируем вершины псевдо-эллипса.
    ellipse.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = sf::Vector2f{
            ellipseRadius.x * std::sin(angle),
            ellipseRadius.y * std::cos(angle)};
        ellipse.setPoint(pointNo, point);
    }

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

        window.clear();
        window.draw(ellipse);
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