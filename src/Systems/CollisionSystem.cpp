#include "Systems/CollisionSystem.hpp"
#include "Entities/Player.hpp"
#include "Entities/Enemy.hpp"
#include "Entities/Projectile.hpp"
#include "Weapons/WeaponPickup.hpp"
#include "Entities/Explosion.hpp"
#include "Utils/Config.hpp"
#include "Utils/Math.hpp"

void CollisionSystem::checkCollisions(
    Player* player,
    std::vector<Enemy*>& enemies,
    std::vector<Projectile*>& projectiles,
    std::vector<WeaponPickup*>& pickups,
    std::vector<Explosion*>& explosions
) {
    checkPlayerProjectiles(player, projectiles);
    checkEnemyProjectiles(enemies, projectiles, explosions);
    checkPlayerPickups(player, pickups);
}

void CollisionSystem::checkPlayerProjectiles(Player* player, std::vector<Projectile*>& projectiles) {
    for (auto* proj : projectiles) {
        if (!proj->active) continue;
        if (proj->fromPlayer) continue;
        
        if (player->collider.checkCollision(proj->collider, player->transform.x, player->transform.y, 
                                            proj->transform.x, proj->transform.y)) {
            player->health.damage(proj->damage);
            proj->active = false;
        }
    }
}

void CollisionSystem::checkEnemyProjectiles(std::vector<Enemy*>& enemies, std::vector<Projectile*>& projectiles, std::vector<Explosion*>& explosions) {
    for (auto* proj : projectiles) {
        if (!proj->active) continue;
        
        for (auto* enemy : enemies) {
            if (!enemy->health.isAlive()) continue;
            
            if (enemy->collider.checkCollision(proj->collider, enemy->transform.x, enemy->transform.y,
                                              proj->transform.x, proj->transform.y)) {
                
                enemy->health.damage(proj->damage);
                proj->active = false;
                
                if (proj->isAoE) {
                    explosions.push_back(new Explosion(proj->transform.x, proj->transform.y, proj->aoeRadius));
                    
                    for (auto* otherEnemy : enemies) {
                        if (!otherEnemy->health.isAlive()) continue;
                        
                        float dist = Math::distance(proj->transform.x, proj->transform.y,
                                                   otherEnemy->transform.x, otherEnemy->transform.y);
                        
                        if (dist < proj->aoeRadius) {
                            float aoeDamage = proj->damage * 0.5f * (1.0f - dist / proj->aoeRadius);
                            otherEnemy->health.damage(aoeDamage);
                        }
                    }
                }
                
                break;
            }
        }
    }
}

void CollisionSystem::checkPlayerPickups(Player* player, std::vector<WeaponPickup*>& pickups) {
    for (auto* pickup : pickups) {
        if (pickup->pickedUp) continue;
        
        float dist = Math::distance(player->transform.x, player->transform.y,
                                   pickup->transform.x, pickup->transform.y);
        
        if (dist < Config::PICKUP_RANGE) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                player->pickupWeapon(pickup->weaponType);
                pickup->pickedUp = true;
            }
        }
    }
}