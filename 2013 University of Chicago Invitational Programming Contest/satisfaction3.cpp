#include <bits/stdc++.h>
using namespace std;

// Optimized shunting yard with reduced lambda overhead
string shunting_yard(const string &infix) {
    stack<char> ops;
    string rpn;
    rpn.reserve(infix.size()); // Pre-allocate memory
    
    for (char c : infix) {
        if (c >= 'A' && c <= 'Z') {
            rpn += c;
        } else if (c == '(') {
            ops.push(c);
        } else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') {
                rpn += ops.top();
                ops.pop();
            }
            if (!ops.empty()) ops.pop();
        } else if (c == '|' || c == '&' || c == '~') {
            // Inline precedence and associativity checks
            int prec_c = (c == '|') ? 1 : (c == '&') ? 2 : 3;
            bool left_assoc = (c == '|' || c == '&');
            
            while (!ops.empty()) {
                char op = ops.top();
                if (op != '|' && op != '&' && op != '~') break;
                
                int prec_op = (op == '|') ? 1 : (op == '&') ? 2 : 3;
                if ((left_assoc && prec_c <= prec_op) || (!left_assoc && prec_c < prec_op)) {
                    rpn += op;
                    ops.pop();
                } else break;
            }
            ops.push(c);
        }
    }
    
    while (!ops.empty()) {
        rpn += ops.top();
        ops.pop();
    }
    
    return rpn;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> program;
    vector<char> vars;
    bool seen[26] = {false};
    string s;
    
    // Read input
    while (cin >> s) {
        program.push_back(s);
        for (char c : s) {
            if (c >= 'A' && c <= 'Z' && !seen[c - 'A']) {
                vars.push_back(c);
                seen[c - 'A'] = true;
            }
        }
    }
    sort(vars.begin(), vars.end());

    int n = vars.size(), m = program.size();
    int indices[26];
    fill(indices, indices + 26, -1);
    for (int i = 0; i < n; i++) indices[vars[i] - 'A'] = i;

    // Parse program structure
    vector<string> rpns;
    vector<vector<pair<int, bool>>> order;
    vector<pair<int, bool>> checkpoint;
    
    for (int i = 0; i < m; i++) {
        if (program[i] == "if") {
            checkpoint.emplace_back(rpns.size(), false);
            rpns.push_back(shunting_yard(program[i + 1]));
            i += 2;
        } else if (program[i] == "fi") {
            checkpoint.pop_back();
        } else if (program[i] == "else") {
            checkpoint.back().second = true;
        } else if (program[i] == "checkpoint") {
            order.push_back(checkpoint);
        }
    }

    // Build truth tables
    vector<bitset<1 << 20>> table(n);
    int total_states = 1 << n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < total_states; j++) {
            table[i][j] = (j >> i) & 1;
        }
    }

    // Evaluate expressions
    vector<bitset<1 << 20>> evals(rpns.size());
    for (size_t i = 0; i < rpns.size(); i++) {
        stack<bitset<1 << 20>> st;
        for (char c : rpns[i]) {
            if (c >= 'A' && c <= 'Z') {
                st.push(table[indices[c - 'A']]);
            } else if (c == '~') {
                auto bs1 = st.top();
                st.pop();
                st.push(~bs1);
            } else {
                auto bs1 = st.top();
                st.pop();
                auto bs2 = st.top();
                st.pop();
                st.push((c == '&') ? (bs1 & bs2) : (bs1 | bs2));
            }
        }
        evals[i] = st.top();
    }

    // Process checkpoints
    for (const auto& checkpoint : order) {
        bitset<1 << 20> bs;
        bs.set();

        for (const auto& [i, negate] : checkpoint) {
            bs &= negate ? ~evals[i] : evals[i];
        }

        cout << ">";
        if (bs.none()) {
            cout << "unreachable\n";
        } else {
            for (int i = 0; i < n; i++) {
                if ((table[i] & bs) == bs) cout << vars[i];
                else if ((~table[i] & bs) == bs) cout << (char)(vars[i] + 32);
            }
            cout << "\n";
        }
    }
    
    return 0;
}