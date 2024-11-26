#include "Header/Powerups.h"

Powerup::Powerup(PowerupType type, const sf::Texture& texture, float x, float y)
    : type(type), duration(10.0f), elapsedTime(0.0f) {
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setScale(0.5f, 0.5f); // Adjust size as needed
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
}

void Powerup::update(float deltaTime) {
    elapsedTime += deltaTime;
}

void Powerup::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

bool Powerup::isExpired() const {
    return elapsedTime >= duration;
}

PowerupType Powerup::getType() const {
    return type;
}

sf::FloatRect Powerup::getBounds() const {
    return sprite.getGlobalBounds();
}
