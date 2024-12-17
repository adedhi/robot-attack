# Table of Contents
- [Robot Attack](#robot-attack)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [License](#license)
- [Acknowledgements](#acknowledgements)
- [Contact](#contact)

------------------------------

# Robot Attack
![Game Screenshot](https://github.com/adedhi/robot-attack/blob/main/Images/robot_attack_image.png)
![GitHub](https://img.shields.io/github/license/adedhi/robot-attack)

This is a 3D robot attack game created for the CPS511: Computer Graphics course at Toronto Metropolitan University. The project implements a defensive cannon that the player controls to shoot waves of incoming robots, which walk forward and fire projectiles. The game includes collision detection, animated projectiles, and increasing difficulty with each wave. The scene is rendered with GPU vertex and fragment shaders for lighting, shading, and texture mapping.

## Features
- **Defensive Cannon**: Player-controlled cannon (via arrow keys) that can fire projectiles using the space bar.
- **Enemy Robots**: Animated robots that walk toward the cannon and shoot projectiles with random accuracy.
- **Progressive Waves**: Endless waves of robots that increase in number, speed, and firing rate as the game progresses.
- **Collision Detection**: Projectiles can collide with robots, other projectiles, and the ground, with appropriate visual responses.
- **Game States**: The cannon animates to a broken state when hit, and the player can choose to restart or quit the game.
- **Shaders**: Uses custom vertex and fragment shaders to handle lighting, shading, and texture mapping.
- **Textures**: Texture-mapped cannon and projectiles for enhanced visuals.

## Requirements
- Visual Studio 2022 (or compatible version)

## Installation
1. Download the 'Code' folder, which contains all the program files, visual studio files, and dependencies.

## Usage
1. Open Visual Studio
2. Click 'Open a Project or Solution'
3. Choose the 'Assignment 3.sln' file in the 'Code' folder
5. Once the project loads, click the Run button (green arrow) on the top of the screen (It says 'Local Windows Debugger' on Windows)
6. The project will open a debugging terminal (with instructions on how to use the program) and a separate window with the game

------------------------------

# Acknowledgements
- This program was created for a project in the CPS511: Computer Graphics course at Toronto Metropolitan University
- This project uses the stb_image.h file from the stb library by Sean Barrett. GitHub link: (https://github.com/nothings/stb).

# License
This project is licensed under the MIT License - learn more about it [here](LICENSE).

# Contact
If you have any questions, suggestions, or feedback, feel free to reach out to me at dadeshvir@gmail.com
