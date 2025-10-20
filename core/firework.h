#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

#define g 19.8f

class FireWork;

struct Sparkel
{
    float lifespan = 1.f;
    int stage = 0;          // stages of sparkels
    sf::Color color{255, 255, 255};
    float rad{1.f};
    sf::Vector2f pos{0.f, 0.f};
    sf::Vector2f vel{0.f, 0.f};
    float burstSpeed = 30.f;


    Sparkel() = default;
    Sparkel(float lifespan, int stage, sf::Color color, float radius, sf::Vector2f pos, sf::Vector2f vel)
        : lifespan{lifespan}, stage{stage}, color{color}, rad{radius}, pos{pos}, vel{vel} {}

    int update(float delta, FireWork& firework);    // return 1 when sparkel is done
    void draw(sf::RenderWindow& window);
    void burst(float burstSpeed, int num, sf::Color color, FireWork& firework); 
};


class FireWork
{
public:
    int stage{0};   // 0 -> fireball, 1 -> sparkels stage 0 , 2 -> sparkels stage 1, ....
    int maxStages{1};
    std::vector<Sparkel> sparkels;


    FireWork(sf::Vector2f pos, sf::Vector2f vel, float rad, sf::Color color = sf::Color(255, 255, 255, 255), int stages = 1);
    void draw(sf::RenderWindow& window);
    int update(float delta);
};

static float randomVal()
{
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_real_distribution<float> dist; // reused
    dist.param(std::uniform_real_distribution<float>::param_type(-1.f, 1.f));
    return dist(gen);

}