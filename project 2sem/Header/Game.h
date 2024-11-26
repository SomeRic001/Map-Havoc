#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "MainMenu.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Powerups.h"
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <iostream>
#include "Achievements.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void updateScore(float amount);
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void handleMouseInput(sf::Mouse::Button button, bool isPressed);
    void toggleFullscreen();
    void updateFPS();
    void spawnEnemy();
    void createBullet();
    void checkCollision();
    void updateEnemySpawnRate();
    void updateWave();
    void centerText(sf::Text& text, float width, float height, float offsetX = 0, float offsetY = 0);
    void updateScreenPositions();
    void loadLeaderboard();
    void saveLeaderboard();
    void updateLeaderboard(int newScore);
    void spawnPowerup(); // New function to spawn power-ups
    void updatePowerups(float deltaTime); // New function to update power-ups
    void checkPowerupCollision();
    void applyPowerup(PowerupType type); // New function to apply power-up effects
    sf::RenderWindow window;
    MainMenu mainMenu;
    Player player;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    std::vector<Powerup> powerups; // Vector to hold power-ups
    bool isMovingUp, isMovingDown, isMovingLeft, isMovingRight, isShooting;
    bool isMenuActive;
    bool isHowToPlayActive;
    bool isGameOver;
    bool isFullscreen;
    bool isLeaderboardActive;
    bool isAchievementsActive;
    int killCount;
    int powerupsUsed;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture cursorTexture;
    sf::Sprite cursorSprite;

    sf::Texture enemyTexture1; // Declare enemy textures
    sf::Texture enemyTexture2;
    sf::Texture enemyTexture3;
    sf::Texture enemyTexture4;

    sf::Texture powerupTextureIncreaseDamage;
    sf::Texture powerupTextureStopEnemies;
    sf::Texture powerupTextureFourD; // Declare the new FourD power-up texture

    sf::Font font;
    sf::Text fpsText; // Text to display FPS
    sf::Clock clock; // Clock to measure time for FPS calculation
    float fps; // Variable to store FPS value
    sf::Time accumulatedTime; // Accumulated frame time
    unsigned int frameCount; // Number of frames in the accumulation period
  
    sf::Clock fpsclock;
    sf::Clock deltaclock;
    sf::Text scoreText;
    sf::Text howToPlayText;
    sf::Text backToMenuText;
    sf::Text gameOverText;
    sf::Text finalScoreText;
    sf::Text mainMenuOption;
    sf::Text playAgainOption;
    sf::Text waveText;
    sf::Text newWaveText;
    sf::Text backToAcMenuText;
    sf::Clock enemySpawnClock;
    sf::Clock bulletClock;
    sf::Clock newWaveClock;
    sf::Clock powerupSpawnClock; // Clock for spawning power-ups
    sf::Clock powerupEffectClock; // Clock for power-up effects
    sf::Time powerupSpawnInterval;

    sf::Music GameMusic;
    sf::Music menuMusic;
    sf::Music Pew;
    sf::Music gameOverMusic; 
    sf::Sound PowerupSound;
    sf::SoundBuffer PowerupSoundBuffer;
    bool showNewWaveText;
    int score;
    int enemySpawnRate;
    int wave;

    std::vector<int> leaderboard;

    // Power-up effects
    bool increaseDamageActive = false;
    bool stopEnemiesActive = false;
    bool fourDActive = false; // Add flag for FourD power-up
    Achievements achievements;
};

