#pragma once
#include <string>
#include <vector>

class Projectile;

enum class WeaponType {
    Pistol,
    FireballLauncher
};

class IWeapon {
public:
    virtual ~IWeapon() = default;
    
    virtual void fire(float x, float y, float targetX, float targetY, std::vector<Projectile*>& projectiles) = 0;
    virtual void reload() = 0;
    virtual void update(float dt) = 0;
    
    virtual bool canFire() const = 0;
    virtual int getCurrentAmmo() const = 0;
    virtual int getMaxAmmo() const = 0;
    virtual std::string getName() const = 0;
    virtual WeaponType getType() const = 0;
    
protected:
    int currentAmmo;
    int maxAmmo;
    float fireRate;
    float reloadTime;
    float timeSinceLastShot;
    float reloadTimer;
    bool isReloading;
};