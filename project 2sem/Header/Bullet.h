#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(float startX, float startY, sf::Vector2f direction); // Constructor with three arguments

    void update();
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;

private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float speed;
};
