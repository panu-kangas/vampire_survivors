# Vampires! 🧛

**Vampires!** is a survival game built on top of an old Supercell code challenge template. Developed entirely by me, it is written in **C++** using the **SFML** library.  


The game was developed over **40 working hours**, adding new mechanics, enemies, and features on top of the original template. A full list of all additions and updates can be found in the `UpdateList.txt` file.

# Gameplay video (click the image to view in YouTube)

[![Watch the Vampires! demo](https://img.youtube.com/vi/f27j3-jZVr8/maxresdefault.jpg)](https://youtu.be/f27j3-jZVr8)

# Installation

Instructions on how to use the game.

## Prerequisites

1. You need to install **CMake** and **Git** in order to be able to compile this project.  
2. On Windows, you need the Visual Studio -program.  
3. If you use Linux, install SFML's dependencies using your system package manager. On Ubuntu and other Debian-based distributions you can use the following commands:
    ```
    sudo apt update
    sudo apt install \
        libfreetype6-dev \
        libxrandr-dev \
        libxcursor-dev \
        libudev-dev \
        libfreetype-dev \
        libopenal-dev \
        libflac-dev \
        libvorbis-dev \
        libgl1-mesa-dev \
        libegl1-mesa-dev
    ```

## Compilation instructions

Run the following commands in your terminal:

1. ```git clone https://github.com/panu-kangas/vampires.git && cd vampires```  
2. ```cmake -B build```  
3. ```cmake --build build```
4. ```./build/bin/vampires```

# About the game

In **Vampires!**, you play as the sole survivor of a terrible vampire outburst, and your goal is simple: survive the hordes and escape to safety.  

The game progresses in levels, so new challenges appear gradually — more vampires, new vampire types, and ever-shortening spawn times ensure the task is not easy.  

Luckily, you are armed! Your beloved **Lance** pierces through vampires, and the **Holy Pulse** ability deals area damage to your pointy-toothed foes. These abilities can be upgraded with **Skill Points** earned from completing levels.  

Good luck, and don’t forget to bring garlic!

Oh, and on top of the vampire survival craziness, this project aims to provide clean and scalable code architecture so that future development is easy and smooth.  

### Game controls

ARROW KEYS & ENTER - Navigate menu elements  

ARROW KEYS - Move player  
SPACE - Use Lance attack  
V - Use Holy Pulse attack  

# Credits

Coming soon! 

