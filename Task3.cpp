//TASK 3 - TIC-TAC-TOE GAME

#include<bits/stdc++.h>
using namespace std;

// Function to print the Tic Tac Toe board with indices for unchosen cells
void printBoard(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                cout << i * 3 + j << " ";
            } else {
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }
}

// Function to check if a player has won
bool checkWin(const vector<vector<char>>& board, char player) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }

    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }

    return false;
}

// Function to check if the board is full (a tie)
bool checkTie(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ')
                return false; // There is an empty cell, game is not tied yet
        }
    }
    return true; // Board is full, it's a tie
}

// Function to clear the board for a new game
void clearBoard(vector<vector<char>>& board) {
    for (auto& row : board) {
        for (char& cell : row) {
            cell = ' ';
        }
    }
}

int main() {

    cout << "Welcome You to the TIC-TAC-TOE GAME\n\n";

    char playAgain;
    
    do {
        vector<vector<char>> board(3, vector<char>(3, ' ')); // Initialize the 3x3 Tic Tac Toe board

        char currentPlayer = 'X';
        int row, col;

        while (true) {
            // Print the current board
            cout << "Current Board:" << endl;
            printBoard(board);

            // Get the current player's move
            cout << "Player " << currentPlayer << ", enter your move (index): ";
            cin >> row;

            // Convert index to row and column
            col = row % 3;
            row /= 3;

            // Check if the chosen cell is valid and empty
            if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
                // Make the move
                board[row][col] = currentPlayer;

                // Check if the current player has won
                if (checkWin(board, currentPlayer)) {
                    cout << "Current Board:" << endl;
                    printBoard(board);
                    cout << "Player " << currentPlayer << " wins!" << endl;
                    break;
                }

                // Check if the game is tied
                if (checkTie(board)) {
                    cout << "Current Board:" << endl;
                    printBoard(board);
                    cout << "It's a tie!" << endl;
                    break;
                }

                // Switch to the other player
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            } else {
                cout << "Invalid move! Try again." << endl;
            }
        }

        // Ask if the players want to play again
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

        if (tolower(playAgain) != 'y') {
            cout << "Thanks for playing! Goodbye." << endl;
            break;
        } else {
            // Clear the board for a new game
            clearBoard(board);
        }

    } while (true);

    return 0;
}