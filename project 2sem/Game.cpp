#include <iostream> 
#include <iomanip> 
#include <fstream>
#include <vector>
#include <string>
#include "Header/Game.h"

Game::Game()
    : window(sf::VideoMode(1920, 1080), "MAP HAVOC"),achievements(),
    mainMenu(window.getSize().x, window.getSize().y),
    player(window.getSize().x / 2.0f, window.getSize().y / 2.0f),
    isMovingUp(false),
    isMovingDown(false),
    isMovingLeft(false),
    isMovingRight(false),
    isShooting(false),
    isMenuActive(true),
    isHowToPlayActive(false),
    isLeaderboardActive(false),
    isGameOver(false),
    isFullscreen(false),
    fps(0.0f),
    score(0),
    enemySpawnRate(100),
    wave(1),
    showNewWaveText(false), accumulatedTime(sf::Time::Zero),
    frameCount(0),
    powerupSpawnInterval(sf::seconds(30.0f)),killCount(0),powerupsUsed(0),
    isAchievementsActive(false)
    {

    window.setFramerateLimit(120);
    if (!powerupTextureStopEnemies.loadFromFile("Assets/hourglass.png")) {
        std::cout << "Error loading hourglass.png" << std::endl;
    }
    if (!powerupTextureIncreaseDamage.loadFromFile("Assets/flame.png")) {
        std::cout << "Error loading flame.png" << std::endl;
    }
    if (!powerupTextureFourD.loadFromFile("Assets/FourD.png")) { 
        std::cout << "Error loading FourD.png" << std::endl; 
    }

    powerupSpawnClock.restart();
    powerupEffectClock.restart();
    backToAcMenuText.setFont(font); 
    backToAcMenuText.setString("Back to Menu");
    backToAcMenuText.setCharacterSize(30); 
    backToAcMenuText.setFillColor(sf::Color::Red);
    backToAcMenuText.setPosition(window.getSize().x / 2.0f - backToMenuText.getGlobalBounds().width / 2.0f, window.getSize().y - 100.0f);
    if (!enemyTexture1.loadFromFile("Assets/Enemy1.png")) {
        std::cout << "Error loading Enemy1.png" << std::endl;
    }
    if (!enemyTexture2.loadFromFile("Assets/Enemy2.png")) {
        std::cout << "Error loading Enemy2.png" << std::endl;
    }
    if (!enemyTexture3.loadFromFile("Assets/Enemy3.png")) {
        std::cout << "Error loading Enemy3.png" << std::endl;
    }
    if (!enemyTexture4.loadFromFile("Assets/Enemy4.png")) {
        std::cout << "Error loading Enemy4.png" << std::endl;
    }

    // Load font
    if (!font.loadFromFile("MegaMax.ttf")) {
        std::cout << "Error loading font" << std::endl;
    }

    // Initialize new wave text
    newWaveText.setFont(font);
    newWaveText.setCharacterSize(70);
    newWaveText.setFillColor(sf::Color::Black);
    newWaveText.setString("New Wave...");
    newWaveText.setPosition(window.getSize().x / 2.0f - newWaveText.getGlobalBounds().width / 2.0f,
                            window.getSize().y / 2.0f - newWaveText.getGlobalBounds().height / 2.0f);
    waveText.setFont(font); // Assuming font is already loaded
    waveText.setCharacterSize(30);
    waveText.setFillColor(sf::Color::Black);
    waveText.setString("Wave 1");
    waveText.setPosition(window.getSize().x / 2.0f - waveText.getGlobalBounds().width / 2.0f, 10.0f);

    // Load and play menu music
    if (!menuMusic.openFromFile("Assets/MMmusic.wav")) {
        std::cout << "Error loading MMmusic.wav" << std::endl;
    }
    menuMusic.setLoop(true); // Set music to loop
    menuMusic.play(); // Start playing music

    // Load game music
    if (!GameMusic.openFromFile("Assets/GameMusic.wav")) {
        std::cout << "Error loading GameMusic.wav" << std::endl;
    }
    GameMusic.setLoop(true); // Set game music to loop

    // Load background texture for the game
    if (!backgroundTexture.loadFromFile("Assets/background.png")) {
        // handle error
        std::cout << "Error loading background.png" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    if (!gameOverMusic.openFromFile("Assets/gameover.wav")) {
        std::cout << "Error loading gameover music" << std::endl;
    }
    // Load power-up sound 
    if (!PowerupSoundBuffer.loadFromFile("Assets/powerup.wav")) { 
        std::cout << "Error loading powerup.wav" << std::endl;
    } 
    PowerupSound.setBuffer (PowerupSoundBuffer); // Set buffer for power-up sound
    // Load cursor texture
    if (!cursorTexture.loadFromFile("Assets/cross.png")) {
        // handle error
        std::cout << "Error loading cross.png" << std::endl;
    }
    cursorSprite.setTexture(cursorTexture);
    cursorSprite.setOrigin(cursorTexture.getSize().x / 2.0f, cursorTexture.getSize().y / 2.0f); // Center the cursor
    cursorSprite.setScale(0.1f, 0.1f); // Scale to 0.1 of its original size

    // Load font for FPS text
    if (!font.loadFromFile("Megamax.ttf")) {
        // handle error
        std::cout << "Error loading Megamax.ttf" << std::endl;
    }

    // Set up FPS text
    fpsText.setFont(font);
    fpsText.setCharacterSize(20); // Set font size
    fpsText.setFillColor(sf::Color::Black); // Set text color
    fpsText.setPosition(10.0f, 10.0f); // Position at top left

    // Set up score text
    scoreText.setFont(font);
    scoreText.setCharacterSize(20); // Set font size
    scoreText.setFillColor(sf::Color::Black); // Set text color
    scoreText.setPosition(10.0f, 40.0f); // Position below the FPS counter

    // Set up "How to Play" text
    howToPlayText.setFont(font);
    howToPlayText.setCharacterSize(30); // Increase font size
    howToPlayText.setFillColor(sf::Color::White); // Set text color
    howToPlayText.setString(
        "Controls:\n"
        "W - Move Up\n"
        "S - Move Down\n"
        "A - Move Left\n"
        "D - Move Right\n"
        "Mouse - Aim\n"
        "Left Click - Shoot\n\n\n\n"
        "Powerups:\n\n"
        "Hourglass -     Stop enemy movements\n"
        "Four Bullets -  Allows player to shoot in four direction\n"
        "Blue Flame -    Doubles the damage dealt\n\n\n"
        "Powerup Duration - 10 seconds\n\n\n\n\n\n"
        "Avoid enemies and shoot them to increase your score. Good luck!\n\n"
    );
    howToPlayText.setPosition(
        window.getSize().x / 2.0f - howToPlayText.getGlobalBounds().width / 2.0f,
        window.getSize().y / 2.0f - howToPlayText.getGlobalBounds().height / 2.0f - 50.0f
    ); // Center the how-to-play text

    // Set up "Back to Main Menu" text
    backToMenuText.setFont(font);
    backToMenuText.setCharacterSize(30); // Increase font size
    backToMenuText.setFillColor(sf::Color::Red); // Set text color
    backToMenuText.setString("Back to Main Menu");
    backToMenuText.setPosition(
        window.getSize().x / 2.0f - backToMenuText.getGlobalBounds().width / 2.0f,
        window.getSize().y / 2.0f + howToPlayText.getGlobalBounds().height / 2.0f + 50.0f
    ); // Center the back-to-menu text

    // Set up "Game Over" text
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50); // Set font size
    gameOverText.setFillColor(sf::Color::Red); // Set text color
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition(
        window.getSize().x / 2.0f - gameOverText.getGlobalBounds().width / 2.0f,
        window.getSize().y / 2.0f - gameOverText.getGlobalBounds().height / 2.0f - 100.0f
    ); // Center the game-over text

    // Set up final score text
    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(30); // Set font size
    finalScoreText.setFillColor(sf::Color::White); // Set text color
    finalScoreText.setPosition(
        window.getSize().x / 2.0f - finalScoreText.getGlobalBounds().width / 2.0f,
        window.getSize().y / 2.0f - finalScoreText.getGlobalBounds().height / 2.0f - 50.0f
    ); // Center the final score text

    // Set up "Main Menu" option
    mainMenuOption.setFont(font);
    mainMenuOption.setCharacterSize(30); // Set font size
    mainMenuOption.setFillColor(sf::Color::Red); // Set text color
    mainMenuOption.setString("Main Menu");
    mainMenuOption.setPosition(
        window.getSize().x / 2.0f - mainMenuOption.getGlobalBounds().width / 2.0f,
        window.getSize().y / 2.0f + gameOverText.getGlobalBounds().height / 2.0f + 50.0f
    ); // Center the main menu option

    // Set up "Play Again" option
    playAgainOption.setFont(font);
    playAgainOption.setCharacterSize(30); // Set font size
    playAgainOption.setFillColor(sf::Color::Red); // Set text color
    playAgainOption.setString("Play Again");
    playAgainOption.setPosition(
        window.getSize().x / 2.0f - playAgainOption.getGlobalBounds().width / 2.0f,
        window.getSize().y / 2.0f + gameOverText.getGlobalBounds().height / 2.0f + 100.0f
    ); // Center the play again option
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::F) {
                toggleFullscreen();
            }
            else if (event.key.code == sf::Keyboard::Escape && isFullscreen) {
                toggleFullscreen();
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            handleMouseInput(event.mouseButton.button, true);
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            handleMouseInput(event.mouseButton.button, false);
        }

        if (isMenuActive) {
            mainMenu.processEvents(window); // Process menu hover effect
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                for (int i = 0; i < 5; ++i) { // Updated loop to check all menu items
                    if (mainMenu.menu[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                        if (i == 0) { // Play button
                            // Reset the game state
                            isMenuActive = false;
                            isGameOver = false;
                            isLeaderboardActive = false;
                            isAchievementsActive = false; // Add this line
                            score = 0; // Reset score
                            killCount = 0; // Reset kill count
                            powerupsUsed = 0; // Reset power-ups used
                            scoreText.setString("Score: 0"); // Update the score text
                            enemies.clear(); // Clear existing enemies
                            bullets.clear(); // Clear existing bullets
                            player.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f); // Reset player position
                            // Reset movement controls
                            isMovingUp = false;
                            isMovingDown = false;
                            isMovingLeft = false;
                            isMovingRight = false;
                            // Stop menu music and play game music
                            menuMusic.stop();
                            GameMusic.play();
                        }
                        else if (i == 1) { // How to Play button
                            isMenuActive = false;
                            isHowToPlayActive = true;
                        }
                        else if (i == 2) { // Highscores button
                            isMenuActive = false;
                            isLeaderboardActive = true;
                            loadLeaderboard(); // Load the leaderboard scores
                        }
                        else if (i == 4) { // Exit button
                            window.close();
                        }
                        else if (i == 3) { // Achievements button
                            isMenuActive = false;
                            isAchievementsActive = true; // Add this line
                        }
                    }
                }
            }
        }
        else if (isHowToPlayActive || isLeaderboardActive || isAchievementsActive) { // Handle return from submenus
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (backToMenuText.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    isMenuActive = true;
                    isHowToPlayActive = false;
                    isLeaderboardActive = false;
                    isAchievementsActive = false;
                }
            }
            else {
                // Handle hover effect for the "Back to Main Menu" text
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (backToMenuText.getGlobalBounds().contains(window.mapPixelToCoords(mousePosition))) {
                    backToMenuText.setCharacterSize(40); // Expand on hover
                    backToMenuText.setPosition(
                        window.getSize().x / 2.0f - backToMenuText.getGlobalBounds().width / 2.0f,
                        window.getSize().y / 2.0f + howToPlayText.getGlobalBounds().height / 2.0f + 50.0f
                    ); // Re-center after resizing
                }
                else {
                    backToMenuText.setCharacterSize(30); // Default size
                    backToMenuText.setPosition(
                        window.getSize().x / 2.0f - backToMenuText.getGlobalBounds().width / 2.0f,
                        window.getSize().y / 2.0f + howToPlayText.getGlobalBounds().height / 2.0f + 50.0f
                    ); // Re-center after resizing
                }
            }
        }
        else if (isGameOver) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (mainMenuOption.getGlobalBounds().contains(window.mapPixelToCoords(mousePosition))) {
                    isGameOver = false;
                    isMenuActive = true;
                    score = 0; // Reset score
                    scoreText.setString("Score: 0"); // Update the score text
                    // Ensure the game state is reset for new game
                    enemies.clear(); // Clear existing enemies
                    bullets.clear(); // Clear existing bullets
                    player.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f); // Reset player position
                    isMovingUp = false;
                    isMovingDown = false;
                    isMovingLeft = false;
                    isMovingRight = false;
                    // Stop game music and play menu music
                    GameMusic.stop();
                    menuMusic.play();
                }
                else if (playAgainOption.getGlobalBounds().contains(window.mapPixelToCoords(mousePosition))) {
                    isGameOver = false;
                    score = 0; // Reset score
                    scoreText.setString("Score: 0"); // Update the score text
                    enemies.clear(); // Clear existing enemies
                    bullets.clear(); // Clear existing bullets
                    player.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f); // Reset player position
                    // Reset movement controls
                    isMovingUp = false;
                    isMovingDown = false;
                    isMovingLeft = false;
                    isMovingRight = false;
                    // Play game music again
                    GameMusic.play();
                }
            }
            else {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (mainMenuOption.getGlobalBounds().contains(window.mapPixelToCoords(mousePosition))) {
                    mainMenuOption.setCharacterSize(40); // Expand on hover
                    mainMenuOption.setPosition(
                        window.getSize().x / 2.0f - mainMenuOption.getGlobalBounds().width / 2.0f,
                        window.getSize().y / 2.0f + gameOverText.getGlobalBounds().height / 2.0f + 50.0f
                    ); // Re-center after resizing
                }
                else {
                    mainMenuOption.setCharacterSize(30); // Default size
                    mainMenuOption.setPosition(
                        window.getSize().x / 2.0f - mainMenuOption.getGlobalBounds().width / 2.0f,
                        window.getSize().y / 2.0f + gameOverText.getGlobalBounds().height / 2.0f + 50.0f
                    ); // Re-center after resizing
                }

                if (playAgainOption.getGlobalBounds().contains(window.mapPixelToCoords(mousePosition))) {
                    playAgainOption.setCharacterSize(40); // Expand on hover
                    playAgainOption.setPosition(
                        window.getSize().x / 2.0f - playAgainOption.getGlobalBounds().width / 2.0f,
                        window.getSize().y / 2.0f + gameOverText.getGlobalBounds().height / 2.0f + 100.0f
                    ); // Re-center after resizing
                }
                else {
                    playAgainOption.setCharacterSize(30); // Default size
                    playAgainOption.setPosition(
                        window.getSize().x / 2.0f - playAgainOption.getGlobalBounds().width / 2.0f,
                        window.getSize().y / 2.0f + gameOverText.getGlobalBounds().height / 2.0f + 100.0f
                    ); // Re-center after resizing
                }
            }
        }
        else {
            if (event.type == sf::Event::KeyPressed) {
                handlePlayerInput(event.key.code, true);
            }
            else if (event.type == sf::Event::KeyReleased) {
                handlePlayerInput(event.key.code, false);
            }
        }
    }
}


