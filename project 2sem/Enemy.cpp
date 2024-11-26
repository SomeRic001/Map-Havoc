#include "Header/Enemy.h"
#include <cmath>
#include <cstdlib> 

Enemy::Enemy(float startX, float startY, const sf::Texture& texture)
    : position(startX, startY), speed(0.4f) {


    size = 0.3f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (1.1f - 0.3f)));

    sprite.setTexture(texture);
    sprite.setScale(size, size);
    sprite.setPosition(position);
    sprite.setOrigin(SPRITE_WIDTH / 2.0f, SPRITE_HEIGHT / 2.0f);

    maxHealth = static_cast<int>(size * 10);
    health = maxHealth;

    // Initialize health bar
    healthBar.setSize(sf::Vector2f(size * 100, 10));
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setPosition(position.x, position.y - sprite.getGlobalBounds().height / 2 - 10);
}

void Enemy::update(const sf::Vector2f& playerPosition) {
    // Calculate direction vector
    sf::Vector2f direction = playerPosition - position;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= length;

    position += direction * speed;
    sprite.setPosition(position);

    // Center and adjust the health bar
    healthBar.setPosition(position.x - healthBar.getSize().x / 2, position.y - sprite.getGlobalBounds().height / 2 - 10);
    healthBar.setSize(sf::Vector2f((static_cast<float>(health) / maxHealth) * (size * 100), 5));
}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
    window.draw(healthBar);
}

void Enemy::takeDamage(int damage) {
    health -= damage; if (health < 0) health = 0;
}

bool Enemy::isDefeated() const {
    return health <= 0;
}

sf::FloatRect Enemy::getBounds() const {
    return sprite.getGlobalBounds();
}

float Enemy::getSize() const {
    return size;
}

float Enemy::getSpeed() const {
    return speed;
}

void Enemy::setSpeed(float newSpeed) {
    speed = newSpeed;
}
