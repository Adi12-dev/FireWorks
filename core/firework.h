#pragma once

#include <SFML/Graphics.hpp>
#include <vector>


constexpr float g = 15.f;

class FireWork;

struct Sparkle
{
    float lifespan = 1.f;
    int stage = 0;                      // stages of sparkles
    sf::Color color{255, 255, 255};
    float rad{1.f};
    sf::Vector2f pos{0.f, 0.f};
    sf::Vector2f vel{0.f, 0.f};
    float burstSpeed{30.f};


    Sparkle() = default;
    Sparkle(float lifespan, int stage, sf::Color color, float radius, sf::Vector2f pos, sf::Vector2f vel)
        : lifespan{lifespan}, stage{stage}, color{color}, rad{radius}, pos{pos}, vel{vel} {}

    void burst(float burstSpeed, int num, sf::Color color, FireWork& firework); 
    int update(float delta, FireWork& firework);    // return 1 when sparkle is done
    void draw(sf::RenderWindow& window);
};


class FireWork
{
public:
    int maxStages{1};
    std::vector<Sparkle> sparkles;


    FireWork(sf::Vector2f pos, sf::Vector2f vel, float rad, sf::Color color = sf::Color(255, 255, 255), int stages = 2);
    int update(float delta);
    void draw(sf::RenderWindow& window);
};