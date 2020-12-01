#pragma once

#include <SFML/Graphics.hpp>

#include "animation.h"

enum class Layer {
    Background,
    Frontground,
    COUNT
};

class Render: private sf::NonCopyable {  // TODO(ANDY) Надо класс что-ли сделать)))
 public:
    explicit Render(sf::RenderWindow& window);
    void update(sf::Time dt);
    void get_change();
    void draw();

 private:
    void loadTextures();
    void buildScene();
    void adaptPlayerPosition();
    void adaptPlayerVelocity();

 private:
    std::vector<AnimationManager> _manager;


 private:
    sf::RenderWindow& _window;
    sf::View _view;

    //SceneNode							mSceneGraph;
    //std::vector<SceneNode*>	mSceneLayers;  // Layer::COUNT - size

    sf::FloatRect						mWorldBounds;
    sf::Vector2f						mSpawnPosition;
};