void Game::render() {
    updateScreenPositions();

    window.clear();
    if (isMenuActive) {
        mainMenu.draw(window);
    }
    else if (isHowToPlayActive) {
        window.draw(howToPlayText);
        window.draw(backToMenuText);
    }
    else if (isLeaderboardActive) {
        sf::Text leaderboardTitle;
        leaderboardTitle.setFont(font);
        leaderboardTitle.setCharacterSize(50);
        leaderboardTitle.setFillColor(sf::Color::Yellow);
        leaderboardTitle.setString("Leaderboard");
        leaderboardTitle.setPosition(
            window.getSize().x / 2.0f - leaderboardTitle.getGlobalBounds().width / 2.0f,
            window.getSize().y / 4.0f - leaderboardTitle.getGlobalBounds().height / 2.0f
        );
        window.draw(leaderboardTitle);

        sf::Text leaderboardText;
        leaderboardText.setFont(font);
        leaderboardText.setCharacterSize(30);
        leaderboardText.setFillColor(sf::Color::White);
        std::string leaderboardStr;
        for (size_t i = 0; i < leaderboard.size(); ++i) {
            leaderboardStr += std::to_string(i + 1) + ". " + std::to_string(leaderboard[i]) + "\n";
        }
        leaderboardText.setString(leaderboardStr);
        leaderboardText.setPosition(
            window.getSize().x / 2.0f - leaderboardText.getGlobalBounds().width / 2.0f,
            window.getSize().y / 2.0f - leaderboardText.getGlobalBounds().height / 2.0f
        );
        window.draw(leaderboardText);

        window.draw(backToMenuText);
    }
    else if (isAchievementsActive) { // Add this condition
        achievements.drawAchievements(window);
        window.draw(backToMenuText);
    }
    else if (isGameOver) {
        window.draw(gameOverText);
        window.draw(finalScoreText);
        window.draw(mainMenuOption);
        window.draw(playAgainOption);
    }
    else {
        window.draw(backgroundSprite); // Draw game background
        player.draw(window);

        for (const auto& enemy : enemies) {
            enemy.draw(window); // This line draws both the enemy and its health bar
        }

        for (const auto& bullet : bullets) {
            bullet.draw(window);
        }

        // Draw power-ups
        for (const auto& powerup : powerups) {
            powerup.draw(window);
        }
        window.draw(cursorSprite); // Draw custom cursor
        window.draw(scoreText); // Draw score
        window.draw(waveText);
        window.draw(fpsText);
        if (showNewWaveText) {
            window.draw(newWaveText); // Draw new wave text
        }

    }
    window.display();
}



