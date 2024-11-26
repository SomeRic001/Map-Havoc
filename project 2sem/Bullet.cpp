#include "Header/Bullet.h"
#include <cmath>

Bullet::Bullet(float startX, float startY, sf::Vector2f direction) : speed(10.0f) {
    shape.setRadius(5.0f); // Bullet size
    shape.setFillColor(sf::Color::Blue); // Bullet color
    shape.setPosition(startX, startY);
    shape.setOrigin(shape.getRadius(), shape.getRadius());

    // Set velocity based on normalized direction
    velocity = direction * speed;
}

void Bullet::update() {
    shape.move(velocity);
}

void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::FloatRect Bullet::getBounds() const {
    return shape.getGlobalBounds();
}
