#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

char board[3][3];
char currentPlayer;

int playerXScore = 0;
int playerOScore = 0;
int drawScore = 0;

// Initialize board
void initializeBoard() {

    char ch = '1';

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = ch++;
        }
    }
}

// Display board
void displayBoard() {

    cout << "\n";
    cout << "=====================\n";
    cout << "     TIC TAC TOE     \n";
    cout << "=====================\n";

    cout << "\nScoreboard:\n";
    cout << "Player X : " << playerXScore << endl;
    cout << "Player O : " << playerOScore << endl;
    cout << "Draws    : " << drawScore << endl;

    cout << "\n";

    for(int i = 0; i < 3; i++) {

        cout << " ";

        for(int j = 0; j < 3; j++) {

            cout << board[i][j];

            if(j < 2)
                cout << " | ";
        }

        cout << "\n";

        if(i < 2)
            cout << "---|---|---\n";
    }

    cout << "\n";
}

// Switch player
void switchPlayer() {

    if(currentPlayer == 'X')
        currentPlayer = 'O';
    else
        currentPlayer = 'X';
}

// Validate move
bool isValidMove(int choice) {

    if(choice < 1 || choice > 9)
        return false;

    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if(board[row][col] == 'X' || board[row][col] == 'O')
        return false;

    return true;
}

// Make move
void makeMove(int choice) {

    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    board[row][col] = currentPlayer;
}

// Check win
bool checkWin() {

    // Rows
    for(int i = 0; i < 3; i++) {

        if(board[i][0] == board[i][1] &&
           board[i][1] == board[i][2])
            return true;
    }

    // Columns
    for(int i = 0; i < 3; i++) {

        if(board[0][i] == board[1][i] &&
           board[1][i] == board[2][i])
            return true;
    }

    // Diagonals
    if(board[0][0] == board[1][1] &&
       board[1][1] == board[2][2])
        return true;

    if(board[0][2] == board[1][1] &&
       board[1][1] == board[2][0])
        return true;

    return false;
}

// Check draw
bool checkDraw() {

    for(int i = 0; i < 3; i++) {

        for(int j = 0; j < 3; j++) {

            if(board[i][j] != 'X' &&
               board[i][j] != 'O')
                return false;
        }
    }

    return true;
}

// Generate AI move
int generateAIMove() {

    int move;

    do {
        move = rand() % 9 + 1;
    }
    while(!isValidMove(move));

    return move;
}

// Save game history
void saveGameHistory(string result) {

    ofstream file("history.txt", ios::app);

    if(file.is_open()) {

        file << result << endl;

        file.close();
    }
}

int main() {

    srand(time(0));

    char replay;
    int mode;

    cout << "==============================\n";
    cout << "      TIC TAC TOE GAME        \n";
    cout << "==============================\n";

    do {

        initializeBoard();

        cout << "\nSelect Game Mode:\n";
        cout << "1. Player vs Player\n";
        cout << "2. Player vs Computer\n";
        cout << "Enter choice: ";
        cin >> mode;

        currentPlayer = 'X';

        bool gameOver = false;

        while(!gameOver) {

            displayBoard();

            int choice;

            // Computer move
            if(mode == 2 && currentPlayer == 'O') {

                cout << "Computer is making a move...\n";

                choice = generateAIMove();
            }
            else {

                cout << "Player "
                     << currentPlayer
                     << ", enter your move (1-9): ";

                cin >> choice;
            }

            // Validate move
            if(!isValidMove(choice)) {

                cout << "Invalid move! Try again.\n";
                continue;
            }

            // Make move
            makeMove(choice);

            // Check win
            if(checkWin()) {

                displayBoard();

                string result;

                if(mode == 2 && currentPlayer == 'O') {

                    cout << "Computer wins!\n";

                    result = "Computer won the match.";

                    playerOScore++;
                }
                else {

                    cout << "Player "
                         << currentPlayer
                         << " wins!\n";

                    result = string("Player ") +
                             currentPlayer +
                             " won the match.";

                    if(currentPlayer == 'X')
                        playerXScore++;
                    else
                        playerOScore++;
                }

                saveGameHistory(result);

                gameOver = true;
            }

            // Check draw
            else if(checkDraw()) {

                displayBoard();

                cout << "It's a draw!\n";

                drawScore++;

                saveGameHistory("Match ended in a draw.");

                gameOver = true;
            }

            // Continue game
            else {

                switchPlayer();
            }
        }

        cout << "\nDo you want to play again? (y/n): ";
        cin >> replay;

    } while(replay == 'y' || replay == 'Y');

    cout << "\n==============================\n";
    cout << "       FINAL SCOREBOARD       \n";
    cout << "==============================\n";

    cout << "Player X Wins : " << playerXScore << endl;
    cout << "Player O Wins : " << playerOScore << endl;
    cout << "Draw Matches  : " << drawScore << endl;


    cout << "\nThanks for playing!\n";

    return 0;
}