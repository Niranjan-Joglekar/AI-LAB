#include <bits/stdc++.h>
using namespace std;

// Rule structure
struct Rule {
    vector<string> antecedents; // IF part
    string consequent;          // THEN part
};

// Forward chaining function
bool forwardChaining(vector<Rule> &rules, set<string> &facts, string goal) {
    bool addedNewFact;

    do {
        addedNewFact = false;

        for (auto &rule : rules) {
            // Check if all antecedents are in facts
            bool canApply = true;
            for (auto &cond : rule.antecedents) {
                if (facts.find(cond) == facts.end()) {
                    canApply = false;
                    break;
                }
            }

            if (canApply) {
                // Apply rule
                if (facts.find(rule.consequent) == facts.end()) {
                    facts.insert(rule.consequent);
                    cout << "Applied rule: IF ";
                    for (auto &c : rule.antecedents) cout << c << " ";
                    cout << "THEN " << rule.consequent << "\n";
                    addedNewFact = true;

                    if (rule.consequent == goal) {
                        cout << "\nGoal '" << goal << "' reached!\n";
                        return true;
                    }
                }
            }
        }
    } while (addedNewFact); // Repeat until no new facts

    cout << "\nGoal '" << goal << "' NOT reachable.\n";
    return false;
}

int main() {
    // Define rules
    vector<Rule> rules = {
        {{"A", "B"}, "C"},
        {{"C", "D"}, "E"},
        {{"B", "E"}, "F"}
    };

    // Initial facts
    set<string> facts = {"A", "B", "D"};

    string goal = "F";

    forwardChaining(rules, facts, goal);

    cout << "\nFinal Facts: ";
    for (auto &f : facts) cout << f << " ";
    cout << "\n";

    return 0;
}
