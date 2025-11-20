#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

// Define the maximum number of states.
// Max |P| * 2^K = 30 * 2^15 = 983040. We'll use a safe upper bound.
const int MAX_STATES = 1000000; 

// Aho-Corasick Automaton structures
// goto_function[u][c] is the next state from u on character c (0 or 1)
int goto_function[MAX_STATES][2]; 
// failure_link[u] is the failure link for state u
int failure_link[MAX_STATES];
// output_link[u] is true if state u is a match state
bool output_link[MAX_STATES];
// dp[i][u] is the number of strings of length i ending in state u without a match
long long dp[51][MAX_STATES];

// Global counter for the number of nodes
int num_nodes = 1;

void build_automaton(const vector<string>& patterns) {
    // Initialize root state (state 0)
    for (int i = 0; i < 2; ++i) goto_function[0][i] = 0;
    failure_link[0] = 0;
    output_link[0] = false;
    
    // 1. Insert patterns into the trie
    for (const string& pattern : patterns) {
        int node = 0;
        for (char c : pattern) {
            int char_idx = c - '0';
            if (goto_function[node][char_idx] == 0) {
                // Create new node
                goto_function[node][char_idx] = num_nodes;
                // Initialize new node
                for (int i = 0; i < 2; ++i) goto_function[num_nodes][i] = 0;
                failure_link[num_nodes] = 0;
                output_link[num_nodes] = false;
                num_nodes++;
            }
            node = goto_function[node][char_idx];
        }
        output_link[node] = true; // Mark the end of a pattern
    }

    // 2. Build failure links and the full transition table (goto function)
    queue<int> q;
    
    // Initialize queue with children of the root
    for (int i = 0; i < 2; ++i) {
        if (goto_function[0][i] != 0) {
            q.push(goto_function[0][i]);
        }
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        int fail_node = failure_link[node];
        
        // Propagate match status from the failure link's match status
        if (output_link[fail_node]) {
            output_link[node] = true;
        }

        for (int char_idx = 0; char_idx < 2; ++char_idx) {
            int next_node = goto_function[node][char_idx];
            
            if (next_node != 0) {
                // Found a direct transition, calculate its failure link
                failure_link[next_node] = goto_function[fail_node][char_idx];
                
                // Propagate match status from the failure link
                if (output_link[failure_link[next_node]]) {
                    output_link[next_node] = true;
                }
                q.push(next_node);
            } else {
                // Build the full transition table (goto function)
                // Use the transition from the failure link
                goto_function[node][char_idx] = goto_function[fail_node][char_idx];
            }
        }
    }
}

void solve() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    string P;
    
    if (!(cin >> N >> P)) return;

    // 1. Generate the set of 2^K concrete patterns (T_P)
    vector<int> wildcard_indices;
    for (int i = 0; i < P.length(); ++i) {
        if (P[i] == '*') {
            wildcard_indices.push_back(i);
        }
    }
    int K = wildcard_indices.size();
    vector<string> patterns;
    
    // Iterate through all 2^K combinations for the wildcards
    for (int i = 0; i < (1 << K); ++i) {
        string current_pattern = P;
        for (int j = 0; j < K; ++j) {
            // Bit 0 -> '0', Bit 1 -> '1'
            char char_to_replace = ((i >> j) & 1) ? '1' : '0';
            current_pattern[wildcard_indices[j]] = char_to_replace;
        }
        patterns.push_back(current_pattern);
    }

    // 2. Build the Aho-Corasick Automaton
    build_automaton(patterns);

    // 3. Dynamic Programming
    
    // Initialize DP table
    // dp[i][u] is already initialized to 0 globally
    
    // Base case: empty string (length 0) is at state 0 (root)
    dp[0][0] = 1;
    
    // DP transition
    for (int i = 0; i < N; ++i) {
        for (int u = 0; u < num_nodes; ++u) {
            if (dp[i][u] == 0) continue;
            
            // Try appending '0' and '1'
            for (int char_idx = 0; char_idx < 2; ++char_idx) {
                // Find the next state using the pre-calculated goto function
                int next_u = goto_function[u][char_idx];
                
                // Check if the next state is a match state
                if (!output_link[next_u]) {
                    // If it's not a match state, we can transition
                    dp[i+1][next_u] += dp[i][u];
                }
            }
        }
    }
    
    // 4. Calculate the final answer
    
    // Total number of strings of length N is 2^N
    long long total_strings = 1LL << N;
    
    // Number of strings that DO NOT contain any pattern (the complement)
    long long complement_count = 0;
    for (int u = 0; u < num_nodes; ++u) {
        complement_count += dp[N][u];
    }
    
    // Number of strings that DO contain at least one pattern
    long long result = total_strings - complement_count;
    
    cout << result << "\n";
}

int main() {
    solve();
    return 0;
}