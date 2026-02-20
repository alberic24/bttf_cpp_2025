#pragma once
#include "Scene.hpp"
#include "GameScene.hpp"
#include "UI/MainMenu.hpp"
#include "UI/SettingsMenu.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

enum class GameState {
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
    
    sf::RenderWindow window;
    sf::Clock clock;
    sf::Font& font;
    sf::Text gameOverText;
    
    GameState state;
    std::unique_ptr<MainMenu> mainMenu;
    std::unique_ptr<SettingsMenu> settingsMenu;
    std::unique_ptr<GameScene> gameScene;
};