#include "UI/HUD.hpp"
#include "Entities/Player.hpp"
#include "Weapons/IWeapon.hpp"

HUD::HUD(sf::Font& font) : font(font), healthText("", font, 20), ammoText("", font, 20), weaponText("", font, 20) {
    healthText.setFillColor(sf::Color::White);
    ammoText.setFillColor(sf::Color::White);
    weaponText.setFillColor(sf::Color::White);
    
    healthBarBg.setSize(sf::Vector2f(200.0f, 20.0f));
    healthBarBg.setFillColor(sf::Color(50, 50, 50));
    healthBarBg.setOutlineThickness(2.0f);
    healthBarBg.setOutlineColor(sf::Color::White);
    
    healthBar.setSize(sf::Vector2f(200.0f, 20.0f));
    healthBar.setFillColor(sf::Color::Green);
}

void HUD::draw(sf::RenderWindow& window, Player* player) {
    
    healthBarBg.setPosition(20.0f, 20.0f);
    healthBar.setPosition(20.0f, 20.0f);
    healthBar.setSize(sf::Vector2f(200.0f * player->health.getPercentage(), 20.0f));
    
    window.draw(healthBarBg);
    window.draw(healthBar);
    
    healthText.setString("HP: " + std::to_string(static_cast<int>(player->health.current)) + "/" + 
                        std::to_string(static_cast<int>(player->health.maximum)));
    healthText.setPosition(230.0f, 18.0f);
    window.draw(healthText);
    
    IWeapon* weapon = player->getCurrentWeapon();
    ammoText.setString("Ammo: " + std::to_string(weapon->getCurrentAmmo()) + "/" + 
                       std::to_string(weapon->getMaxAmmo()));
    ammoText.setPosition(20.0f, 50.0f);
    window.draw(ammoText);
    
    weaponText.setString("Weapon: " + weapon->getName());
    weaponText.setPosition(20.0f, 80.0f);
    window.draw(weaponText);
}