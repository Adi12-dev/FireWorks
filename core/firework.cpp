#include "core/firework.h"
#include "core/rng.h"

// std
#include <cmath>

void Sparkle::burst(float burstSpeed, int num, sf::Color color, FireWork& firework)
{
    float d = 2 * M_PI / (float)num;
    float theta = 0.f;
    for (int i = 0; i < num; i++)
    {
        sf::Vector2f v = sf::Vector2f(cosf(theta), sinf(theta)) * burstSpeed; 

        firework.sparkles.emplace_back(
            1.5f + randomVal() * 0.5,           // lifespan
            stage + 1,                          // stage
            color,                              // color
            1.f,                                // radius
            pos,                                // pos
            v                                   // vel
        );

        // to make the burst more visually appealing
        sf::Vector2f v_side_sparkle = sf::Vector2f(randomVal(), randomVal()) * (burstSpeed * 0.5f);
        firework.sparkles.emplace_back(
            1.5f + randomVal() * 0.5,           // lifespan
            firework.maxStages,                 // stage
            color,                              // color
            1.f,                                // radius
            pos,                                // pos
            v + v_side_sparkle                  // vel
        );
        theta += d;
    }
}

int Sparkle::update(float delta, FireWork& firework)
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

void Sparkle::draw(sf::RenderWindow& window)
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

    sparkles.reserve(static_cast<int>(std::pow(20, stages)) + 1);
    sparkles.emplace_back(
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
    for(int i = sparkles.size() - 1; i >= 0; i--)
    {
        int done = sparkles[i].update(delta, *this);
        if (done)
        {
            std::swap(sparkles[i], sparkles.back());
            sparkles.pop_back();
        }
    }

    return sparkles.size() == 0 ? 1 : 0;
}

void FireWork::draw(sf::RenderWindow& window)
{
    for (auto& s : sparkles)
    {
        s.draw(window);
    }

}

