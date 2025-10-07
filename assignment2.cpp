#include <bits/stdc++.h>
using namespace std;

class CSP {
    int numVariables;                       // Number of regions
    vector<vector<int>> adjacencyList;      // Graph of constraints
    vector<int> assignment;                 // Colors assigned to each region
    int numColors;                          // Number of available colors

public:
    CSP(int n, int colors) {
        numVariables = n;
        numColors = colors;
        adjacencyList.resize(n);
        assignment.resize(n, -1);
    }

    void addConstraint(int u, int v) {
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
    }

    bool isValid(int var, int color) {
        for (int neighbor : adjacencyList[var]) {
            if (assignment[neighbor] == color) return false;
        }
        return true;
    }

 
    bool backtrack(int var) {
        if (var == numVariables) return true; 

        for (int color = 0; color < numColors; color++) {
            if (isValid(var, color)) {
                assignment[var] = color;  
                if (backtrack(var + 1)) return true;
                assignment[var] = -1;     
            }
        }
        return false; 
    }

 
    void solve() {
        if (backtrack(0)) {
            cout << "Solution Found:\n";
            for (int i = 0; i < numVariables; i++) {
                cout << "Region " << i << " -> Color " << assignment[i] << "\n";
            }
        } else {
            cout << "No solution exists with " << numColors << " colors.\n";
        }
    }
};

int main() {
    
    CSP csp(4, 3);

    csp.addConstraint(0, 1);
    csp.addConstraint(0, 2);
    csp.addConstraint(1, 2);
    csp.addConstraint(2, 3);

    csp.solve();
    return 0;
}
