# GASCrash ⚡

A combat game built in Unreal Engine 5 as a deep dive into the **Gameplay Ability System (GAS)**. The project covers all core GAS components from scratch — abilities, attributes, AI, Gameplay Effects, Gameplay Cues and more.

> 🚧 Work in progress — actively developed alongside a structured GAS course.

---

## 🎮 About

GASCrash uses free Paragon assets from Epic Games and implements a fully functional action combat loop entirely through GAS. Every mechanic — from player input to enemy AI — is built on top of the Ability System Component.

The goal is a thorough, hands-on understanding of GAS architecture in a real game context.

---

## ✅ Implemented

| System | Details |
|--------|---------|
| **Project setup** | Blank project with Paragon assets, character classes, Character Blueprint |
| **Enhanced Input** | Player Controller with Input Mapping Contexts for movement and abilities |
| **Ability System Component** | Custom ASC with Gameplay Abilities, Base Ability Class, Play Montage and Wait task |
| **Gameplay Tags** | Native tags defined in C++, abilities activated by tag |
| **Ability architecture** | Primary, secondary and tertiary ability slots |
| **Gameplay Events** | Enemies, Directional HitReacts, Auto Activated Abilities |
| **Attributes & Attribute Sets** | Attribute Sets, Widgets, Gameplay Effects, Curve Tables, Leveling Up Abilities |

---

## 🔜 In Progress

- Character Death & Respawning
- Enemy Combat AI
- Player Damage & Hit Reacts
- Ability Cost & Cooldown

---

## 🛠️ Tech Stack

- **Engine:** Unreal Engine 5
- **Language:** C++ and Blueprint
- **Key system:** Gameplay Ability System (GAS)
- **Assets:** Paragon (Epic Games — free)

---

## 🚀 Getting Started

### Prerequisites
- Unreal Engine 5.x
- Visual Studio 2022 (with C++ game development workload)

### Setup
```bash
git clone https://github.com/jkaczor6/GASCrash.git
```
1. Right-click `GASCrash.uproject` → **Generate Visual Studio project files**
2. Open `GASCrash.sln` in Visual Studio and build
3. Open `GASCrash.uproject` in Unreal Engine 5

---

## 👤 Author

**Jakub Kaczor** — [Portfolio](https://jkaczor6.github.io/portfolio/) · [GitHub](https://github.com/jkaczor6)
