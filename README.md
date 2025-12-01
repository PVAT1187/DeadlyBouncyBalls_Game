# Deadly Bouncy Balls (C++ / SFML Game)

A fast-paced mini game where the player controls a rectangle and must dodge bouncing balls that move, collide, and split over time. 
Designed to explore game mechanics, real-time physics, entity handling, and game loop architecture while working with the SFML multimedia framework.

---

## Design Overview
This project was created to practice essential game development concepts using modern C++ and SFML. 
The goal was to build a minimal yet complete game system featuring dynamic entity interactions, physics-based movement, and real-time collision handling.
   - Facial Analysis: Uses Google ML Kit to detect eye landmarks and probabilities of eye openness in real-time
   - Alert System: Provides immediate visual warnings when drowsiness is detected
   - Data Analytics: Logs events to Firebase and exports to BigQuery for monitoring patterns and large-scale analysis
   - System Design: Modular structure separates detection logic, UI, and backend analytics, allowing future enhancements         easily

---

## Design Goals
- Provide real-time, immidiate feedback to enhance drivers safety
- Implement a modular architecture separating detection logic, UI, and backend analytics
- Integrate cloud-based analytics to monitor performance and usage data
- Maintain scalability and flexibility for future improvements, such as new alert mechanisms,...

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