void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePerFrame = sf::seconds(1.f / 120.f); // 120 FPS

    while (window.isOpen()) {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;

            processEvents();
            update();
        }

        render();
    }
}

void Game::handleMouseInput(sf::Mouse::Button button, bool isPressed) {
    if (button == sf::Mouse::Left) {
        isShooting = isPressed;
        if (isShooting) {
            // Get player position and aim direction
            sf::Vector2f playerPosition = player.getSprite().getPosition();
            sf::Vector2f aimDirection = window.mapPixelToCoords(sf::Mouse::getPosition(window)) - playerPosition;
            sf::Vector2f direction = aimDirection / std::sqrt(aimDirection.x * aimDirection.x + aimDirection.y * aimDirection.y);

            // Calculate angle from aim direction
            float angle = std::atan2(aimDirection.y, aimDirection.x);

            // Shoot bullets in four directions relative to the cursor
            bullets.emplace_back(playerPosition.x, playerPosition.y, direction);
            if (fourDActive) {
                sf::Vector2f direction90(std::cos(angle + 3.14159265f / 2.0f), std::sin(angle + 3.14159265f / 2.0f));
                sf::Vector2f direction_90(std::cos(angle - 3.14159265f / 2.0f), std::sin(angle - 3.14159265f / 2.0f));
                sf::Vector2f direction180(std::cos(angle + 3.14159265f), std::sin(angle + 3.14159265f));
                bullets.emplace_back(playerPosition.x, playerPosition.y, direction90);
                bullets.emplace_back(playerPosition.x, playerPosition.y, direction_90);
                bullets.emplace_back(playerPosition.x, playerPosition.y, direction180);
            }
        }
    }
}

