#pragma once
#include "IWeapon.hpp"

class Pistol : public IWeapon {
public:
    Pistol();
    
    void fire(float x, float y, float targetX, float targetY, std::vector<Projectile*>& projectiles) override;
    void reload() override;
    void update(float dt) override;
    
    bool canFire() const override;
    int getCurrentAmmo() const override;
    int getMaxAmmo() const override;
    std::string getName() const override;
    WeaponType getType() const override;

private:
    static constexpr int PISTOL_MAX_AMMO = 500;
    static constexpr float PISTOL_FIRE_RATE = 3.0f;
    static constexpr float PISTOL_RELOAD_TIME = 1.5f;
    static constexpr float PROJECTILE_DAMAGE = 20.0f;
};