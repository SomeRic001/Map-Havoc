#pragma once
#include <SFML/Graphics.hpp>

class MainMenu {
public:
    MainMenu(float width, float height);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedItemIndex() const;
    void processEvents(const sf::RenderWindow& window);

    sf::Text menu[5]; // Increase array size for the new menu item
    void updatePositions(float width, float height);
private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text title;
    sf::Text toggle;

  
};

