#include "UI/SettingsMenu.hpp"
#include "Core/ResourceManager.hpp"
#include "Utils/Config.hpp"
#include <algorithm>

SettingsMenu::SettingsMenu(sf::Font& font, sf::RenderWindow* window) 
    : font(font), gameWindow(window), title("SETTINGS", font, 50), 
      volumeText("", font, 24), fullscreenText("", font, 24) {
    
    title.setFillColor(sf::Color::White);
    volumeText.setFillColor(sf::Color::White);
    fullscreenText.setFillColor(sf::Color::White);
    
    volumeDownButton = std::make_unique<Button>(550.0f, 240.0f, 60.0f, 50.0f, "-", font);
    volumeDownButton->setCallback([]() {
        Config::settings.volume = std::max(0.0f, Config::settings.volume - 0.1f);
        Config::settings.save();
        ResourceManager::getInstance().getMenuMusic().setVolume(Config::settings.volume * 100);
    });
    
    volumeUpButton = std::make_unique<Button>(700.0f, 240.0f, 60.0f, 50.0f, "+", font);
    volumeUpButton->setCallback([]() {
        Config::settings.volume = std::min(1.0f, Config::settings.volume + 0.1f);
        Config::settings.save();
        ResourceManager::getInstance().getMenuMusic().setVolume(Config::settings.volume * 100);
    });
    
    fullscreenToggle = std::make_unique<Button>(550.0f, 340.0f, 200.0f, 50.0f, "Toggle", font);
    fullscreenToggle->setCallback([this]() {
        Config::settings.fullscreen = !Config::settings.fullscreen;
        Config::settings.save();
        applyFullscreen();
    });
    
    backButton = std::make_unique<Button>(490.0f, 500.0f, 300.0f, 60.0f, "Back", font);
    
    updateTexts();
}

void SettingsMenu::applyFullscreen() {
    if (!gameWindow) return;
    
    gameWindow->close();
    
    if (Config::settings.fullscreen) {
        gameWindow->create(sf::VideoMode::getDesktopMode(), Config::WINDOW_TITLE, sf::Style::Fullscreen);
    } else {
        gameWindow->create(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), Config::WINDOW_TITLE, sf::Style::Default);
    }
    
    gameWindow->setFramerateLimit(60);
}

void SettingsMenu::updateTexts() {
    int volumePercent = static_cast<int>(Config::settings.volume * 100);
    volumeText.setString("Volume: " + std::to_string(volumePercent) + "%");
    fullscreenText.setString("Fullscreen: " + std::string(Config::settings.fullscreen ? "ON" : "OFF"));
}

bool SettingsMenu::update(sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    float centerX = windowSize.x / 2.0f;
    
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setPosition(centerX - titleBounds.width / 2.0f, 80.0f);
    
    volumeText.setPosition(200.0f, 250.0f);
    fullscreenText.setPosition(200.0f, 350.0f);
    
    volumeDownButton->setPosition(centerX - 100.0f, 240.0f);
    volumeUpButton->setPosition(centerX + 50.0f, 240.0f);
    fullscreenToggle->setPosition(centerX - 100.0f, 340.0f);
    backButton->setPosition(centerX - 150.0f, 500.0f);
    
    volumeDownButton->isClicked(window);
    volumeUpButton->isClicked(window);
    fullscreenToggle->isClicked(window);
    
    updateTexts();
    
    return backButton->isClicked(window);
}

void SettingsMenu::draw(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(volumeText);
    window.draw(fullscreenText);
    
    volumeDownButton->draw(window);
    volumeUpButton->draw(window);
    fullscreenToggle->draw(window);
    backButton->draw(window);
}