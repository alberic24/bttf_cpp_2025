#pragma once
#include "Scene.hpp"
#include "GameScene.hpp"
#include "UI/MainMenu.hpp"
#include "UI/SettingsMenu.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <string>

enum class GameState {
    Intro,
    MainMenu,
    Settings,
    Playing,
    GameOver,
    Quit
};

class Game {
public:
    Game();
    ~Game();
    
    void run();
    
private:
    void handleEvents();
    void update(float dt);
    void render();
    void drawIntro();
    
    sf::RenderWindow window;
    sf::Clock clock;
    sf::Font& font;
    sf::Text gameOverText;
    
    // Intro
    int currentSlide = 0;
    float slideTimer = 0.0f;
    float textAlpha = 0.0f;
    bool fadingIn = true;
    std::vector<std::string> slides;
    sf::Text slideText;
    sf::Text skipText;
    sf::RectangleShape introBackground;
    
    GameState state;
    std::unique_ptr<MainMenu> mainMenu;
    std::unique_ptr<SettingsMenu> settingsMenu;
    std::unique_ptr<GameScene> gameScene;
};