void Game::toggleFullscreen() {
    if (isFullscreen) {
        window.create(sf::VideoMode(1920, 1080), "MAP HAVOC", sf::Style::Default);
        isFullscreen = false;
    }
    else {
        window.create(sf::VideoMode::getDesktopMode(), "MAP HAVOC", sf::Style::Fullscreen);
        isFullscreen = true;
    }
    // Update menu positions after resizing
    mainMenu.updatePositions(window.getSize().x, window.getSize().y);
}

void Game::spawnEnemy() {
    float x, y;
    int side = rand() % 4; // Random side: 0 = top, 1 = right, 2 = bottom, 3 = left

    switch (side) {
    case 0: // Top
        x = rand() % window.getSize().x;
        y = -50;
        break;
    case 1: // Right
        x = window.getSize().x + 50;
        y = rand() % window.getSize().y;
        break;
    case 2: // Bottom
        x = rand() % window.getSize().x;
        y = window.getSize().y + 50;
        break;
    case 3: // Left
        x = -50;
        y = rand() % window.getSize().y;
        break;
    }

    // Initialize selectedTexture to nullptr
    sf::Texture* selectedTexture = nullptr;
    int randomTexture = rand() % 4;
    switch (randomTexture) {
    case 0:
        selectedTexture = &enemyTexture1;
        break;
    case 1:
        selectedTexture = &enemyTexture2;
        break;
    case 2:
        selectedTexture = &enemyTexture3;
        break;
    case 3:
        selectedTexture = &enemyTexture4;
        break;
    }

    if (selectedTexture != nullptr) {
        enemies.emplace_back(x, y, *selectedTexture); // Pass the selected texture to the enemy constructor
    }
}
void Game::createBullet() {
    sf::Vector2f playerPosition = player.getSprite().getPosition();
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window); // Get cursor position in pixel coordinates
    sf::Vector2f worldMousePosition = window.mapPixelToCoords(mousePosition); // Convert to world coordinates
    // Calculate direction vector
    sf::Vector2f direction = worldMousePosition - playerPosition;

    // Normalize the direction vector
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction /= length;
    }

    bullets.emplace_back(playerPosition.x, playerPosition.y, direction);
}
void Game::update() {
    float deltaTime = deltaclock.restart().asSeconds(); // Capture the delta time

    if (!isMenuActive && !isGameOver) {
        // Update player
        player.update(isMovingUp, isMovingDown, isMovingLeft, isMovingRight, window);
        // Update enemies only if stopEnemiesActive is false
        if (!stopEnemiesActive) {
            for (auto& enemy : enemies) {
                enemy.update(player.getSprite().getPosition());
            }
        }

        // Update bullets and apply damage with increased damage effect
        for (auto& bullet : bullets) {
            bullet.update();
        }

        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [this](Bullet& bullet) {
            for (auto it = enemies.begin(); it != enemies.end(); ++it) {
                if (bullet.getBounds().intersects(it->getBounds())) {
                    int damage = 3; // Base damage
                    if (increaseDamageActive) {
                        damage *= 2; // Double the damage
                    }
                    it->takeDamage(damage);
                    if (it->isDefeated()) {
                        float enemySize = it->getSize();
                        enemies.erase(it);
                        killCount++; // Increment killCount here
                        if (Pew.openFromFile("Assets/Pew.wav")) {
                            Pew.play();
                        }
                        updateScore(enemySize);
                    }
                    return true;
                }
            }
            return false;
            }), bullets.end());


        // Check for other collisions
        checkCollision();

        // Update cursor position
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        cursorSprite.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

        // Update player rotation to face mouse pointer
        sf::Vector2f playerPosition = player.getSprite().getPosition();
        sf::Vector2f aimDirection = window.mapPixelToCoords(mousePosition) - playerPosition;
        float angle = std::atan2(aimDirection.y, aimDirection.x) * 180.0f / 3.14159265f + 90.0f;
        player.getSprite().setRotation(angle);

        // Update power-ups
        updatePowerups(deltaTime);

        // Check for power-up collisions with the player
        checkPowerupCollision();

        // Manage power-up effects duration
        if (increaseDamageActive && powerupEffectClock.getElapsedTime().asSeconds() > 10.0f) {
            increaseDamageActive = false;
        }
        if (stopEnemiesActive && powerupEffectClock.getElapsedTime().asSeconds() > 10.0f) {
            stopEnemiesActive = false;
        }
        if (fourDActive && powerupEffectClock.getElapsedTime().asSeconds() > 10.0f) {
            fourDActive = false;
        }

        // Check if it's time to spawn a new power-up
        if (powerupSpawnClock.getElapsedTime() >= powerupSpawnInterval) {
            spawnPowerup();
            powerupSpawnClock.restart(); // Reset the clock after spawning a power-up
        }

        // Check for game over condition
        if (isGameOver) {
            isGameOver = true;
       
        }
    }

    // Update wave and enemy spawn rate
    updateWave();
    updateEnemySpawnRate();
    // Update FPS display
    updateFPS();
    // Handle new wave text visibility
    if (showNewWaveText) {
       float elapsed = newWaveClock.getElapsedTime().asSeconds();
        if (elapsed >= 1.3f) {
            showNewWaveText = false; // Hide the text after 2 seconds
        }
    }

    // Enemy spawning logic
    static int spawnCounter = 0;
    spawnCounter++;
    if (spawnCounter >= enemySpawnRate) {
        spawnEnemy();
        spawnCounter = 0;
    }
        // Check achievements

    achievements.checkKillCount(killCount);
    achievements.checkWaveCount(wave);
    achievements.checkScore(score);
  

}

