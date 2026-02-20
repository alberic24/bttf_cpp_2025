#pragma once
#include <vector>

class Player;
class Enemy;
class Projectile;
class WeaponPickup;
class Explosion;

class CollisionSystem {
public:
    static void checkCollisions(
        Player* player,
        std::vector<Enemy*>& enemies,
        std::vector<Projectile*>& projectiles,
        std::vector<WeaponPickup*>& pickups,
        std::vector<Explosion*>& explosions
    );
    
private:
    static void checkPlayerProjectiles(Player* player, std::vector<Projectile*>& projectiles);
    static void checkEnemyProjectiles(std::vector<Enemy*>& enemies, std::vector<Projectile*>& projectiles, std::vector<Explosion*>& explosions);
    static void checkPlayerPickups(Player* player, std::vector<WeaponPickup*>& pickups);
};