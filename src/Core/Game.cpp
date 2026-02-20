#include "Core/Game.hpp"
#include "Core/ResourceManager.hpp"
#include "Utils/Config.hpp"
#include <SFML/Window/Event.hpp>

Game::Game() 
    : window(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), Config::WINDOW_TITLE),
      font(ResourceManager::getInstance().getFont()),
      state(GameState::Intro) {
    
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
    
    // Game Over text
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER\n\nAppuyez sur ENTREE pour rejouer\nESCAPE pour revenir au menu");
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    sf::FloatRect bounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    gameOverText.setPosition(Config::WINDOW_WIDTH / 2.f, Config::WINDOW_HEIGHT / 2.f);
    
    // Slides intro
    slides = {
        "2157.\nLa Terre n'est plus ce qu'elle etait.",
        "Des creatures venues des abysses ont tout detruit.\nLes villes, les gouvernements, les espoirs.",
        "Tu es le dernier.\nBats-toi. Survive."
    };
    
    slideText.setFont(font);
    slideText.setCharacterSize(36);
    slideText.setFillColor(sf::Color::White);
    slideText.setString(slides[0]);
    sf::FloatRect slideBounds = slideText.getLocalBounds();
    slideText.setOrigin(slideBounds.width / 2.f, slideBounds.height / 2.f);
    slideText.setPosition(Config::WINDOW_WIDTH / 2.f, Config::WINDOW_HEIGHT / 2.f);
    
    skipText.setFont(font);
    skipText.setCharacterSize(18);
    skipText.setFillColor(sf::Color(180, 180, 180));
    skipText.setString("ESPACE ou CLIC pour continuer");
    sf::FloatRect skipBounds = skipText.getLocalBounds();
    skipText.setOrigin(skipBounds.width / 2.f, skipBounds.height / 2.f);
    skipText.setPosition(Config::WINDOW_WIDTH / 2.f, Config::WINDOW_HEIGHT - 60.f);
    
    introBackground.setSize(sf::Vector2f(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
    introBackground.setFillColor(sf::Color(5, 5, 15));
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
        
        // Avancer dans les slides
        if (state == GameState::Intro) {
            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) ||
                (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)) {
                currentSlide++;
                if (currentSlide >= (int)slides.size()) {
                    state = GameState::MainMenu;
                } else {
                    slideText.setString(slides[currentSlide]);
                    sf::FloatRect b = slideText.getLocalBounds();
                    slideText.setOrigin(b.width / 2.f, b.height / 2.f);
                    slideText.setPosition(Config::WINDOW_WIDTH / 2.f, Config::WINDOW_HEIGHT / 2.f);
                    textAlpha = 0.f;
                    fadingIn = true;
                }
            }
        }
        
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            if (state == GameState::Intro) {
                state = GameState::MainMenu;
            } else if (state == GameState::Playing) {
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
        case GameState::Intro: {
            // Fade in du texte
            if (fadingIn) {
                textAlpha += dt * 120.f;
                if (textAlpha >= 255.f) {
                    textAlpha = 255.f;
                    fadingIn = false;
                }
            }
            slideText.setFillColor(sf::Color(255, 255, 255, (sf::Uint8)textAlpha));
            skipText.setFillColor(sf::Color(180, 180, 180, (sf::Uint8)textAlpha));
            break;
        }
        
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
        case GameState::Intro:
            drawIntro();
            break;
            
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

void Game::drawIntro() {
    float W = (float)window.getSize().x;
    float H = (float)window.getSize().y;
    
    introBackground.setSize(sf::Vector2f(W, H));
    
    sf::FloatRect sb = slideText.getLocalBounds();
    slideText.setOrigin(sb.width / 2.f, sb.height / 2.f);
    slideText.setPosition(W / 2.f, H / 2.f);
    
    sf::FloatRect kb = skipText.getLocalBounds();
    skipText.setOrigin(kb.width / 2.f, kb.height / 2.f);
    skipText.setPosition(W / 2.f, H - 60.f);
    
    window.draw(introBackground);
    window.draw(slideText);
    window.draw(skipText);
}