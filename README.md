# Deadly Bouncy Balls (C++ / SFML Game)

A fast-paced arcade-style mini game where the player dodges and shoots bouncing balls that move, collide, and split over time. 

---

## Design Overview
This project was created to practice essential game development concepts using modern C++ and SFML. 
The goal was to build a minimal yet complete game system featuring game mechanics, game states management, dynamic entity interactions, physics-based movement, real-time collision handling, and UI navigation
   - Game Mechanics: Implements a continuous game loop architecture that updates movement, handles physics, detects and          resolves collisions, and renders each frame
   - Physics Simulation: Balls move with velocity, bounce off walls, collide with each other, and split into smaller,            faster balls over time
   - Systems: Modular gameplay systems for combat, shooting, aiming, collision detection, and asset management, designed to      separate responsibilities and support future feature expansion
   - Entity Handling: Modular gameplay structure with dedicated classes for Player, Ball, and BallManager
   - Screen Management: Multiple game screens such as Start Screen, Gameplay Screen, and Game Over Screen for game states        manager
   - Overlays: Interactive overlays for instructions and pause menu using clickable text buttons
   - Visual Effects: Balls blink as a visual warning before splitting, enhancing player feedback and game feel
   - Framework Integration: Demonstrates use of SFML’s real-time rendering, drawable shapes, vector math, and timing systems

---

## Design Goals
- Provide an engaging and reactive gameplay experience based on dodging mechanics
- Implement a scalable and modular architecture separating UI and core gameplay
- Explore real-time game loops, physics handling, delta-time movement, entity-based interactions, game states management,     and UI navigaton
- Build familiarity with SFML as a game development framework
- Allow room for future enhancements
- Keep the codebase readable, modular, and refactor-friendly

---

## Download
Get the latest Windows installer: [Releases](https://github.com/PVAT1187/DeadlyBouncyBalls_Game/releases)

---

## Demo
![DeadlyBouncyBalls_v1 1_Demo](https://github.com/user-attachments/assets/30a01c42-b2a6-419b-aec5-7dd63aae3693)

---

## Features
- Core Gameplay
  - Real-time physics and bouncing behavior
  - Circle-to-rectangle and circle-to-circle collisions
  - Ball splitting with blinking warning effect
  - Random color, speed, position and direction for dynamic difficulty
  - Shooting mechanics with bullet lifetime handling
  - Animated aiming crosshair for accurate targeting
- Game States & UI
  - Start Screen with game title and clickable buttons
  - Gameplay Screen with real-time rendering and physics
  - Game Over Screen with restart and main menu navigation
  - Instructions Overlay available from the menu
  - Pause Menu Overlay with resume and main menu options
  - Fully interactive SFML Text buttons using mouse detection
- Architecture
  - Frame-rate independent movement using deltaTime
  - System-driven design (Combat, Shooting, Collision, Aiming)
  - Modular separation of core, entities, math, physics, screens, overlays and UI utilities

---

## Tech Stack
- Programming Language: C++
- Frameworks: SFML
- Systems/Concepts:
    - Game loop architecture
    - Game state management (screens and overlays)
    - Pure Math Utilities
    - Physics & collision detection
    - Combat and projectile systems
    - Entity Management
    - UI rendering and text interaction
    - Real-time updates
- IDE/Tools: Visual Studio, Git/GitHub

---

## Future Improvement
- New Gameplay Features
    - Power-ups and collectibles
    - Score tracking
- Architecture
    - Refactor toward more event-driven systems
    - Introduce component-based abilities
- Audio and Visual Effects
    - Expand experience with sound effects and background music
    - Polish tutorial screen

---

## Authors
**Vu Anh Thu Phan** - [GitHub](https://github.com/PVAT1187)
