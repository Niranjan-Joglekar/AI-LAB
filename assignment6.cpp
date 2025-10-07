#include <bits/stdc++.h>
using namespace std;

#define N 8

// Function to print the board
void printBoard(vector<vector<int>> &board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << "\n";
    }
    cout << "----------------------\n";
}

// Check if it's safe to place queen at board[row][col]
bool isSafe(vector<vector<int>> &board, int row, int col) {
    // Check column
    for (int i = 0; i < row; i++)
        if (board[i][col]) return false;

    // Check upper-left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return false;

    // Check upper-right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++)
        if (board[i][j]) return false;

    return true;
}

// Recursive backtracking function
bool solveNQueen(vector<vector<int>> &board, int row) {
    // Base case: all queens placed
    if (row == N) {
        printBoard(board);
        return true;  // change to false if you want all solutions
    }

    // Try all columns in current row
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1;  // place queen

            // Recurse for next row
            if (solveNQueen(board, row + 1))
                return true; // stop after first solution

            // Backtrack
            board[row][col] = 0;
        }
    }

    return false; // No place found
}

int main() {
    vector<vector<int>> board(N, vector<int>(N, 0));
    if (!solveNQueen(board, 0))
        cout << "No solution found\n";
    return 0;
}
