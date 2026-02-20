#include "Core/GameScene.hpp"
#include "Systems/CollisionSystem.hpp"
#include "Utils/Config.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "Utils/Math.hpp"
#include <cstdlib>
#include <ctime>

GameScene::GameScene(sf::Font& font, sf::RenderWindow& win) 
    : font(font), window(&win), enemySpawnTimer(0.0f), enemySpawnInterval(3.0f),
      pickupSpawnTimer(0.0f), enemiesSpawned(0), bossSpawned(false),
      lastSpawnedWeapon(WeaponType::FireballLauncher) {
    
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    
    player = std::make_unique<Player>(Config::WINDOW_WIDTH / 2.0f, Config::WINDOW_HEIGHT / 2.0f);
    hud = std::make_unique<HUD>(font);
    
    for (int i = 0; i < 3; i++) {
        spawnEnemy();
    }
}

GameScene::~GameScene() {
    cleanup();
}

bool GameScene::isPlayerAlive() const {
    return player->health.isAlive();
}

void GameScene::handleInput(sf::RenderWindow& window) {
    player->handleInput(window, 1.0f / 60.0f);
    
    static bool rightClickPressed = false;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        if (!rightClickPressed) {
            player->switchWeapon();
        }
        rightClickPressed = true;
    } else {
        rightClickPressed = false;
    }
}

void GameScene::update(float dt) {
    player->update(dt, projectiles, *window);
    
    for (auto* proj : projectiles) {
        if (proj->active) {
            proj->update(dt);
            if (proj->transform.x < 0 || proj->transform.x > Config::WINDOW_WIDTH ||
                proj->transform.y < 0 || proj->transform.y > Config::WINDOW_HEIGHT) {
                proj->active = false;
            }
        }
    }
    
    for (auto* enemy : enemies) {
        if (enemy->health.isAlive()) {
            enemy->update(dt, player->transform.x, player->transform.y, projectiles);
        }
    }
    
    for (auto* explosion : explosions) {
        explosion->update(dt);
    }
    
    CollisionSystem::checkCollisions(player.get(), enemies, projectiles, pickups, explosions);
    
    enemySpawnTimer += dt;
    if (enemySpawnTimer >= enemySpawnInterval) {
        spawnEnemy();
        enemySpawnTimer = 0.0f;
        enemiesSpawned++;
        
        if (enemiesSpawned >= 10 && !bossSpawned) {
            spawnEnemy(true);
            bossSpawned = true;
        }
    }
    
    if (pickups.empty()) {
        pickupSpawnTimer += dt;
        if (pickupSpawnTimer >= 90.0f) {
            spawnWeaponPickup();
            pickupSpawnTimer = 0.0f;
        }
    }
    
    cleanup();
}

void GameScene::draw(sf::RenderWindow& window) {
    player->draw(window);
    
    for (auto* enemy : enemies) {
        if (enemy->health.isAlive()) {
            enemy->draw(window);
        }
    }
    
    for (auto* proj : projectiles) {
        proj->draw(window);
    }
    
    for (auto* pickup : pickups) {
        pickup->draw(window);
    }
    
    for (auto* explosion : explosions) {
        explosion->draw(window);
    }
    
    hud->draw(window, player.get());
}

void GameScene::spawnEnemy(bool boss) {
    float x = static_cast<float>(std::rand() % Config::WINDOW_WIDTH);
    float y = static_cast<float>(std::rand() % Config::WINDOW_HEIGHT);
    
    while (Math::distance(x, y, player->transform.x, player->transform.y) < 200.0f) {
        x = static_cast<float>(std::rand() % Config::WINDOW_WIDTH);
        y = static_cast<float>(std::rand() % Config::WINDOW_HEIGHT);
    }
    
    enemies.push_back(new Enemy(x, y, boss));
}

void GameScene::spawnWeaponPickup() {
    // Ne pas spawner la même arme deux fois de suite
    WeaponType type;
    if (lastSpawnedWeapon == WeaponType::Pistol) {
        type = WeaponType::FireballLauncher;
    } else {
        type = WeaponType::Pistol;
    }
    lastSpawnedWeapon = type;
    
    float x = 200.0f + static_cast<float>(std::rand() % (Config::WINDOW_WIDTH - 400));
    float y = 200.0f + static_cast<float>(std::rand() % (Config::WINDOW_HEIGHT - 400));
    
    pickups.push_back(new WeaponPickup(x, y, type));
}

void GameScene::cleanup() {
    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
                      [](Projectile* p) {
                          if (!p->active) { delete p; return true; }
                          return false;
                      }),
        projectiles.end()
    );
    
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
                      [](Enemy* e) {
                          if (!e->health.isAlive()) { delete e; return true; }
                          return false;
                      }),
        enemies.end()
    );
    
    pickups.erase(
        std::remove_if(pickups.begin(), pickups.end(),
                      [](WeaponPickup* p) {
                          if (p->pickedUp) { delete p; return true; }
                          return false;
                      }),
        pickups.end()
    );
    
    explosions.erase(
        std::remove_if(explosions.begin(), explosions.end(),
                      [](Explosion* e) {
                          if (e->isFinished()) { delete e; return true; }
                          return false;
                      }),
        explosions.end()
    );
}