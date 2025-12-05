# Deadly Bouncy Balls (C++ / SFML Game)

A fast-paced mini game where the player controls a rectangle and must dodge bouncing balls that move, collide, and split over time. 

---

## Design Overview
This project was created to practice essential game development concepts using modern C++ and SFML. 
The goal was to build a minimal yet complete game system featuring game mechanics, game states management, dynamic entity interactions, physics-based movement, real-time collision handling, and UI navigation
   - Game Mechanics: Implements a continuous game loop architecture that updates movement, handles physics, detects and          resolves collisions, and renders each frame
   - Physics Simulation: Balls move with velocity, bounce off walls, collide with each other, and split into smaller,            faster balls over time
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
- Allow room for future enhancements such as UI, scoring, sound effects, or additional mechanics

---

## Setup Instructions
Prerequisites
- C++17 or newer
- SFML 2.5 or newer
- Visual Studio / any C++ IDE
- CMake (optional)

Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/PVAT1187/DeadlyBouncyBall.git
2. Install and configure SFML:
   - Add include and lib paths
   - Link:
       - sfml-graphics
       - sfml-window
       - sfml-system
   - Copy SFML .dll files next to your executable if on Windows
3. Build and run the project

---

## Usage
![DeadlyBouncyBalls_Demo](https://github.com/user-attachments/assets/6768ab90-7b0b-406b-bb23-dc173ce17414)

---

## Features
- Core Gameplay
  - Real-time physics and bouncing
  - Circle-to-rectangle and ball-to-ball collisions
  - Ball splitting with blinking warning effect
  - Random color, speed, position and direction for dynamic difficulty
- Game States & UI
  - Start Screen with game title and clickable buttons
  - Gameplay Screen with real-time rendering and physics
  - Game Over Screen with restart and main menu navigation
  - Instructions Overlay available from the menu
  - Pause Menu Overlay with resume and main menu options
  - Fully interactive SFML Text buttons using mouse detection
- Architecture
  - Frame-rate independent movement using deltaTime
  - Modular classes for core, entities, math, physics, screens, overlays and UI utilities
  - Clean separation of logic, UI, rendering

---

## Tech Stack
- Programming Language: C++
- Frameworks: SFML
- Systems/Concepts:
    - Game loop architecture
    - Game state management (screens/overlays)
    - Pure Math Utilities
    - Physics & collision detection
    - Entity Management
    - UI rendering and text interaction
    - Real-time updates
- IDE/Tools: Visual Studio, Git/GitHub, Unreal Engine for blueprint

---

## Future Improvement
- Enhance Player Design
    - Explore new shape or custom sprite-based character
    - Add player rotation
- Expanded Input Handling
    - Introduce keyboard for movement handling and optional bindings
    - Switch mouse control for player direction and aiming
- New Gameplay Features
    - Add new gameplay mechanisims for Player
- Audio and Visual Effects
    - Expand experience with sound effects and background music
    - Polish gameplay animation

---

## Authors
**Vu Anh Thu Phan** - [GitHub](https://github.com/PVAT1187)
