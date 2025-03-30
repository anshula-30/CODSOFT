#include <iostream>
#include <string>
using namespace std;

class TicTacToe {
private:
    char board[3][3];
    string players[2] = {"Player X", "Player O"};
    char symbols[2] = {'X', 'O'};
    int currentPlayer;

public:
    TicTacToe() {
        resetBoard();
    }

    void resetBoard() {
        for (int i = 0; i < 3; i++) 
            for (int j = 0; j < 3; j++) 
                board[i][j] = ' ';
        currentPlayer = 0;
    }

    void drawBoard() {
        cout << "-------------\n";
        for (int i = 0; i < 3; i++) {
            cout << "| ";
            for (int j = 0; j < 3; j++) 
                cout << board[i][j] << " | ";
            cout << "\n-------------\n";
        }
    }

    bool isValidMove(int row, int col) {
        return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ';
    }

    bool checkWin() {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') return true;
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') return true;
        }
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') return true;
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') return true;
        return false;
    }

    bool isFull() {
        for (int i = 0; i < 3; i++) 
            for (int j = 0; j < 3; j++) 
                if (board[i][j] == ' ') return false;
        return true;
    }

    void play() {
        char choice;
        do {
            resetBoard();
            cout << "Welcome to Tic-Tac-Toe!\n";
            while (true) {
                drawBoard();
                int row, col;
                cout << players[currentPlayer] << " (" << symbols[currentPlayer] << "), enter row (1-3) and column (1-3): ";
                cin >> row >> col;
                row--; col--;  // Convert to 0-indexed
                
                if (isValidMove(row, col)) {
                    board[row][col] = symbols[currentPlayer];
                    if (checkWin()) {
                        drawBoard();
                        cout << players[currentPlayer] << " wins!\n";
                        break;
                    }
                    if (isFull()) {
                        drawBoard();
                        cout << "It's a draw!\n";
                        break;
                    }
                    currentPlayer = 1 - currentPlayer;  // Switch player
                } else {
                    cout << "Invalid move. Try again.\n";
                }
            }
            cout << "Do you want to play again? (y/n): ";
            cin >> choice;
        } while (choice == 'y' || choice == 'Y');
        cout << "Thanks for playing!\n";
    }
};

int main() {
    TicTacToe game;
    game.play();
    return 0;
}
