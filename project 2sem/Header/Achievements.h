#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class Achievements {
public:
    Achievements();

    void checkKillCount(int kills);
    void checkWaveCount(int wave);
    void checkScore(int score);

    void resetAchievements();
    void drawAchievements(sf::RenderWindow& window) ;

    bool isAchievementUnlocked(const std::string& achievementName) const;

private:
    std::unordered_map<std::string, bool> achievements;
    sf::Font font;
    sf::Text achievementText;
    sf::Text titleText;
    void unlockAchievement(const std::string& name);
};
