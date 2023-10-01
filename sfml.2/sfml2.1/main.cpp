#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

int main()
{
    constexpr float BALL_SIZE = 40;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wave Moveng Ball and Wall ");
    sf::Clock clock;

    sf::Vector2f position = {10, 350};

    constexpr float speedX = 100.f;
    float speedXE = speedX;
    float elapsedTime = 0;
    constexpr float amplitudeY = 80.f;
    constexpr float periodY = 2;

    sf::CircleShape ball(BALL_SIZE);
    ball.setFillColor(sf::Color(0xff, 0xff, 0xff));

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

        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speedXE > 0) || (position.x < 0) && (speedXE < 0))
        {
            speedXE = -speedXE;
        }
        /*
        if ((position.x < 0) && (speedXE < 0))
        {
            speedXE = -speedXE;
        }
        */

        const float deltaTime = clock.restart().asSeconds();

        // y move
        elapsedTime += deltaTime;
        const float wavePhase = elapsedTime * float(2 * M_PI);
        const float y = amplitudeY * std::sin(wavePhase / periodY);

        float x = speedXE * deltaTime;
        position.x += x;
        const sf::Vector2f offset = {position.x, position.y + y};

        ball.setPosition(offset);

        //Рисование текущего состояния
        window.clear();
        window.draw(ball);
        window.display();
    }
}