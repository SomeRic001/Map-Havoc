#include "Header/MainMenu.h"

MainMenu::MainMenu(float width, float height) {
    if (!font.loadFromFile("Megamax.ttf")) {
        // handle error
        printf("Error loading font");
    }

    // Title
    title.setFont(font);
    title.setFillColor(sf::Color::Yellow);
    title.setString("MAP HAVOC");
    title.setCharacterSize(100); // Adjust size as needed
    title.setStyle(sf::Text::Bold);

    // Play Game
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Play");
    menu[0].setCharacterSize(25); // Default size

    // How to Play
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("How to Play");
    menu[1].setCharacterSize(25); // Default size

    // Highscores
    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Highscores");
    menu[2].setCharacterSize(25); // Default size

    // Exit
    menu[3].setFont(font);
    menu[3].setFillColor(sf::Color::White);
    menu[3].setString("Achievements");
    menu[3].setCharacterSize(25); // Default size

    // Achievements
    menu[4].setFont(font);
    menu[4].setFillColor(sf::Color::White);
    menu[4].setString("Exit");
    menu[4].setCharacterSize(25); // Default size
    
 
        toggle.setFont(font);
        toggle.setFillColor(sf::Color::Yellow);
        toggle.setString("Press F to toggle full screen");
        toggle.setCharacterSize(30);
        toggle.setFillColor(sf::Color::Green);
    // Set initial positions
    updatePositions(width, height);
}

void MainMenu::updatePositions(float width, float height) {
    // Center title
    title.setPosition(sf::Vector2f(width / 2 - title.getGlobalBounds().width / 2,
        height / 3 - title.getGlobalBounds().height / 2));

    // Center Play button
    menu[0].setPosition(sf::Vector2f(width / 2 - menu[0].getGlobalBounds().width / 2,
        height / 2));

    // Center How to Play button below Play
    menu[1].setPosition(sf::Vector2f(width / 2 - menu[1].getGlobalBounds().width / 2,
        height / 2 + 60));

    // Center Highscores button below How to Play
    menu[2].setPosition(sf::Vector2f(width / 2 - menu[2].getGlobalBounds().width / 2,
        height / 2 + 120));

    // Center Achievements button below Highscore
    menu[3].setPosition(sf::Vector2f(width / 2 - menu[3].getGlobalBounds().width / 2,
        height / 2 + 180));
    // Center Exit button below Achievements
    menu[4].setPosition(sf::Vector2f(width / 2 - menu[4].getGlobalBounds().width / 2,
        height / 2 + 240));

    toggle.setPosition(sf::Vector2f(width / 2 - toggle.getGlobalBounds().width / 2, height / 2 + 500));

}

void MainMenu::processEvents(const sf::RenderWindow& window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    for (int i = 0; i < 5; i++) { // Update loop to process all menu items
        if (menu[i].getGlobalBounds().contains(window.mapPixelToCoords(mousePosition))) {
            if (menu[i].getString()[0] != '>') {
                menu[i].setString("> " + menu[i].getString());
            }
            menu[i].setCharacterSize(30); // Expand on hover
        }
        else {
            std::string menuItem = menu[i].getString();
            if (menuItem[0] == '>') {
                menuItem = menuItem.substr(2); // Remove '>' on unhover
                menu[i].setString(menuItem);
            }
            menu[i].setCharacterSize(24); // Default size
        }
    }
}

void MainMenu::draw(sf::RenderWindow& window) {
    window.clear(sf::Color::Black); // Clear window with black color
    window.draw(title);
    for (int i = 0; i < 5; i++) { // Assuming there are 5 menu items
        window.draw(menu[i]);
    }
    window.draw(toggle);
}
