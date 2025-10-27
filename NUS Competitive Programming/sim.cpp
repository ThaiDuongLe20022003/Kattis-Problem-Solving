#include <iostream>
#include <string>
#include <list>
#include <iterator> // Required for std::list::iterator

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    cin.ignore(); // Consume the newline after reading T

    while (T--) {
        string s;
        getline(cin, s); // Read the whole line, including spaces if any

        list<char> text;
        list<char>::iterator cursor = text.end();

        for (char c : s) {
            if (c == '<') {
                if (cursor != text.begin()) {
                    cursor--; // Move iterator back to the character to delete
                    cursor = text.erase(cursor); // Erase and update cursor
                }
            } else if (c == '[') {
                cursor = text.begin();
            } else if (c == ']') {
                cursor = text.end();
            } else {
                // Insert character *before* the cursor position.
                // The cursor iterator remains valid and points after the new char.
                text.insert(cursor, c);
            }
        }

        // Print the final text
        for (char ch : text) {
            cout << ch;
        }
        cout << "\n";
    }

    return 0;
}