# 21-Point Poker Game

## Overview

This project is a simple implementation of a 21-Point Poker game using C and the EasyX graphics library. The game allows two players to draw cards, aiming to achieve a hand total as close to 21 as possible without exceeding it. The game features basic graphical interfaces for card display and player interactions.

## Features

- **Card Dealing**: Each player is dealt two initial cards.
- **Player Actions**: Players can choose to "Hit" (draw another card) or "Stand" (keep their current hand).
- **Graphics**: Visual representation of cards and game controls using EasyX.
- **Help Menu**: Instructions on how to play the game.
- **Winner Determination**: Determines and displays the winner based on the highest score ≤ 21.

## Prerequisites

- **EasyX Library**: Required for graphical functions. Download and install the EasyX library from the [EasyX website](http://easyx.cn/).
- **C Compiler**: A C compiler that supports the C99 standard or later.

## Installation

1. **Install EasyX Library**:
   - Download the EasyX library from the official [EasyX website](http://easyx.cn/).
   - Follow the installation instructions provided on the website to integrate EasyX into your development environment.

2. **Set Up Your Development Environment**:
   - Ensure EasyX header files and libraries are properly linked in your project settings.

## Compilation and Execution

1. **Compile the Code**:
   ```bash
   gcc -o poker_game poker_game.c -lEasyX
   ```
   Make sure to link against the EasyX library using `-lEasyX`.

2. **Run the Program**:
   ```bash
   ./poker_game
   ```

## Gameplay Instructions

1. **Initial Deal**: Each player is dealt two cards face up.
2. **Player Turn**: During each player's turn:
   - **Hit**: Draw a new card. Click the "Hit" button to draw a card.
   - **Stand**: Keep your current hand. Click the "Stand" button to end your turn.
3. **Help**: Click the "Help" button to display game instructions.
4. **End of Game**: The game ends when all players have stood. The player with the highest total score ≤ 21 wins. If all players bust (exceed 21), there is no winner.

## Functions

- `initializeDeck(Card deck[], int numDecks)`: Initializes the deck with the specified number of decks.
- `shuffleDeck(Card deck[], int numDecks)`: Shuffles the deck randomly.
- `drawCard(Card deck[], int *deckIndex)`: Draws a card from the deck.
- `calculatePoints(Player *player)`: Calculates the total points for a player’s hand.
- `dealInitialCards(Player players[], Card deck[], int *deckIndex)`: Deals two initial cards to each player.
- `displayCard(int x, int y, Card card)`: Displays a single card at the specified coordinates.
- `displayHand(int x, int y, Player player, int showAll)`: Displays a player's hand.
- `displayText(int x, int y, const char *text)`: Displays text at the specified coordinates.
- `displayHelp()`: Displays the help menu with game instructions.
- `gameLoop(Player players[], Card deck[], int numDecks)`: Manages the game flow and player interactions.

## Acknowledgements

- **EasyX Library**: Provides graphical functions used in this project.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
