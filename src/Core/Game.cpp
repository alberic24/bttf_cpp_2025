#include "Core/Game.hpp"
#include "Core/ResourceManager.hpp"
#include "Utils/Config.hpp"
#include <SFML/Window/Event.hpp>

Game::Game() 
    : window(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), Config::WINDOW_TITLE),
      font(ResourceManager::getInstance().getFont()),
      state(GameState::MainMenu) {
    
    Config::settings.load();
    
    window.close();
    if (Config::settings.fullscreen) {
        window.create(sf::VideoMode::getDesktopMode(), Config::WINDOW_TITLE, sf::Style::Fullscreen);
    } else {
        window.create(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), Config::WINDOW_TITLE, sf::Style::Default);
    }
    
    window.setFramerateLimit(60);
    
    mainMenu = std::make_unique<MainMenu>(font);
    settingsMenu = std::make_unique<SettingsMenu>(font, &window);
    
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER\n\nAppuyez sur ENTREE pour rejouer\nESCAPE pour revenir au menu");
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    sf::FloatRect bounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    gameOverText.setPosition(Config::WINDOW_WIDTH / 2.f, Config::WINDOW_HEIGHT / 2.f);
}

Game::~Game() {
    Config::settings.save();
}

void Game::run() {
    while (window.isOpen() && state != GameState::Quit) {
        handleEvents();
        
        float dt = clock.restart().asSeconds();
        dt = std::min(dt, 0.1f);
        
        update(dt);
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            state = GameState::Quit;
            window.close();
        }
        
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            if (state == GameState::Playing) {
                state = GameState::MainMenu;
                gameScene.reset();
            } else if (state == GameState::Settings) {
                state = GameState::MainMenu;
            } else if (state == GameState::GameOver) {
                state = GameState::MainMenu;
                gameScene.reset();
            }
        }
    }
}

void Game::update(float dt) {
    switch (state) {
        case GameState::MainMenu: {
            sf::Music& music = ResourceManager::getInstance().getMenuMusic();
            if (music.getStatus() != sf::Music::Playing) {
                music.play();
            }
            
            MenuAction action = mainMenu->update(window);
            if (action == MenuAction::StartGame) {
                state = GameState::Playing;
                gameScene = std::make_unique<GameScene>(font, window);
                music.stop();
            } else if (action == MenuAction::Settings) {
                state = GameState::Settings;
            } else if (action == MenuAction::Quit) {
                state = GameState::Quit;
            }
            break;
        }
        
        case GameState::Settings: {
            if (settingsMenu->update(window)) {
                state = GameState::MainMenu;
            }
            break;
        }
        
        case GameState::Playing: {
            if (gameScene) {
                gameScene->handleInput(window);
                gameScene->update(dt);
                
                if (!gameScene->isPlayerAlive()) {
                    state = GameState::GameOver;
                    gameScene.reset();
                }
            }
            break;
        }
        
        case GameState::GameOver: {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
                sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                state = GameState::Playing;
                gameScene = std::make_unique<GameScene>(font, window);
            }
            break;
        }
        
        default:
            break;
    }
}

void Game::render() {
    window.clear(sf::Color(20, 20, 30));
    
    switch (state) {
        case GameState::MainMenu:
            mainMenu->draw(window);
            break;
            
        case GameState::Settings:
            settingsMenu->draw(window);
            break;
            
        case GameState::Playing:
            if (gameScene) {
                gameScene->draw(window);
            }
            break;
            
        case GameState::GameOver:
            window.draw(gameOverText);
            break;
            
        default:
            break;
    }
    
    window.display();
}