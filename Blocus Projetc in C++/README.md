# Brocus Project in C++

## Table of contents
- [Introduction](#introduction)
- [How it is played](#how-it-is-played)
- [Usage](#usage)
- [Contact](#contact)

## Introduction

Welcome to the Blockus Project! This project is a variation of the popular game Blokus for two players (more info: https://en.wikipedia.org/wiki/Blokus) and was created by me and my fellow students as part of the Object-Oriented Programming course.

## How it is played

Blokus is a strategy game in which 2 players participate, sitting opposite each other. Each player has a unique number (index) and a name. Additionally, there is a board, and each player possesses 21 pieces that they place on the board. An example of the board is shown in the image below:

<img width="423" alt="Στιγμιότυπο οθόνης 2024-10-04, 11 01 03 πμ" src="https://github.com/user-attachments/assets/4bd57670-2ecb-4941-8bce-85e85ba6f282">

The goal of the game is for each player to place as many of their pieces as possible on the board while simultaneously blocking their opponent from placing their pieces.

The available pieces of the players:

<img width="586" alt="Στιγμιότυπο οθόνης 2024-10-04, 11 04 22 πμ" src="https://github.com/user-attachments/assets/d07cfefc-41f5-4a7f-ad68-5fe4783b62a5">

<img width="588" alt="Στιγμιότυπο οθόνης 2024-10-04, 11 05 02 πμ" src="https://github.com/user-attachments/assets/6d68413d-a3d1-4849-bffb-4431dca307d2">

In each round of the game, players take turns placing their pieces alternately. Every new piece placed must touch at least one other piece of the same symbol (0 / #) (i.e., from the same player) at one of its corners, but not along the sides. Once the round is over, the game state is printed, showing the score of both players.

The game ends when the board doesn't fit another piece and the winner is the player who has placed the most pieces in the board.

<img width="590" alt="Στιγμιότυπο οθόνης 2024-10-04, 11 43 05 πμ" src="https://github.com/user-attachments/assets/72ef20d1-c5aa-4c14-954b-48b080813a85">


> [!NOTE]
> At this point the moves of both players are random. However, with a few changes the program can ask from the user to choose the moves of player 1 in order to play against the computer.


## Usage

To run the program, follow these steps:

1. **Download the project files**:  
   Clone the repository or download the project files into a folder on your computer.

2. **Open the project in an IDE**:  
   - Use a C++ IDE such as Xcode (the one that I used), VSCode, CodeBlocks.
   - Open the IDE and load all the project files into the appropriate folder, or create a new project and add the files manually.

3. **Compile and run the program**:  
   - Compile (build) the program using the IDE.  
   - Once the compilation is successful, run the program directly from the IDE.

## Contact

* Name: Vagelis Zarkadoulas
* Email: vagzarkadoulasdh@gmail.com
* GitHub: vagzark

[Return to the top](#blocus-project-in-c++)







