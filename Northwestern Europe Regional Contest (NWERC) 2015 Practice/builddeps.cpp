#include <iostream>
#include <string>
#include <vector>
#include <unordered_map> // Faster than map
#include <queue>
#include <sstream>

int main() {
    // 1. --- FAST I/O ---
    // Disable synchronization with C-style stdio
    std::ios_base::sync_with_stdio(false); 
    // Untie cin from cout
    std::cin.tie(NULL); 

    int n;
    std::cin >> n;
    std::cin.ignore(); // Consume the newline after reading n

    // 2. --- GRAPH DATA STRUCTURES ---
    
    // adj[dependency] = list of files that depend on 'dependency'
    std::unordered_map<std::string, std::vector<std::string>> adj;
    
    // in_degree[file] = count of how many files 'file' depends on
    std::unordered_map<std::string, int> in_degree;
    
    // Keep track of all filenames
    std::vector<std::string> all_files(n);
    
    // 3. --- BUILD THE GRAPH ---
    for (int i = 0; i < n; ++i) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string word;

        // Read the filename (e.g., "solution:")
        ss >> word;
        std::string filename = word.substr(0, word.length() - 1);
        
        all_files[i] = filename;
        
        int dep_count = 0;
        // Read dependencies
        while (ss >> word) {
            // 'word' is a dependency. Add edge: word -> filename
            adj[word].push_back(filename);
            dep_count++;
        }
        in_degree[filename] = dep_count;
    }

    // 4. --- INITIALIZE RECOMPILATION ---
    std::string changed_file;
    std::cin >> changed_file;
    
    // needs_recompile[file] = true if it needs to be recompiled
    std::unordered_map<std::string, bool> needs_recompile;
    needs_recompile[changed_file] = true; // Mark the initial file

    // 5. --- KAHN'S ALGORITHM (TOPOLOGICAL SORT) ---
    
    // Queue for nodes with in-degree 0
    std::queue<std::string> q;

    // Find all initial nodes with in-degree 0
    for (const std::string& file : all_files) {
        if (in_degree[file] == 0) {
            q.push(file);
        }
    }

    // Stores the final ordered output
    std::vector<std::string> result;

    while (!q.empty()) {
        std::string u = q.front();
        q.pop();

        // 6. --- CHECK & PROPAGATE RECOMPILATION ---
        
        // If this file needs recompiling...
        if (needs_recompile[u]) {
            result.push_back(u);
            
            // ...propagate the 'needs_recompile' status to all dependents
            for (const std::string& v : adj[u]) {
                needs_recompile[v] = true;
            }
        }

        // 7. --- CONTINUE TOPOLOGICAL SORT ---
        
        // "Remove" this node by updating its neighbors' in-degrees
        for (const std::string& v : adj[u]) {
            in_degree[v]--;
            // If a neighbor now has no un-processed dependencies, add to queue
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    // 8. --- PRINT THE RESULT ---
    for (const std::string& file : result) {
        std::cout << file << "\n";
    }

    return 0;
}