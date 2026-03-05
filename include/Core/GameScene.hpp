#pragma once
#include "Scene.hpp"
#include "Entities/Player.hpp"
#include "Entities/Enemy.hpp"
#include "Entities/Projectile.hpp"
#include "Entities/Explosion.hpp"
#include "Weapons/WeaponPickup.hpp"
#include "UI/HUD.hpp"
#include <vector>
#include <memory>

class GameScene : public Scene {
public:
    GameScene(sf::Font& font, sf::RenderWindow& win);
    ~GameScene();
    
    void handleInput(sf::RenderWindow& window) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    bool isPlayerAlive() const;
    bool isBossDefeated() const { return bossDefeated; }  // <-- AJOUTÉ
    int getKillCount() const { return enemyKillCount; }    // <-- AJOUTÉ
    int score = 0;
    
private:
    sf::Font& font;
    std::unique_ptr<Player> player;
    std::unique_ptr<HUD> hud;
    sf::RenderWindow* window = nullptr;
    
    std::vector<Enemy*> enemies;
    std::vector<Projectile*> projectiles;
    std::vector<WeaponPickup*> pickups;
    std::vector<Explosion*> explosions;
    
    float enemySpawnTimer;
    float enemySpawnInterval;
    float pickupSpawnTimer;
    int enemiesSpawned;
    int enemyKillCount;          // <-- AJOUTÉ : Compteur de kills
    bool bossSpawned;
    bool bossDefeated;           // <-- AJOUTÉ : Boss vaincu ?
    WeaponType lastSpawnedWeapon;
    
    void spawnEnemy(bool boss = false);
    void spawnWeaponPickup();
    void cleanup();
};