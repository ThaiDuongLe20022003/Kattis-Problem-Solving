#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Define the structure for a Trie node
struct TrieNode {
    // children[0] is 'a', children[1] is 'b', etc.
    TrieNode* children[26];
    // How many names have this prefix
    int count;

    TrieNode() : count(0) {
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
    }
};

/**
 * Inserts a name into the Trie, incrementing the count
 * at each node along the path.
 */
void insert(TrieNode* root, const string& name) {
    TrieNode* curr = root;
    for (char c : name) {
        int idx = c - 'a';
        if (curr->children[idx] == nullptr) {
            curr->children[idx] = new TrieNode();
        }
        curr = curr->children[idx];
        curr->count++;
    }
}

/**
 * Queries the Trie for a nickname and returns the
 * number of names that have it as a prefix.
 */
int query(TrieNode* root, const string& nickname) {
    TrieNode* curr = root;
    for (char c : nickname) {
        int idx = c - 'a';
        if (curr->children[idx] == nullptr) {
            // If the path doesn't exist, no names match.
            return 0;
        }
        curr = curr->children[idx];
    }
    // The count at the end of the nickname's path is our answer.
    return curr->count;
}

// TODO: A real application would need a function to delete the Trie
// to prevent memory leaks, but it's omitted in competitive programming.

int main() {
    // Fast I/O, as requested by the problem warning
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int A;
    cin >> A;
    cin.ignore(); // Consume the newline

    TrieNode* root = new TrieNode();
    string line;

    // 1. Build the Trie from all A names
    for (int i = 0; i < A; ++i) {
        getline(cin, line);
        insert(root, line);
    }

    int B;
    cin >> B;
    cin.ignore(); // Consume the newline

    // 2. Query the Trie for all B nicknames
    for (int i = 0; i < B; ++i) {
        getline(cin, line);
        cout << query(root, line) << "\n";
    }

    // Note: We don't free the memory allocated for the Trie,
    // as the program is about to exit and the OS will reclaim it.
    return 0;
}