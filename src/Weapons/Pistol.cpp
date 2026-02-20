#include "Weapons/Pistol.hpp"
#include "Entities/Projectile.hpp"
#include "Utils/Math.hpp"
#include "Utils/Config.hpp"

Pistol::Pistol() {
    currentAmmo = PISTOL_MAX_AMMO;
    maxAmmo = PISTOL_MAX_AMMO;
    fireRate = PISTOL_FIRE_RATE;
    reloadTime = PISTOL_RELOAD_TIME;
    timeSinceLastShot = 0.0f;
    reloadTimer = 0.0f;
    isReloading = false;
}

void Pistol::fire(float x, float y, float targetX, float targetY, std::vector<Projectile*>& projectiles) {
    if (!canFire()) return;
    
    currentAmmo--;
    timeSinceLastShot = 0.0f;
    
    float angle = Math::angle(x, y, targetX, targetY);
    auto* proj = new Projectile(x, y, angle, Config::PROJECTILE_SPEED * 1.5f, PROJECTILE_DAMAGE, false);
    proj->fromPlayer = true;
    projectiles.push_back(proj);
}

void Pistol::reload() {
    if (!isReloading && currentAmmo < maxAmmo) {
        isReloading = true;
        reloadTimer = 0.0f;
    }
}

void Pistol::update(float dt) {
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

bool Pistol::canFire() const {
    return !isReloading && currentAmmo > 0 && timeSinceLastShot >= (1.0f / fireRate);
}

int Pistol::getCurrentAmmo() const { return currentAmmo; }
int Pistol::getMaxAmmo() const { return maxAmmo; }
std::string Pistol::getName() const { return "Pistol"; }
WeaponType Pistol::getType() const { return WeaponType::Pistol; }