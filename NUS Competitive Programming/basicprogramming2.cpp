#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_set>
#include <map>

using namespace std;

// Use long long for potentially large sums if needed, although inputs fit in int
using ll = long long;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, t;
    cin >> N >> t;

    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    if (t == 1) {
        unordered_set<int> seen;
        bool found = false;
        for (int x : A) {
            int complement = 7777 - x;
            if (seen.count(complement)) {
                found = true;
                break;
            }
            seen.insert(x);
        }
        if (found) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    } else if (t == 2) {
        unordered_set<int> seen;
        bool duplicate = false;
        for (int x : A) {
            if (!seen.insert(x).second) { // insert returns pair<iterator, bool>
                duplicate = true;         // .second is false if element already exists
                break;
            }
        }
        if (duplicate) {
            cout << "Contains duplicate" << endl;
        } else {
            cout << "Unique" << endl;
        }
    } else if (t == 3) {
        // Boyer-Moore Voting Algorithm
        int candidate = -1;
        int count = 0;
        for (int x : A) {
            if (count == 0) {
                candidate = x;
                count = 1;
            } else if (x == candidate) {
                count++;
            } else {
                count--;
            }
        }

        // Verify the candidate
        count = 0;
        for (int x : A) {
            if (x == candidate) {
                count++;
            }
        }

        if (count > N / 2) {
            cout << candidate << endl;
        } else {
            cout << -1 << endl;
        }
    } else if (t == 4) {
        sort(A.begin(), A.end());
        if (N % 2 == 1) {
            cout << A[N / 2] << endl;
        } else {
            cout << A[N / 2 - 1] << " " << A[N / 2] << endl;
        }
    } else if (t == 5) {
        vector<int> result;
        for (int x : A) {
            if (x >= 100 && x <= 999) {
                result.push_back(x);
            }
        }
        sort(result.begin(), result.end());
        for (int i = 0; i < result.size(); ++i) {
            cout << result[i] << (i == result.size() - 1 ? "" : " ");
        }
        cout << endl;
    }

    return 0;
}