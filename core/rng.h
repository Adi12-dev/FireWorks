#pragma once

#include <random>
#include <SFML/Graphics/Color.hpp>

static float randomVal()
{
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_real_distribution<float> dist(-1.f, 1.f);

    return dist(gen);
}