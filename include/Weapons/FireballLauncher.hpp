#pragma once
#include "IWeapon.hpp"

class FireballLauncher : public IWeapon {
public:
    FireballLauncher();
    
    void fire(float x, float y, float targetX, float targetY, std::vector<Projectile*>& projectiles) override;
    void reload() override;
    void update(float dt) override;
    
    bool canFire() const override;
    int getCurrentAmmo() const override;
    int getMaxAmmo() const override;
    std::string getName() const override;
    WeaponType getType() const override;

private:
    static constexpr int FIREBALL_MAX_AMMO = 900;
    static constexpr float FIREBALL_FIRE_RATE = 1.0f;
    static constexpr float FIREBALL_RELOAD_TIME = 2.5f;
    static constexpr float PROJECTILE_DAMAGE = 35.0f;
};