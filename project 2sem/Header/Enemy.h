#include <SFML/Graphics.hpp>
#include <vector>

class Enemy {
public:
    Enemy(float startX, float startY, const sf::Texture& texture);
    void update(const sf::Vector2f& playerPosition);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
    float getSize() const;
    float getSpeed() const;
    void setSpeed(float newSpeed);
    void takeDamage(int damage);
    bool isDefeated() const;

private:
    sf::Sprite sprite;
    sf::Vector2f position;
    float speed;
    float size;
    int health;
    int maxHealth;
    sf::RectangleShape healthBar;

    void selectRandomSprite(const sf::Texture& texture);

    static const int SPRITE_WIDTH = 64;
    static const int SPRITE_HEIGHT = 64;
};
