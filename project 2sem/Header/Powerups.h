#pragma once
#include <SFML/Graphics.hpp>

enum class PowerupType {
    IncreaseDamage,
    StopEnemies,
    FourD
};

class Powerup {
public:
    Powerup(PowerupType type, const sf::Texture& texture, float x, float y);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    bool isExpired() const;
    PowerupType getType() const;
    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;
    PowerupType type;
    float duration; // Duration for which the power-up should be on screen (e.g., 10 seconds)
    float elapsedTime; // Elapsed time since the power-up was created
};
