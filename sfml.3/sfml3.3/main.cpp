#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct Eye
{
    sf::ConvexShape eye;
    sf::ConvexShape pupil;
    sf::Vector2f position;
    float rotation = 0;
    const float pupilOrbitRadius = 40;
};

//Переводит полярные координаты в декартовы
sf::Vector2f toEuclidean(float radius, float angle)
{
    return {
        float(radius * cos(angle)),
        float(radius * sin(angle))};
}

// Переводит радианы в градусы
float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

// Обновляет позиции и повороты зрачков согласно текущему
// состоянию курсора
void updatePupilPosition(Eye &eye)
{
    const sf::Vector2f eyeOffset = toEuclidean(eye.pupilOrbitRadius, eye.rotation);
    eye.pupil.setPosition(eye.position + eyeOffset);
}

//init Ellipse
void initEllipse(sf::ConvexShape &ellipse,
                 sf::Vector2f ellipseRadius)
{
    const float pointCount = 200;
    ellipse.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            float(ellipseRadius.x * std::sin(angle)),
            float(ellipseRadius.y * std::cos(angle))};
        ellipse.setPoint(pointNo, point);
    }
}

// init Eye
void initEye(Eye &eye, sf::Vector2f position)
{

    eye.position = position;

    eye.eye.setPosition(position);
    eye.eye.setFillColor(sf::Color(0xff, 0xff, 0xff));
    const sf::Vector2f eyeRadius = {60, 100};

    eye.pupil.setPosition(position);
    eye.pupil.setFillColor(sf::Color(0x0, 0x0, 0x0));
    const sf::Vector2f pupilRadius = {15, 25};

    initEllipse(eye.eye, eyeRadius);
    initEllipse(eye.pupil, pupilRadius);

    updatePupilPosition(eye);
}

//Обрабатывает событие MouseMove, обновляя позиции мыши

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
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

// Обновляет направление взгляда, указывающего на мышь
void update(const sf::Vector2f &mousePosition, Eye &eye)
{
    const sf::Vector2f delta = mousePosition - eye.position;
    eye.rotation = atan2(delta.y, delta.x);
    if (eye.rotation != 0)
    {
        if (delta.x * delta.x + delta.y * delta.y <= eye.pupilOrbitRadius * eye.pupilOrbitRadius)
        {
            eye.pupil.setPosition(mousePosition);
        }
        else
        {
            updatePupilPosition(eye);
        }
    }
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, Eye &eye1, Eye &eye2)
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
    window.draw(eye1.eye);
    window.draw(eye1.pupil);
    window.draw(eye2.eye);
    window.draw(eye2.pupil);
    window.display();
}

int main()
{
    // window
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Running eyes follow mouse", sf::Style::Default, settings);

    //eyes

    Eye leftEye;
    Eye rightEye;

    sf::Vector2f mousePosition;

    const sf::Vector2f eyeCenter = {400, 300};
    const float distance = 200.f;

    sf::Vector2f leftEyePos = {eyeCenter.x - distance / 2, eyeCenter.y};
    sf::Vector2f rightEyePos = {eyeCenter.x + distance / 2, eyeCenter.y};

    // init Eye
    initEye(leftEye, leftEyePos);
    initEye(rightEye, rightEyePos);

    // main program cycle
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);

        update(mousePosition, leftEye);

        update(mousePosition, rightEye);

        redrawFrame(window, leftEye, rightEye);
    }
}