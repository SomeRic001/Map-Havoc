#include "Header/Achievements.h"

#include <iostream>

Achievements::Achievements() {
    achievements["Havoc Master"] = false;
    achievements["Wave Master"] = false;
    achievements["Half a millenia"] = false;

    if (!font.loadFromFile("Megamax.ttf")) {
        // handle error
    }

    // Initialize title text
    titleText.setFont(font);
    titleText.setString("Achievements");
    titleText.setCharacterSize(70);
    titleText.setFillColor(sf::Color::Yellow);
}

void Achievements::drawAchievements(sf::RenderWindow& window) {
    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    // Center the title text
    titleText.setPosition(windowWidth / 2.0f - titleText.getGlobalBounds().width / 2.0f, windowHeight / 4.0f - titleText.getGlobalBounds().height / 2.0f);
    window.draw(titleText);

    // Define the achievement descriptions
    std::unordered_map<std::string, std::string> achievementDescriptions = {
        {"Havoc Master", "You know the true meaning of Havoc. Kill 200 enemies."},
        {"Wave Master", "You are in a realm of your own. Reach Wave 8"},
        {"Half a millenia", "Cross 500 score"}
    };

    float yPosition = windowHeight / 2.0f; // Start from the middle of the screen
    for (const auto& achievement : achievements) {
        std::string fullText = "• " + achievement.first + ": " + achievementDescriptions[achievement.first]; // Combine name and description
        sf::Text text(fullText, font, 30); // Add bullet point
        text.setFillColor(achievement.second ? sf::Color::Green : sf::Color::Red);
        text.setPosition(windowWidth / 2.0f - text.getGlobalBounds().width / 2.0f, yPosition); // Center horizontally
        window.draw(text);
        yPosition += 60.0f; // Increment y-position with more spacing
    }
}


void Achievements::checkKillCount(int kills) {
    if (kills >= 200) {
        unlockAchievement("Havoc Master");
    }
}

void Achievements::checkWaveCount(int wave) {
    if (wave >= 8) {
        unlockAchievement("Wave Master");
    }
}

void Achievements::checkScore(int score) {
    if (score >= 500) {
        unlockAchievement("Half a millenia");
    }
}



void Achievements::unlockAchievement(const std::string& name) { 
    if (achievements.find(name) != achievements.end() && !achievements[name]) {
        achievements[name] = true; 
    } 
}

bool Achievements::isAchievementUnlocked(const std::string& achievementName) const {
    auto it = achievements.find(achievementName);
    if (it != achievements.end()) {
        return it->second;
    }
    return false;
}

void Achievements::resetAchievements() {
    for (auto& achievement : achievements) {
        achievement.second = false;
    }
}