void Game::updateScore(float enemySize) {
    score += static_cast<int>(4 * enemySize); // Score is 4 times the size
    scoreText.setString("Score: " + std::to_string(score));
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::W) {
        isMovingUp = isPressed;
    }
    else if (key == sf::Keyboard::S) {
        isMovingDown = isPressed;
    }
    else if (key == sf::Keyboard::A) {
        isMovingLeft = isPressed;
    }
    else if (key == sf::Keyboard::D) {
        isMovingRight = isPressed;
    }
}


void Game::loadLeaderboard() {
    leaderboard.clear();
    std::ifstream file("Leaderboard.txt");
    int score;
    while (file >> score) {
        leaderboard.push_back(score);
    }
    file.close();

    // Ensure there are at least 5 scores
    while (leaderboard.size() < 5) {
        leaderboard.push_back(0);
    }
}

void Game::saveLeaderboard() {
    std::ofstream file("Leaderboard.txt");
    for (int score : leaderboard) {
        file << score << std::endl;
    }
    file.close();
}

void Game::updateLeaderboard(int newScore) {
    loadLeaderboard(); // Load the current leaderboard

    // Check if the new score is a high score
    for (size_t i = 0; i < leaderboard.size(); ++i) {
        if (newScore > leaderboard[i]) {
            leaderboard.insert(leaderboard.begin() + i, newScore);
            leaderboard.pop_back(); // Ensure only top 3 scores are kept
            break;
        }
    }

    saveLeaderboard(); // Save the updated leaderboard
}

