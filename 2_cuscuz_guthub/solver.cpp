#include "list.hpp"
#include <iostream>
#include <string>

using namespace std;

// Helper function to determine numeric value of a card
int getCardValue(string card) {
    char valueChar = card[0];
    if (valueChar >= '1' && valueChar <= '9') {
        return valueChar - '0';
    }
    return 0; // Should never happen
}

// Helper function to assign a value to the suit
int getSuitValue(string card) {
    char suitChar = card[1];
    if (suitChar == 'P') return 4; // Clubs
    if (suitChar == 'O') return 3; // Diamonds
    if (suitChar == 'E') return 2; // Spades
    if (suitChar == 'C') return 1; // Hearts
    return 0;
}

bool card1_is_greater(string card1, string card2) {
    int val1 = getCardValue(card1);
    int val2 = getCardValue(card2);

    if (val1 > val2) return true;
    if (val1 < val2) return false;

    // If values are equal, compare suit
    int suit1 = getSuitValue(card1);
    int suit2 = getSuitValue(card2);

    return suit1 > suit2;
}

int main() {
    string game_header;
    int N, M, H;
    cin >> game_header >> N >> M >> H;

    // 1. Initialize players' hands
    Queue* playerHands = new Queue[N];

    // 2. Deal the cards
    for (int h = 0; h < H; ++h) {
        for (int p = 0; p < N; ++p) {
            string card;
            cin >> card;
            playerHands[p].push(card);
        }
    }

    // 3. Initialize scores
    int* scores = new int[N];
    for (int i = 0; i < N; ++i) {
        scores[i] = 0;
    }

    Stack pile;

    int playersInGame = 0;
    for (int i = 0; i < N; ++i) {
        if (playerHands[i].size() > 0) {
            playersInGame++;
        }
    }

    // 4. Main game loop
    for (int round = 0; round < M; ++round) {
        // Stop condition: only one player has cards
        if (playersInGame <= 1) {
            break;
        }

        string bestCard = "";

        int winners[N];
        int numWinners = 0;
        string cardsPlayed[N];
        int numPlayed = 0;

        // 4a. Each player plays one card
        for (int p = 0; p < N; ++p) {
            if (playerHands[p].size() > 0) {
                string card = playerHands[p].front();
                playerHands[p].pop();
                cardsPlayed[numPlayed++] = card;

                if (bestCard == "") {
                    bestCard = card;
                    numWinners = 0;
                    winners[numWinners++] = p;
                } else if (card1_is_greater(card, bestCard)) {
                    bestCard = card;
                    numWinners = 0;
                    winners[numWinners++] = p;
                } else if (getCardValue(card) == getCardValue(bestCard) &&
                           getSuitValue(card) == getSuitValue(bestCard)) {
                    winners[numWinners++] = p;
                }
            }
        }

        // 4b. Add cards to the pile
        for (int i = 0; i < numPlayed; ++i) {
            pile.push(cardsPlayed[i]);
        }

        // 4c. Display round results
        cout << round << " " << bestCard;
        for (int i = 0; i < numWinners; ++i) {
            int winner_id = winners[i];
            cout << " " << winner_id;
            scores[winner_id]++;
        }
        cout << endl;

        // 4d. Handle pile distribution
        if (numWinners == 1) {
            int sole_winner = winners[0];
            while (pile.size() > 0) {
                playerHands[sole_winner].push(pile.top());
                pile.pop();
            }
        } else {
            // Tie: discard pile
            while (pile.size() > 0) {
                pile.pop();
            }
        }

        // 4e. Update number of active players
        playersInGame = 0;
        for (int i = 0; i < N; ++i) {
            if (playerHands[i].size() > 0) {
                playersInGame++;
            }
        }
    }

    // 5. Final output

    // 5a. Print players’ scores
    for (int i = 0; i < N; ++i) {
        cout << scores[i] << (i == N - 1 ? "" : " ");
    }
    cout << endl;

    // 5b. Determine final winners
    int finalWinners[N];
    int numFinalWinners = 0;

    if (playersInGame <= 1) {
        // Case 1: only one (or none) player left
        for (int i = 0; i < N; ++i) {
            if (playerHands[i].size() > 0) {
                finalWinners[numFinalWinners++] = i;
            }
        }
    } else {
        // Case 2: game ended due to max rounds
        int maxScore = -1;
        for (int i = 0; i < N; ++i) {
            if (scores[i] > maxScore) {
                maxScore = scores[i];
            }
        }
        for (int i = 0; i < N; ++i) {
            if (scores[i] == maxScore) {
                finalWinners[numFinalWinners++] = i;
            }
        }
    }

    // 5c. Display hands of the winners
    for (int i = 0; i < numFinalWinners; ++i) {
        int winner_id = finalWinners[i];
        cout << winner_id << ":";
        size_t handSize = playerHands[winner_id].size();
        for (size_t j = 0; j < handSize; ++j) {
            string card = playerHands[winner_id].front();
            playerHands[winner_id].pop();
            cout << " " << card;
            playerHands[winner_id].push(card);
        }
        cout << endl;
    }

    // Clean up allocated memory
    delete[] playerHands;
    delete[] scores;

    return 0;
}