#include <bits/stdc++.h>
using namespace std;

// Rule structure
struct Rule {
    vector<string> antecedents; // IF part
    string consequent;          // THEN part
};

// Backward Chaining function
bool backwardChaining(string goal, vector<Rule> &rules, set<string> &facts, set<string> &visited) {
    // If goal is already a known fact
    if (facts.find(goal) != facts.end()) return true;

    // Prevent infinite loops
    if (visited.find(goal) != visited.end()) return false;
    visited.insert(goal);

    // Check each rule whose consequent is the goal
    for (auto &rule : rules) {
        if (rule.consequent == goal) {
            bool allAntecedentsTrue = true;

            // Recursively check all antecedents
            for (auto &ante : rule.antecedents) {
                if (!backwardChaining(ante, rules, facts, visited)) {
                    allAntecedentsTrue = false;
                    break;
                }
            }

            if (allAntecedentsTrue) {
                cout << "Rule applied: IF ";
                for (auto &ante : rule.antecedents) cout << ante << " ";
                cout << "THEN " << rule.consequent << "\n";
                facts.insert(goal); // Add goal to facts
                return true;
            }
        }
    }

    return false; // Goal cannot be proven
}

int main() {
    // Knowledge base
    vector<Rule> rules = {
        {{"A", "B"}, "C"},
        {{"C", "D"}, "E"},
        {{"B", "E"}, "F"}
    };

    // Initial facts
    set<string> facts = {"A", "B", "D"};

    string goal = "F";
    set<string> visited; // prevent infinite recursion

    if (backwardChaining(goal, rules, facts, visited)) {
        cout << "\nGoal '" << goal << "' is proven!\n";
    } else {
        cout << "\nGoal '" << goal << "' cannot be proven.\n";
    }

    cout << "\nFinal Facts: ";
    for (auto &f : facts) cout << f << " ";
    cout << "\n";

    return 0;
}