void Game::checkCollision() {
    sf::FloatRect playerBounds = player.getSprite().getGlobalBounds();

    for (const auto& enemy : enemies) {
        sf::FloatRect enemyBounds = enemy.getBounds();
        if (playerBounds.intersects(enemyBounds)) {
            isGameOver = true;
            gameOverMusic.play(); 

            finalScoreText.setString("Score: " + std::to_string(score));
            finalScoreText.setPosition(
                window.getSize().x / 2.0f - finalScoreText.getGlobalBounds().width / 2.0f,
                window.getSize().y / 2.0f - finalScoreText.getGlobalBounds().height / 2.0f
            );

            // Update the leaderboard with the new score
            updateLeaderboard(score);

            break;
        }
    }
}

void Game::updateScreenPositions() {
    float width = window.getSize().x;
    float height = window.getSize().y;

    // Center GameOver elements
    centerText(gameOverText, width, height, 0, -100.0f);
    centerText(finalScoreText, width, height, 0, -50.0f);
    centerText(mainMenuOption, width, height, 0, 50.0f);
    centerText(playAgainOption, width, height, 0, 100.0f);

    // Center HowToPlay elements
    centerText(howToPlayText, width, height, 0, -50.0f);
    centerText(backToMenuText, width, height, 0, 50.0f);

    // Center Leaderboard elements
    sf::Text leaderboardTitle;
    leaderboardTitle.setFont(font);
    leaderboardTitle.setCharacterSize(50);
    leaderboardTitle.setFillColor(sf::Color::Yellow);
    leaderboardTitle.setString("Leaderboard");
    centerText(leaderboardTitle, width, height, 0, -height / 4.0f);
    sf::Text leaderboardText;
    leaderboardText.setFont(font);
    leaderboardText.setCharacterSize(30);
    leaderboardText.setFillColor(sf::Color::White);
    std::string leaderboardStr;
    for (size_t i = 0; i < leaderboard.size(); ++i) {
        leaderboardStr += std::to_string(i + 1) + ". " + std::to_string(leaderboard[i]) + "\n";
    }
    leaderboardText.setString(leaderboardStr);
    centerText(leaderboardText, width, height);
    centerText(backToMenuText, width, height, 0, height / 4.0f);
}

