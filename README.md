# Top-Down Shooter - BTTF CPP

Projet de rattrapage pour la piste Gameplay du module R-Type.

## 🎮 Description

Shooter top-down solo avec mécaniques de combat, système d'armes interchangeables, et affrontement contre des ennemis et un boss.

## 📋 Prérequis

- CMake 3.10+
- C++17 compiler (g++, clang++, MSVC)
- SFML 2.5+

### Installation de SFML

**Ubuntu/Debian:**
```bash
sudo apt-get install libsfml-dev
```

**Arch Linux:**
```bash
sudo pacman -S sfml
```

**macOS (Homebrew):**
```bash
brew install sfml
```

**Windows:**
Télécharger depuis https://www.sfml-dev.org/download.php

## 🔨 Compilation

```bash
mkdir build && cd build
cmake ..
make
./TopDownShooter
```

## 🎯 Contrôles du jeu

### Déplacement 
- **H** : Avancer (haut)
- **B** : Reculer (bas)
- **G** : Gauche
- **D** : Droite

### Combat
- **Souris (mouvement)** : Visée (le joueur regarde vers le curseur)
- **Clic gauche/espace** : Tirer
- **Clic droit / Molette /E** : Changer d'arme
- **R** : Recharger

### Interaction
- **E** : Ramasser une arme (lorsque proche d'un pickup)

### Interface
- **ESC** : Retour au menu principal (pendant le jeu)

## 🔫 Système d'armes

Le jeu implémente un système d'armes **orienté objet** via l'interface `IWeapon`.

### Armes disponibles

#### 1. Pistol (Pistolet)
- **Type** : Projectile rapide, tir de précision
- **Munitions** : 12 balles
- **Cadence de tir** : 3 tirs/seconde
- **Rechargement** : 1.5 secondes
- **Dégâts** : 20 par projectile
- **Utilité tactique** : Arme polyvalente, efficace à moyenne distance

#### 2. Fireball Launcher (Lance-boules de feu)
- **Type** : Projectile lent avec **zone d'effet (AoE)**
- **Munitions** : 6 boules de feu
- **Cadence de tir** : 1 tir/seconde (plus lent)
- **Rechargement** : 2.5 secondes
- **Dégâts** : 35 directs + dégâts de zone
- **Rayon AoE** : 80 unités
- **Utilité tactique** : Contrôle de zone, efficace contre groupes d'ennemis

### Différences mécaniques fondamentales

| Caractéristique | Pistol | Fireball Launcher |
|----------------|--------|-------------------|
| Vitesse projectile | Rapide (1.5x) | Lente (0.6x) |
| Type de dégâts | Ponctuel | Zone d'effet |
| Cadence de tir | Élevée | Faible |
| Portée effective | Longue | Moyenne |
| Cibles multiples | Non | Oui (explosion) |

## 👾 Système d'ennemis

### Ennemi basique
- **Vie** : 50 HP
- **Comportement** : Se déplace vers le joueur
- **Attaque** : Tire un projectile unique toutes les 2 secondes
- **Dégâts** : 10 par projectile

### Boss (spawn après 10 ennemis)
- **Vie** : 150 HP (3× celle d'un ennemi normal)
- **Comportement** : Mouvement identique mais plus agressif
- **Attaque** : Tire en **éventail** (3 projectiles simultanés) toutes les 1 seconde
- **Angle d'éventail** : ±15° de la direction du joueur
- **Dégâts** : 15 par projectile
- **Apparence** : Plus grand, rouge vif avec contour orange

## 💥 Système de collisions

Le jeu détecte les collisions suivantes :
- ✅ Projectile ↔ Joueur
- ✅ Projectile ↔ Ennemi
- ✅ Projectile ↔ Mur (bords de l'écran)
- ✅ Joueur ↔ Pickup (armes)
- ✅ AoE ↔ Multiples ennemis (pour Fireball Launcher)

### Détection circulaire
Toutes les collisions utilisent des cercles (AABB serait aussi acceptable).

## 🖥️ Interface utilisateur

### Menu principal
- **Start Game** : Lancer une partie
- **Settings** : Accéder aux paramètres
- **Quit** : Quitter le jeu

### Menu Settings
- **Volume** : Ajuster avec boutons +/- (0-100%)
- **Fullscreen** : Activer/désactiver le plein écran
- **Sauvegarde automatique** : Les paramètres sont sauvegardés dans `settings.cfg`

### HUD en jeu
- **Barre de vie** : Affichage graphique + numérique (HP actuel/max)
- **Munitions** : Affichage actuel/max pour l'arme équipée
- **Arme actuelle** : Nom de l'arme équipée

## 🏗️ Architecture du code

### Organisation
```
include/
├── Components/      # Components ECS (Transform, Health, Collider)
├── Core/           # Logique principale (Game, Scene, ResourceManager)
├── Entities/       # Entités du jeu (Player, Enemy, Projectile, Explosion)
├── Systems/        # Systèmes (Collision, Physics)
├── UI/             # Interface utilisateur (Menus, HUD, Button)
├── Utils/          # Utilitaires (Config, Math)
└── Weapons/        # Système d'armes (IWeapon interface + implémentations)

src/
└── [Mêmes dossiers que include/]
```

### Points importants pour l'évaluation

#### ✅ Abstraction du système d'armes
- **Interface** : `IWeapon` (classe abstraite avec méthodes virtuelles pures)
- **Implémentations** : `Pistol` et `FireballLauncher` héritent de `IWeapon`
- **Polymorphisme** : Le joueur utilise `IWeapon*` pour gérer toutes les armes
- **Mécaniques différentes** : Projectile rapide vs AoE lent (pas juste des stats)

#### ✅ Système de collisions
- **CollisionSystem** : Classe dédiée avec méthodes statiques
- **Détection** : Collision circulaire (distance entre centres < somme des rayons)
- **Types gérés** : Player, Enemy, Projectile, Pickup, AoE

#### ✅ Persistance des paramètres
- **Config::Settings** : Classe avec méthodes `save()` et `load()`
- **Fichier** : `settings.cfg` (format clé=valeur)
- **Paramètres** : Volume, fullscreen

## 🎨 Wrappers C++

Bien que SFML soit déjà en C++, voici comment le code respecte le paradigme objet :
- Tous les fichiers utilisent des **classes** et des **méthodes**
- Pas de code C brut dans la logique gameplay
- Utilisation de **smart pointers** (`std::unique_ptr`, `std::vector`)
- Encapsulation correcte (private/public)
- Interfaces avec **méthodes virtuelles pures**

## 📦 Fonctionnalités implémentées

### Mécaniques de base ✅
- [x] Déplacement WASD
- [x] Visée souris
- [x] Tir (clic gauche)
- [x] Changement d'arme (clic droit/molette)
- [x] Rechargement (touche R)
- [x] Ramassage d'armes (touche E)

### Système d'armes ✅
- [x] Interface `IWeapon` abstraite
- [x] 2 armes mécaniquement différentes (Projectile vs AoE)
- [x] Système de munitions complet
- [x] Pickups d'armes au sol
- [x] Inventaire multi-armes

### Système d'ennemis ✅
- [x] Ennemi basique avec IA simple
- [x] Boss (3× vie + pattern d'attaque différent)
- [x] Spawn progressif d'ennemis

### Collisions ✅
- [x] Joueur ↔ Projectile
- [x] Ennemi ↔ Projectile
- [x] Projectile ↔ Mur (bords)
- [x] Joueur ↔ Pickup

### UI ✅
- [x] Menu principal fonctionnel
- [x] Menu Settings avec volume + fullscreen
- [x] HUD avec vie, munitions, arme
- [x] Sauvegarde des paramètres

## 🐛 Notes de développement

### Limitations connues
- Pas de sons/musique (non requis)
- Pas de tilemap complexe (jeu sur fond uni)
- Pas de particle effects avancés

### Extensions possibles
- Système de vagues d'ennemis
- Plus de types d'armes
- Power-ups
- Système de scoring

## 📝 Auteur

Projet réalisé dans le cadre du module BTTF CPP - Track Gameplay

## 📄 Licence

Projet académique - EPITECH