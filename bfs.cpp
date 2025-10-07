#include <bits/stdc++.h>
using namespace std;

const int N = 3;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void printBoard(vector<vector<int>> board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0) cout << "_ ";
            else cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

string boardToString(vector<vector<int>> &board) {
    string s = "";
    for (auto &row : board)
        for (auto &val : row)
            s += to_string(val);
    return s;
}

// BFS Node structure
struct Node {
    vector<vector<int>> board;
    int x, y;     // position of blank tile (0)
    int depth;    // level in BFS tree
    vector<string> path;  // moves made (optional)
};

bool isGoal(vector<vector<int>> &board) {
    vector<vector<int>> goal = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };
    return board == goal;
}

void bfs(vector<vector<int>> &start, int startX, int startY) {
    queue<Node> q;
    unordered_set<string> visited;

    Node root = {start, startX, startY, 0, {}};
    q.push(root);
    visited.insert(boardToString(start));

    while (!q.empty()) {
        Node curr = q.front();
        q.pop();

        if (isGoal(curr.board)) {
            cout << "Goal reached at depth " << curr.depth << endl;
            printBoard(curr.board);
            cout << "Path length: " << curr.depth << endl;
            return;
        }

        // Try all 4 directions
        for (int dir = 0; dir < 4; dir++) {
            int newX = curr.x + dx[dir];
            int newY = curr.y + dy[dir];

            if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
                // Copy current board
                vector<vector<int>> newBoard = curr.board;
                swap(newBoard[curr.x][curr.y], newBoard[newX][newY]);

                string hash = boardToString(newBoard);

                if (visited.find(hash) == visited.end()) {
                    visited.insert(hash);
                    Node child = {newBoard, newX, newY, curr.depth + 1};
                    q.push(child);
                }
            }
        }
    }

    cout << "Goal not reachable!" << endl;
}

int main() {
    // Example initial state
    vector<vector<int>> start = {
        {1, 2, 3},
        {4, 0, 5},
        {6, 7, 8}
    };

    // Find position of blank (0)
    int startX, startY;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (start[i][j] == 0) {
                startX = i;
                startY = j;
            }

    bfs(start, startX, startY);
    return 0;
}
