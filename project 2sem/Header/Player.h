#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player(float startX, float startY, float speed = 1.3f);
    void update(bool isMovingUp, bool isMovingDown, bool isMovingLeft, bool isMovingRight, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;
    sf::Sprite& getSprite();
    sf::FloatRect getBounds() const;
    void setPosition(float x, float y);
    void setSpeed(float newSpeed);
   
  

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f position;
    float speed;
   
   
};
