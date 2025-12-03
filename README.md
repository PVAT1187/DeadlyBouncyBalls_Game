# Deadly Bouncy Balls (C++ / SFML Game)

A fast-paced mini game where the player controls a rectangle and must dodge bouncing balls that move, collide, and split over time. 
Designed to explore game mechanics, real-time physics, entity handling, and game loop architecture while working with the SFML multimedia framework.

---

## Design Overview
This project was created to practice essential game development concepts using modern C++ and SFML. 
The goal was to build a minimal yet complete game system featuring dynamic entity interactions, physics-based movement, and real-time collision handling.
   - Game Mechanics: Implements a continuous game loop that updates movement, handles physics, detects collisions, and          renders each frame
   - Physics Simulation: Balls move with velocity, bounce off walls, collide with each other, and split into smaller,           faster balls over time
   - Entity Handling: Uses dedicated classes (Ball, BallManager, Player) to modularize gameplay logic
   - Visual Effects: Balls blink as a visual warning before splitting, enhancing player feedback and game feel
   - Framework Integration: Demonstrates use of SFML’s rendering, input handling, vector math, and timing systems

---

## Design Goals
- Provide an engaging and reactive gameplay experience based on dodging mechanics
- Implement a scalable and modular architecture separating physics, rendering, and game state logic
- Explore real-time game loops, delta-time movement, and entity-based interactions
- Build familiarity with SFML as a multimedia/game development framework
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


---

## Features
- Core Gameplay
  - Real-time physics and bouncing
  - Circle-to-rectangle and ball-to-ball collisions
  - Ball splitting with blinking warning effect
  - Random color, speed, and direction for dynamic difficulty
- Game States & UI
  - Start Screen with game title and clickable start button
  - Gameplay Screen with real-time rendering and physics
  - Game Over Screen with restart and main menu navigation
  - Instructions Overlay available from the menu
  - Pause Menu Overlay with resume and exit options
  - Fully interactive SFML Text buttons using mouse detection
- Architecture
  - Frame-rate independent movement using deltaTime
  - Modular classes for entities, physics, screens, and overlays
  - Clean separation of logic vs UI vs rendering

---

## Tech Stack
- Programming Language: C++
- Frameworks: SFML
- Systems/Concepts:
    - Game loop architecture
    - State management (screens/overlays)
    - Physics & collision detection
    - Entity Management
    - UI rendering and text interaction
    - Real-time updates
- IDE/Tools: Visual Studio, Git/GitHub

---

## Future Improvement
- Explore new alert mechanisms to enhance respnsiveness
- Expand analytics capabilities with more detailed event tracking

---

## Authors
**Vu Anh Thu Phan** - [GitHub](https://github.com/PVAT1187)
