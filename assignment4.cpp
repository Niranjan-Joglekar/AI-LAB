#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
#include <algorithm>
using namespace std;

struct Node {
    int x, y;
    int g, h, f;
    Node* parent;
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->f > b->f; // Min-heap based on f
    }
};

// Manhattan distance heuristic
int heuristic(int x, int y, int gx, int gy) {
    return abs(x - gx) + abs(y - gy);
}

// Check if (x, y) is within grid
bool isValid(int x, int y, int rows, int cols) {
    return x >= 0 && y >= 0 && x < rows && y < cols;
}

void aStar(int startX, int startY, int goalX, int goalY, int rows, int cols) {
    priority_queue<Node*, vector<Node*>, Compare> openList;
    set<pair<int, int>> closedList;

    Node* start = new Node{startX, startY, 0, heuristic(startX, startY, goalX, goalY), 0, NULL};
    start->f = start->g + start->h;

    openList.push(start);

    // Directions: down, up, right, left
    vector<pair<int, int>> dirs;
    dirs.push_back(make_pair(1, 0));
    dirs.push_back(make_pair(-1, 0));
    dirs.push_back(make_pair(0, 1));
    dirs.push_back(make_pair(0, -1));

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        // skip if already visited
        if (closedList.count(make_pair(current->x, current->y)) > 0)
            continue;

        closedList.insert(make_pair(current->x, current->y));

        cout << "Visiting: (" << current->x << "," << current->y << ") f=" << current->f << endl;

        // Goal reached
        if (current->x == goalX && current->y == goalY) {
            cout << "\n Path found:\n";
            vector<pair<int, int>> path;
            while (current != NULL) {
                path.push_back(make_pair(current->x, current->y));
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            for (int i = 0; i < path.size(); i++) {
                cout << "(" << path[i].first << "," << path[i].second << ") ";
            }
            cout << endl;
            return;
        }

        // Explore neighbors
        for (int i = 0; i < dirs.size(); i++) {
            int nx = current->x + dirs[i].first;
            int ny = current->y + dirs[i].second;

            if (!isValid(nx, ny, rows, cols))
                continue;
            if (closedList.count(make_pair(nx, ny)) > 0)
                continue;

            int g = current->g + 1;
            int h = heuristic(nx, ny, goalX, goalY);
            int f = g + h;

            Node* neighbor = new Node{nx, ny, g, h, f, current};
            openList.push(neighbor);
        }
    }

    cout << " No path found\n";
}

int main() {
    int rows = 4, cols = 4;
    aStar(0, 0, 3, 3, rows, cols);
    return 0;
}
