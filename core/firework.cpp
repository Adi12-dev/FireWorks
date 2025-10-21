#include "core/firework.h"
#include "core/rng.h"

// std
#include <cmath>

void Sparkel::burst(float burstSpeed, int num, sf::Color color, FireWork& firework)
{
    float d = 2 * M_PI / (float)num;
    float theta = 0.f;
    for (int i = 0; i < num; i++)
    {
        sf::Vector2f v = sf::Vector2f(cosf(theta), sinf(theta)) * burstSpeed; 

        firework.sparkels.emplace_back(
            1.5f + randomVal() * 0.5,           // lifespan
            stage + 1,                          // stage
            color,                              // color
            1.f,                                // radius
            pos,                                // pos
            v                                   // vel
        );

        // to make the burst more visually appealing
        sf::Vector2f v_side_sparkle = sf::Vector2f(randomVal(), randomVal()) * (burstSpeed * 0.5f);
        firework.sparkels.emplace_back(
            1.5f + randomVal() * 0.5,           // lifespan
            stage + 2,                          // stage
            color,                              // color
            1.f,                                // radius
            pos,                                // pos
            v + v_side_sparkle                  // vel
        );
        theta += d;
    }
}

int Sparkel::update(float delta, FireWork& firework)
{
    vel += sf::Vector2f(0, g) * delta;
    pos += vel * delta;
    lifespan -= delta;
    if (lifespan <= 0 && stage < firework.maxStages)
    {
        burst(50.f / (stage + 1) + (5.f + randomVal() * 5.f), 10 , color, firework);
    }
    return lifespan <= 0 ? 1 : 0;
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
    maxStages = stages;             // number of bursts

    sparkels.reserve(static_cast<int>(std::pow(20, stages)) + 1);
    sparkels.emplace_back(
        1.f,                        // lifespan
        0,                          // stage
        color,                      // color
        rad,                        // radius
        pos,                        // pos
        vel                         // vel

    );
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

void FireWork::draw(sf::RenderWindow& window)
{
    for (auto& s : sparkels)
    {
        s.draw(window);
    }

}

