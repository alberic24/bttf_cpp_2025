#include "Weapons/FireballLauncher.hpp"
#include "Entities/Projectile.hpp"
#include "Utils/Math.hpp"
#include "Utils/Config.hpp"
#include "Core/ResourceManager.hpp"

FireballLauncher::FireballLauncher() {
    currentAmmo = FIREBALL_MAX_AMMO;
    maxAmmo = FIREBALL_MAX_AMMO;
    fireRate = FIREBALL_FIRE_RATE;
    reloadTime = FIREBALL_RELOAD_TIME;
    timeSinceLastShot = 0.0f;
    reloadTimer = 0.0f;
    isReloading = false;
}

void FireballLauncher::fire(float x, float y, float targetX, float targetY, std::vector<Projectile*>& projectiles) {
    if (!canFire()) return;
    
    currentAmmo--;
    timeSinceLastShot = 0.0f;
    
    ResourceManager::getInstance().getFireballSound().play();
    
    float angle = Math::angle(x, y, targetX, targetY);
    auto* proj = new Projectile(x, y, angle, Config::PROJECTILE_SPEED * 0.6f, PROJECTILE_DAMAGE, true);
    proj->fromPlayer = true;
    projectiles.push_back(proj);
}

void FireballLauncher::reload() {
    if (!isReloading && currentAmmo < maxAmmo) {
        isReloading = true;
        reloadTimer = 0.0f;
    }
}

void FireballLauncher::update(float dt) {
    timeSinceLastShot += dt;
    
    if (isReloading) {
        reloadTimer += dt;
        if (reloadTimer >= reloadTime) {
            currentAmmo = maxAmmo;
            isReloading = false;
            reloadTimer = 0.0f;
        }
    }
}

bool FireballLauncher::canFire() const {
    return !isReloading && currentAmmo > 0 && timeSinceLastShot >= (1.0f / fireRate);
}

int FireballLauncher::getCurrentAmmo() const { return currentAmmo; }
int FireballLauncher::getMaxAmmo() const { return maxAmmo; }
std::string FireballLauncher::getName() const { return "Fireball Launcher"; }
WeaponType FireballLauncher::getType() const { return WeaponType::FireballLauncher; }