void Game::centerText(sf::Text& text, float width, float height, float offsetX, float offsetY) {
    text.setPosition(
        width / 2.0f - text.getGlobalBounds().width / 2.0f + offsetX,
        height / 2.0f - text.getGlobalBounds().height / 2.0f + offsetY
    );
}

void Game::updateEnemySpawnRate() {
    enemySpawnRate = std::max(30, 100 - (wave - 1) * 17); 
}

void Game::updateWave() {
    int newWave = score / 100 + 1; // Calculate the wave number
    if (newWave != wave) {
        wave = newWave;
        waveText.setString("Wave " + std::to_string(wave));
        waveText.setPosition(window.getSize().x / 2.0f - waveText.getGlobalBounds().width / 2.0f, 10.0f);

        // Clear existing enemies
        enemies.clear();
        showNewWaveText = true;
        // Update enemy spawn rate for the new wave
        if (wave > 1) {
            updateEnemySpawnRate();
        }

        // Spawn new enemies at the start of the wave
        for (int i = 0; i < wave * 5; ++i) {
            spawnEnemy();
        }

        // Show new wave text and reset the clock

        newWaveClock.restart();
    }
}
void Game::spawnPowerup() {
    float x = static_cast<int>(rand() % window.getSize().x);
    float y = static_cast<int>(rand() % window.getSize().y);

    int randomType = rand()%3;
    PowerupType type;
    sf::Texture* texture = nullptr;

    switch (randomType) {
    case 0:
        type = PowerupType::IncreaseDamage;
        texture = &powerupTextureIncreaseDamage;
        break;
    case 1:
        type = PowerupType::StopEnemies;
        texture = &powerupTextureStopEnemies;
        break;
    case 2:
        type = PowerupType::FourD;
        texture = &powerupTextureFourD;
        break;
    }

    if (texture) {
        powerups.emplace_back(type, *texture, x, y);
    }
}


