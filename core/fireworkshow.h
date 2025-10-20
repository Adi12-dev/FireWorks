#pragma once

#include "core/firework.h"

class FireWorkShow
{
public:
    void update(float delta);
    void render(sf::RenderWindow& window);
    void runApp();
    void setWidthHeight(int width, int height);

private:
    int windowWidth{800};
    int windowHeight{600};
    std::vector<FireWork> fireworks;
};