#include "Header/Player.h"

Player::Player(float startX, float startY, float speed) : position(startX, startY), speed(1.5) { 
    texture.loadFromFile("Assets/player.png");
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f); // Center the sprite
    sprite.setScale(1.1f, 1.1f); // Scale to 110% of its original size
}

void Player::update(bool isMovingUp, bool isMovingDown, bool isMovingLeft, bool isMovingRight, const sf::RenderWindow& window) {
    // Movement logic
    if (isMovingUp) position.y -= speed;
    if (isMovingDown) position.y += speed;
    if (isMovingLeft) position.x -= speed;
    if (isMovingRight) position.x += speed;

    // Prevent moving out of window bounds
    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;
    if (position.x > window.getSize().x) position.x = window.getSize().x;
    if (position.y > window.getSize().y) position.y = window.getSize().y;

    sprite.setPosition(position);
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::Sprite& Player::getSprite() {
    return sprite;
}

void Player::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
    sprite.setPosition(position);
}

void Player::setSpeed(float newSpeed) {
    speed = newSpeed;
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}
