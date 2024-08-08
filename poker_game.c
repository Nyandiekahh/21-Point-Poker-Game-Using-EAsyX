#include <easyx.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define constants
#define DECK_SIZE 52
#define MAX_DECKS 4
#define PLAYER_COUNT 2
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAX_CARDS 12 // Maximum number of cards a player can have

// Card structure
typedef struct {
    int value;   // Card value
    char suit;   // Card suit
} Card;

// Player structure
typedef struct {
    Card hand[MAX_CARDS]; // Player hand (max 12 cards)
    int cardCount;        // Number of cards in hand
    int totalPoints;      // Total points in hand
} Player;

// Function prototypes
void initializeDeck(Card deck[], int numDecks);
void shuffleDeck(Card deck[], int numDecks);
Card drawCard(Card deck[], int *deckIndex);
int calculatePoints(Player *player);
void dealInitialCards(Player players[], Card deck[], int *deckIndex);
void displayCard(int x, int y, Card card);
void displayHand(int x, int y, Player player, int showAll);
void displayText(int x, int y, const char *text);
void displayHelp();
void gameLoop(Player players[], Card deck[], int numDecks);

int main() {
    // Initialize EasyX
    initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Seed random number generator
    srand(time(0));

    // Initialize deck and players
    Card deck[DECK_SIZE * MAX_DECKS];
    Player players[PLAYER_COUNT];
    int numDecks = 2; // Number of decks to use
    int deckIndex = 0;

    initializeDeck(deck, numDecks);
    shuffleDeck(deck, numDecks);

    // Initialize players
    for (int i = 0; i < PLAYER_COUNT; i++) {
        players[i].cardCount = 0;
        players[i].totalPoints = 0;
    }

    // Deal initial cards
    dealInitialCards(players, deck, &deckIndex);

    // Start game loop
    gameLoop(players, deck, numDecks);

    // Close EasyX
    closegraph();
    return 0;
}

void initializeDeck(Card deck[], int numDecks) {
    char suits[] = {'H', 'D', 'S', 'C'};
    int index = 0;

    for (int d = 0; d < numDecks; d++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 1; j <= 13; j++) {
                deck[index].value = j;
                deck[index].suit = suits[i];
                index++;
            }
        }
    }
}

void shuffleDeck(Card deck[], int numDecks) {
    int n = DECK_SIZE * numDecks;
    for (int i = 0; i < n; i++) {
        int r = rand() % n;
        Card temp = deck[i];
        deck[i] = deck[r];
        deck[r] = temp;
    }
}

Card drawCard(Card deck[], int *deckIndex) {
    return deck[(*deckIndex)++];
}

int calculatePoints(Player *player) {
    int points = 0;
    int aceCount = 0;

    for (int i = 0; i < player->cardCount; i++) {
        int value = player->hand[i].value;
        if (value > 10) {
            points += 10;
        } else if (value == 1) {
            aceCount++;
            points += 11;
        } else {
            points += value;
        }
    }

    while (points > 21 && aceCount > 0) {
        points -= 10;
        aceCount--;
    }

    player->totalPoints = points;
    return points;
}

void dealInitialCards(Player players[], Card deck[], int *deckIndex) {
    for (int i = 0; i < PLAYER_COUNT; i++) {
        players[i].hand[0] = drawCard(deck, deckIndex);
        players[i].hand[1] = drawCard(deck, deckIndex);
        players[i].cardCount = 2;
        calculatePoints(&players[i]);
    }
}

void displayCard(int x, int y, Card card) {
    char valueStr[3];
    if (card.value == 1) {
        sprintf(valueStr, "A");
    } else if (card.value > 10) {
        if (card.value == 11) sprintf(valueStr, "J");
        if (card.value == 12) sprintf(valueStr, "Q");
        if (card.value == 13) sprintf(valueStr, "K");
    } else {
        sprintf(valueStr, "%d", card.value);
    }

    char suitStr[2] = {card.suit, '\0'};
    rectangle(x, y, x + 50, y + 70);
    outtextxy(x + 5, y + 5, valueStr);
    outtextxy(x + 5, y + 35, suitStr);
}

