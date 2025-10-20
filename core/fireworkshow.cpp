#include "core/fireworkshow.h"

#include <iostream>

void FireWorkShow::setWidthHeight(int width, int height)
{
    windowWidth = width;
    windowHeight = height;
}


void FireWorkShow::update(float delta)
{
    for (int i = fireworks.size() - 1; i >= 0; i--)
    {
        int done = fireworks[i].update(delta);
        if (done)
        {
            std::swap(fireworks[i], fireworks.back());
            fireworks.pop_back();
        }
    }
}

void FireWorkShow::render(sf::RenderWindow& window)
{
    for (int i = 0; i < fireworks.size(); i++)
    {
        fireworks[i].draw(window);
    }
}

void FireWorkShow::runApp()
{
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Happy Diwali");

    sf::RectangleShape fade(sf::Vector2f(windowWidth, windowHeight));
    fade.setFillColor(sf::Color(0, 0, 0, 20));  // Low alpha => slow fading, high alpha => fast fade

    window.setFramerateLimit(60);
    float delta = 1.f / 60.f;

    sf::CircleShape circle(10.f);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(sf::Vector2f(300, 300));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                auto mousepos = sf::Mouse::getPosition(window);
                sf::Color col(255 + randomVal() * 255, 255 + randomVal() * 255, 255 + randomVal() * 255);
                fireworks.emplace_back(
                    sf::Vector2f(mousepos.x, mousepos.y),       // pos
                    sf::Vector2f{0.f, -250.f + randomVal() * 50},                  // vel
                    2.f,                                        // radius
                    col,              // color  
                    1                                           // stages
                );
            }
        }

        window.draw(fade);

        // std::cout << fireworks.size() << std::endl;
        render(window);
        update(delta);

        window.display();
    }
}