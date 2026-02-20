#include "UI/MainMenu.hpp"
#include "Core/ResourceManager.hpp" 
#include "Utils/Config.hpp"

MainMenu::MainMenu(sf::Font& font) : font(font), title("TOP-DOWN SHOOTER", font, 60), currentAction(MenuAction::None) {
    title.setFillColor(sf::Color::White);
    
    backgroundTexture = &ResourceManager::getInstance().getTexture("menu_background");
    backgroundSprite.setTexture(*backgroundTexture);
    
    float buttonWidth = 300.0f;
    float buttonHeight = 60.0f;
    float startY = 300.0f;
    float spacing = 80.0f;
    float centerX = Config::WINDOW_WIDTH / 2.0f - buttonWidth / 2.0f;
    
    auto startBtn = std::make_unique<Button>(centerX, startY, buttonWidth, buttonHeight, "Start Game", font);
    startBtn->setCallback([this]() { currentAction = MenuAction::StartGame; });
    buttons.push_back(std::move(startBtn));
    
    auto settingsBtn = std::make_unique<Button>(centerX, startY + spacing, buttonWidth, buttonHeight, "Settings", font);
    settingsBtn->setCallback([this]() { currentAction = MenuAction::Settings; });
    buttons.push_back(std::move(settingsBtn));
    
    auto quitBtn = std::make_unique<Button>(centerX, startY + spacing * 2, buttonWidth, buttonHeight, "Quit", font);
    quitBtn->setCallback([this]() { currentAction = MenuAction::Quit; });
    buttons.push_back(std::move(quitBtn));
}

MenuAction MainMenu::update(sf::RenderWindow& window) {
    MenuAction action = currentAction;
    currentAction = MenuAction::None;
    
    sf::Vector2u windowSize = window.getSize();
    float centerX = windowSize.x / 2.0f;
    
    sf::Vector2u texSize = backgroundTexture->getSize();
    float scaleX = static_cast<float>(windowSize.x) / texSize.x;
    float scaleY = static_cast<float>(windowSize.y) / texSize.y;
    backgroundSprite.setScale(scaleX, scaleY);
    
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setPosition(centerX - titleBounds.width / 2.0f, 100.0f);
    
    float buttonWidth = 300.0f;
    float startY = 300.0f;
    float spacing = 80.0f;
    
    buttons[0]->setPosition(centerX - buttonWidth / 2.0f, startY);
    buttons[1]->setPosition(centerX - buttonWidth / 2.0f, startY + spacing);
    buttons[2]->setPosition(centerX - buttonWidth / 2.0f, startY + spacing * 2);
    
    for (auto& button : buttons) {
        button->isClicked(window);
    }
    
    return action;
}

void MainMenu::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(title);
    for (auto& button : buttons) {
        button->draw(window);
    }
}