void Game::updatePowerups(float deltaTime) {
    // Update and remove power-ups based on their lifetime
    for (auto it = powerups.begin(); it != powerups.end();) {
        it->update(deltaTime); // Update power-up's elapsed time
        if (it->isExpired()) { // Check if the power-up should be removed
            it = powerups.erase(it);
        }
        else {
            ++it;
        }
    }

    // Update active power-up effects
    if (increaseDamageActive && powerupEffectClock.getElapsedTime().asSeconds() > 10.0f) {
        increaseDamageActive = false; // Deactivate increase damage effect after 10 seconds 
    }
    if (stopEnemiesActive && powerupEffectClock.getElapsedTime().asSeconds() > 10.0f || score / 100 + 1 != wave) {
        stopEnemiesActive = false; // Deactivate stop enemies effect after 10 seconds 
    }
    if (fourDActive && powerupEffectClock.getElapsedTime().asSeconds() > 10.0f || score / 100 + 1 != wave) {
        fourDActive = false; // Deactivate four-direction shooting effect after 10 seconds 
    }
}

void Game::checkPowerupCollision() {
    // Check for collisions between player and power-ups
    for (auto it = powerups.begin(); it != powerups.end(); ) {
        if (player.getBounds().intersects(it->getBounds())) {
            // Apply power-up effect based on type
            switch (it->getType()) {
            case PowerupType::IncreaseDamage:
                increaseDamageActive = true;
                powerupEffectClock.restart();
                break;
            case PowerupType::StopEnemies:
                stopEnemiesActive = true;
                powerupEffectClock.restart();
                break;
            case PowerupType::FourD:
                fourDActive = true;
                powerupEffectClock.restart();
                break;
            }
            // Play power-up sound 
               PowerupSound.play();
            // Remove the power-up
            it = powerups.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Game::updateFPS() {
    // Get the time it took to render the previous frame
    sf::Time frameTime = fpsclock.restart();

    // Calculate FPS as the reciprocal of frame time in seconds
    float fps = 1.0f / frameTime.asSeconds();

    // Format FPS as a string for display
    std::string fpsString = "FPS: " + std::to_string(static_cast<int>(fps));

    // Update the text object with the FPS value
    fpsText.setString(fpsString);

}
void Game::applyPowerup(PowerupType type) {

    switch (type) {
    case PowerupType::IncreaseDamage:
        increaseDamageActive = true;
        powerupEffectClock.restart();
        powerupsUsed++;
        break;
    case PowerupType::StopEnemies:
        stopEnemiesActive = true;
        powerupEffectClock.restart();
        powerupsUsed++;
        break;
    case PowerupType::FourD:
        fourDActive = true;
        powerupEffectClock.restart();
        powerupsUsed++;
        break;
    }
}