void displayHand(int x, int y, Player player, int showAll) {
    for (int i = 0; i < player.cardCount; i++) {
        if (showAll || i == 0) {
            displayCard(x + i * 55, y, player.hand[i]);
        } else {
            rectangle(x + i * 55, y, x + i * 55 + 50, y + 70);
        }
    }
}

void displayText(int x, int y, const char *text) {
    outtextxy(x, y, text);
}

void displayHelp() {
    cleardevice();
    displayText(50, 50, "21-Point Poker Game Instructions");
    displayText(50, 100, "1. Each player is dealt two cards initially.");
    displayText(50, 150, "2. Players take turns to either 'Hit' or 'Stand'.");
    displayText(50, 200, "3. 'Hit' means to take another card.");
    displayText(50, 250, "'Stand' means to keep your current hand.");
    displayText(50, 300, "Cards 2-10 are worth their face value.");
    displayText(50, 350, "J, Q, K are worth 10 points each.");
    displayText(50, 400, "Aces can be worth 1 or 11 points.");
    displayText(50, 450, "If a player's total exceeds 21, they bust and lose.");
    displayText(50, 500, "The player with the highest total <= 21 wins.");
    displayText(50, 550, "Press any key to return to the game.");
    getch();
    cleardevice();
}

void gameLoop(Player players[], Card deck[], int numDecks) {
    int deckIndex = numDecks * DECK_SIZE;
    int playerIndex = 0;
    int running = 1;
    MOUSEMSG mouse;

    while (running) {
        while (MouseHit()) {
            mouse = GetMouseMsg();
            if (mouse.uMsg == WM_LBUTTONDOWN) {
                int x = mouse.x;
                int y = mouse.y;

                // Check if "Hit" button was clicked
                if (x >= 50 && x <= 150 && y >= 500 && y <= 550) {
                    if (players[playerIndex].cardCount < MAX_CARDS) {
                        players[playerIndex].hand[players[playerIndex].cardCount++] = drawCard(deck, &deckIndex);
                        int points = calculatePoints(&players[playerIndex]);

                        if (points > 21) {
                            printf("Player %d busts with %d points!\n", playerIndex + 1, points);
                            running = 0;
                            break;
                        }
                    } else {
                        printf("Player %d cannot draw more cards.\n", playerIndex + 1);
                    }
                }

                // Check if "Stand" button was clicked
                if (x >= 200 && x <= 300 && y >= 500 && y <= 550) {
                    playerIndex++;
                    if (playerIndex >= PLAYER_COUNT) {
                        running = 0;
                        break;
                    }
                }

                // Check if "Help" button was clicked
                if (x >= 350 && x <= 450 && y >= 500 && y <= 550) {
                    displayHelp();
                }
            }
        }

        cleardevice();

        displayHand(50, 50, players[0], playerIndex > 0);
        displayHand(50, 200, players[1], 1);

        // Draw buttons
        rectangle(50, 500, 150, 550);
        outtextxy(75, 515, "Hit");
        rectangle(200, 500, 300, 550);
        outtextxy(215, 515, "Stand");
        rectangle(350, 500, 450, 550);
        outtextxy(375, 515, "Help");

        Sleep(100);
    }

    // Compare points
    int winner = -1;
    int maxPoints = 0;

    for (int i = 0; i < PLAYER_COUNT; i++) {
        printf("Player %d's final hand: ", i + 1);
        displayHand(50, 50 + i * 150, players[i], 1);
        printf("Total points: %d\n", players[i].totalPoints);

        if (players[i].totalPoints > maxPoints && players[i].totalPoints <= 21) {
            maxPoints = players[i].totalPoints;
            winner = i;
        }
    }

    if (winner != -1) {
        printf("Player %d wins with %d points!\n", winner + 1, maxPoints);
    } else {
        printf("No winner!\n");
    }
}
