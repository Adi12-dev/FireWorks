#pragma once

#include "core/firework.h"

class FireWorkShow
{
public:
    void setShowSize(int width, int height);
    void setShowModeFullScreen();
    void render(sf::RenderWindow& window);
    void update(float delta);
    void runApp();
    void newFireWork(int posX, int posY);

private:
    bool fullScreen{false};
    int windowWidth{800};
    int windowHeight{600};
    std::vector<FireWork> fireworks;
};