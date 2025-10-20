#include "core/firework.h"
#include <iostream>
#include <cmath>


int Sparkel::update(float delta, FireWork& firework)
{
    vel += sf::Vector2f(0, g) * delta;
    pos += vel * delta;
    lifespan -= delta;
    if (lifespan <= 0 && stage < 2)
    {
        burst(50.f / (stage + 1) + randomVal() * 10, 10 , color, firework);
    }
    return lifespan <= 0 ? 1 : 0;
}

void Sparkel::burst(float burstSpeed, int num, sf::Color color, FireWork& firework)
{
    float d = 2 * M_PI / (float)num;
    float theta = 0.f;
    for (int i = 0; i < num; i++)
    {
        firework.sparkels.emplace_back(
            1.5f + randomVal() * 0.5,                        // lifespan
            stage + 1,                  // stage
            color,                      // color
            1.f,                        // radius
            pos,                        // pos
            sf::Vector2f(cosf(theta), sinf(theta)) * burstSpeed      // vel
        );
        theta += d;
    }
}

void Sparkel::draw(sf::RenderWindow& window)
{
    sf::CircleShape circle(rad);
    circle.setOrigin(rad, rad);
    circle.setPosition(pos);
    circle.setFillColor(color);
    window.draw(circle);
}


FireWork::FireWork(sf::Vector2f pos, sf::Vector2f vel, float rad, sf::Color color, int stages)
{
    maxStages = stages;
    
    sparkels.emplace_back(
        1.f,                        // lifespan
        0,                          // stage
        color,                      // color
        rad,                        // radius
        pos,                        // pos
        vel                         // vel
    );
}

void FireWork::draw(sf::RenderWindow& window)
{
    for (auto& s : sparkels)
    {
        s.draw(window);
    }

}

int FireWork::update(float delta)
{
    for(int i = sparkels.size() - 1; i >= 0; i--)
    {
        int done = sparkels[i].update(delta, *this);
        if (done)
        {
            std::swap(sparkels[i], sparkels.back());
            sparkels.pop_back();
        }
    }

    return sparkels.size() == 0 ? 1 : 0;
}