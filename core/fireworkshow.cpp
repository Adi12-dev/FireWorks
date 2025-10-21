#include "core/fireworkshow.h"
#include "core/rng.h"

// std
#include <iostream>

void FireWorkShow::setShowSize(int width, int height)
{
    if(fullScreen)
    {
        std::cerr << "Video Mode is already set to Full Screen" << std::endl;
    }
    else
    {
        windowWidth = width;
        windowHeight = height;
        std::cout << "Video Mode: " << windowWidth << " x " << windowHeight << std::endl;
    }
}

void FireWorkShow::setShowModeFullScreen()
{
    std::cout << "Video Mode: Full Screen" << std::endl;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    windowWidth = desktop.width;
    windowHeight = desktop.height;
}

void FireWorkShow::render(sf::RenderWindow& window)
{
    for (int i = 0; i < fireworks.size(); i++)
    {
        fireworks[i].draw(window);
    }
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

void FireWorkShow::runApp()
{
    sf::RenderWindow window(
        sf::VideoMode(windowWidth, windowHeight),
        "FireWorks Show",
        sf::Style::Titlebar | sf::Style::Close      // for no Resize
    );

    sf::RectangleShape fade(sf::Vector2f(windowWidth, windowHeight));
    fade.setFillColor(sf::Color(0, 0, 0, 20));      // Low alpha => long trail, high alpha => short trail

    window.setFramerateLimit(60);
    float delta = 1.f / 60.f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                auto mousepos = sf::Mouse::getPosition(window);
                newFireWork(mousepos.x, mousepos.y);
                
            }
        }

        window.draw(fade);

        render(window);
        update(delta);

        window.display();
    }
}

void FireWorkShow::newFireWork(int posX, int posY)
{
    sf::Vector2f vel(0.f, -250.f + randomVal() * 50);
    sf::Color col(randomVal() * 127 + 128, randomVal() * 127 + 128, randomVal() * 127 + 128);
    fireworks.emplace_back(
        sf::Vector2f(posX, posY),       // pos
        vel,                            // vel
        2.f,                            // radius of fireball
        col,                            // color  
        2                               // stages,     2 looks the best
    );
}

